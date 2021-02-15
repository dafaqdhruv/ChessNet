#pragma once

#include "NetCommon.h"
#include "NetMessage.h"
#include "Net_TSQueue.h"

namespace net
{
	template <typename T>
	class connection : public std::enable_shared_from_this<connection<T>> // Creates shared pointer internally from this
	{
	public:

		enum class owner
		{
			server,
			client
		};

		connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>>& qIn) : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
		{
			m_nOwnerType = parent;
		}

		virtual ~connection()
		{}

		uint32_t GetID() const
		{return id;}


	public:

		void ConnectToClient(uint32_t uid = 0)
		{
			if(m_nOwnerType == owner::server)
			{
				if(m_socket.is_open())
				{
					id = uid;
					ReadHeader();
				}
			}
		}


		void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints)
		{
			// Only clients can connect to servers
				if (m_nOwnerType == owner::client)
				{
					// Request asio attempts to connect to an endpoint
					asio::async_connect(m_socket, endpoints,
						[this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
						{
							if (!ec)
							{
								ReadHeader();
							}
						});
				}
		}


		void Disconnect()
		{
			if (IsConnected())
					asio::post(m_asioContext, [this]() { m_socket.close(); });
		}


		bool IsConnected() const
		{
			return m_socket.is_open();
		}

	public:
		
		// ASYNC - Send a message, connections are one-to-one so no need to specifiy
		// the target, for a client, the target is the server and vice versa
		void Send(const message<T>& msg)
		{
			asio::post(m_asioContext,
				[this, msg]()
				{
					// If the queue has a message in it, then we must 
					// assume that it is in the process of asynchronously being written.
					// Either way add the message to the queue to be output. If no messages
					// were available to be written, then start the process of writing the
					// message at the front of the queue.
					bool bWritingMessage = !m_qMessagesOut.empty();
					m_qMessagesOut.push_back(msg);
					if (!bWritingMessage)
					{
						WriteHeader();
					}
				});
		}

		// Retrieve queue of messages from server
		tsqueue<owned_message<T>>& Incoming()
		{ 
			return m_qMessagesIn;
		}


	private:
		//ASYNC - Prime context ready to read a message header
		void ReadHeader()
		{
			asio::async_read(m_socket, asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
				[this](std::error_code ec, std::size_t length)
				{
					if(!ec)
					{
						if(m_msgTemporaryIn.header.size > 0)
						{
							m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
							ReadBody();
						}
						else
						{
							AddToIncomingMessageQueue();
						}
					}
					else
					{
						std::cout<<"["<<id<<"] Read Header Fail.\n";
						m_socket.close();
					}
				});
		}
	
		//ASYNC - Prime context ready to read a message body
		void ReadBody()
		{
			asio::async_read(m_socket, asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
				[this](std::error_code ec, std::size_t length)
				{
					if(!ec)
					{
						AddToIncomingMessageQueue();
					}
					else
					{
						std::cout<<"["<<id<<"] Read Body Fail.\n";
						m_socket.close();
					}
				});
		}
		
		//ASYNC - Prime context ready to write a message header
		void WriteHeader()
		{
			asio::async_write(m_socket, asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
				[this](std::error_code ec, std::size_t length)
				{
					// asio has now sent the bytes - if there was a problem
						// an error would be available...
						if (!ec)
						{
							// ... no error, so check if the message header just sent also
							// has a message body...
							if (m_qMessagesOut.front().body.size() > 0)
							{
								// ...it does, so issue the task to write the body bytes
								WriteBody();
							}
							else
							{
								// ...it didnt, so we are done with this message. Remove it from 
								// the outgoing message queue
								m_qMessagesOut.pop_front();

								// If the queue is not empty, there are more messages to send, so
								// make this happen by issuing the task to send the next header.
								if (!m_qMessagesOut.empty())
								{
									WriteHeader();
								}
							}
						}
						else
						{
							// ...asio failed to write the message, we could analyse why but 
							// for now simply assume the connection has died by closing the
							// socket. When a future attempt to write to this client fails due
							// to the closed socket, it will be tidied up.
							std::cout << "[" << id << "] Write Header Fail.\n";
							m_socket.close();
						}
				});
		}
		
		//ASYNC - Prime context ready to write a message body
		void WriteBody()
		{
			// If this function is called, a header has just been sent, and that header
				// indicated a body existed for this message. Fill a transmission buffer
				// with the body data, and send it!
				asio::async_write(m_socket, asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
					[this](std::error_code ec, std::size_t length)
					{
						if (!ec)
						{
							// Sending was successful, so we are done with the message
							// and remove it from the queue
							m_qMessagesOut.pop_front();

							// If the queue still has messages in it, then issue the task to 
							// send the next messages' header.
							if (!m_qMessagesOut.empty())
							{
								WriteHeader();
							}
						}
						else
						{
							// Sending failed, see WriteHeader() equivalent for description :P
							std::cout << "[" << id << "] Write Body Fail.\n";
							m_socket.close();
						}
					});
		}


		void AddToIncomingMessageQueue()
		{
			if(m_nOwnerType == owner::server)
				m_qMessagesIn.push_back({this->shared_from_this(), m_msgTemporaryIn });
			else
				m_qMessagesIn.push_back({nullptr, m_msgTemporaryIn});

			ReadHeader();
		}

	protected:
		//Each Connection has unique socket to a remote
		asio::ip::tcp::socket m_socket;

		//This context is shared with the whole asio instance
		asio::io_context& m_asioContext;

		// This queue holds all the messages to be sent to the remote side of the connection
		tsqueue<message<T>> m_qMessagesOut;

		//This queue holds all the messages that have been recieved from the remote side of this connection. Note it is a reference as the "owner" of this connection is expected to provide a queue
		tsqueue<owned_message<T>>& m_qMessagesIn;
		message<T> m_msgTemporaryIn;

		//The "owner" decides how some of the connection behaves
		owner m_nOwnerType = owner::server;
		uint32_t id = 0;
	};
}