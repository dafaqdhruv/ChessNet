 #pragma once
#include "NetCommon.h"

namespace net{


	//Message header sent at start of all messages.
	//Template allows us to use any user defined message type to use.
	template<typename T>
	struct message_header
	{
		T id;
		uint32_t size = 0;
	};

	template<typename T>
	struct message
	{
		message_header<T> header{};
		std::vector<uint8_t> body;

		size_t size() const
		{
			return sizeof(message_header<T>) + body.size();	
		}

		//Override for std::cout compatibility - produces friendly description of message
		friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
		{
			os << "ID:" << int(msg.header.id) << "Size:" <<msg.header.size;
			return os;			
		}


		//Pushing any POD-like data into message buffer
		template<typename Datatype>
		friend message<T>& operator << (message<T>& msg, const Datatype& data)
		{
			//Check that the type of the data being pushed is copyable 
			static_assert(std::is_standard_layout<Datatype>::value,"Data is too complex to be pushed into vector.");

			//cache current size of vector as this will be the point we insert new data.
			size_t i = msg.body.size();

			//Resize rhe vector by the size of the data being pushed.
			msg.body.resize(msg.body.size() + sizeof(Datatype));

			//Physically copy the data into the newly allocated vector space
			std::memcpy(msg.body.data() + i, &data, sizeof(Datatype));

			//Recalculate the message size
			msg.header.size = msg.size();

			//Return the target message so it can be "chained"
			return msg;
		}


		template<typename Datatype>
		friend message<T>& operator >> (message<T>& msg, Datatype& data)
		{
			//Check that the type of the data being pushed is copyable 
			static_assert(std::is_standard_layout<Datatype>::value,"Data is too complex to be pushed into vector.");

			//cache the location towards the end of the vector where the pulled data starts
			size_t i = msg.body.size() - sizeof(Datatype);

			//Physically copy the data from the vector into the user variable
			std::memcpy(&data, msg.body.data() + i, sizeof(Datatype));

			//Shrink the vector to remove read bytes, and reset end position
			msg.body.resize(i);

			//Recalculate the message size
			msg.header.size = msg.size();

			//Return the target message so it can be "chained"
			return msg;
		}
	};

	template <typename T>
	class connection;

	template<typename T>
	struct owned_message
	{
		std::shared_ptr<connection<T>> remote = nullptr;
		message<T>  msg;

		friend std::ostream& operator << (std::ostream& os, const owned_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
} 