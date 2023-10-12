#pragma once

#include <iostream>
#include <string>

#include "board.hpp"
#include "gameTile.hpp"
#include "gameWindow.hpp"

#include "easylogging++.h"

#include "NetTranslator.h"
#include "network/NetCommon.h"
#include "network/NetConnection.h"
#include "network/Net_TSQueue.h"
#include "network/NetMessage.h"
#include "network/NetServer.h"
#include "network/NetClient.h"

static const int DEFAULT_PORT = 60000;

int local_grid[8][8] = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

static const bool BLACK = false;
static const bool WHITE = true;

class ChessServer :  public net::server_interface<GameMessage>, public GameWindow	// The initialiser
{
	private:
		el::Logger* ServerLogger;

		std::shared_ptr<net::connection<GameMessage>> opponent;
		bool opponent_active = 0;
		bool init;

		void check(); // alert when check
		void check_mate(); // alert when checkmate
		void piece_moved(); // alert when piece moved or dies you get the idea
		void piece_died();

	public:

		ChessServer(
			uint16_t nPort,
			uint64_t validation,
			bool affiliation = WHITE
		) : net::server_interface< GameMessage >(nPort),
			GameWindow(::chessBoard, affiliation), // init list >> calling func
			ServerLogger(el::Loggers::getLogger("Server"))
		{
			// Start the server with a validation key
			init = true;
			opponent = nullptr;

			Start(validation);
			this->show();
		}

		~ChessServer(){}

	public:
		void Ping(std::shared_ptr<net::connection<GameMessage>> client) {
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Ping;

			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
			msg << timeNow;

			client->Send(msg);
		}

		void MyTurn(std::shared_ptr<net::connection<GameMessage>> client) {
			this->makeTilesSelectable(true);
		}

	protected:
		virtual bool OnClientConnect(std::shared_ptr<net::connection<GameMessage>> client)
		{
			if(opponent_active) return false;
			opponent = client;
			opponent_active = true;

			QObject::connect(
				this,
				&GameWindow::moved,
				[=] (const std::string myMove) {
					net::message<GameMessage> msg;
					msg.header.id = GameMessage::YourTurn;

					for(uint8_t i = 0; i < 4; i++){
						msg << myMove[i];
					}

					client->Send(msg);
					this->makeTilesSelectable(false);
				}
			);

			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Client_Accepted;

			CLOG(INFO, "Server") << "Client connect: " << client->GetID();

			client->Send(msg);
			return true;
		}

		virtual void OnClientDisconnect(std::shared_ptr<net::connection<GameMessage>> client)
		{
			CLOG(INFO, "Server") << "Client Disconnect: " << client->GetID();
			opponent_active = false;
		}

		virtual void OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
		{
			switch(msg.header.id)
			{
				case GameMessage::GetStatus :
				{
					CLOG(INFO, "Server") << "[TODO]Opponent request status. Sending board info.";
				}
				break;

				case GameMessage::Ping :
				{
					CLOG(INFO, "Server") << "["<<client->GetID()<<"] Client Pinged back.";
				}
				break;

				case GameMessage::YourTurn :
				{
					std::string move = "";
					char c;
					for(int8_t i = 0; i < 4; i++) {
						msg >> c;
						move = c + move;
					}

					CLOG(INFO, "Server") << "[" << client->GetID() << "] Opponent move received: " << move;

					this->movePiece(translateString(move.substr(0,2)), translateString(move.substr(2,2)), false);
					this->GameWindow::isKingsUnsafeFrom(move.substr(2,2));

					MyTurn(client);
				}
				break;

				case GameMessage::Game_BeginGame :
				{
					CLOG(INFO, "Server") << "Client request begin game. Server's turn.";
					Ping(client);
					MyTurn(client);
				}
				break;


				// Game is over. Display result and wait for exit / new game
				// case GameMessage::Game_EndGame :
				// {}
				// break;

				// Update the local board according to opponent's move
				// case GameMessage::Game_UpdatePlayer :
				// {
				// 	// string moved;
				// 	// msg >> moved;
				// }
				// break;
			}
		}


};


class ChessClient :  public net::client_interface<GameMessage>, public GameWindow
{
private:
	el::Logger* ClientLogger;

	bool opponent_active = 0;
	bool init;

	void check();
	void check_mate();
	void piece_moved();
	void piece_died();

public:
	ChessClient(
		std::string IP,
		uint16_t nPort,
		bool affiliation
	) : GameWindow(::chessBoard, affiliation),
		ClientLogger(el::Loggers::getLogger("Client"))
	{
		init = true;
		Connect(IP, nPort, 7587303549);

		this->show();
		QObject::connect(
			this,
			&GameWindow::moved,
			[=] (const std::string move){
				net::message<GameMessage> msg;
				msg.header.id = GameMessage::YourTurn;

				CLOG(INFO, "Client") << "My move" << move;

				for(uint8_t i = 0; i < 4; i++){
					msg << move[i];
				}

				Send(msg);
				this->makeTilesSelectable(false);
			}
		);
	}

	~ChessClient(){}
	// virtual ~ChessClient(){}
	// VIRTUAL BECAUSE WITHOUT IT GCC GIVES LINKER ERROR  [undef reference to vtable for ~client()]
	// yo how did I figure this out??!

public:
	void Ping()
	{
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Ping;

		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
		msg << timeNow;

		Send(msg);
	}

	void MyTurn()
	{
		this->makeTilesSelectable(true);
	}

protected:
	virtual void OnMessage(std::shared_ptr< net::connection<GameMessage> > client, net::message< GameMessage >& message)
	{
		switch(message.header.id)
		{
		case GameMessage::GetStatus : {
			CLOG(INFO, "Client") << "Opponent request status. Sending board info.";
		}
		break;

		case GameMessage::Client_Accepted :	{
			CLOG(INFO, "Client") << "Server accept. Requesting game start.";

			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Game_BeginGame;
			Send(msg);
		}
		break;

		case GameMessage::Ping : {
			CLOG(INFO, "Client") << "Server Ping. Pinging back.";
			Send(message);
		}
		break;

		case GameMessage::YourTurn : {
			bool is_my_move = false;

			char tmp[4];

			for(int8_t i = 3; i>=0; i--){
				message >> tmp[i];
			}

			std::string move = "";
			move += tmp[0];
			move += tmp[1];
			move += tmp[2];
			move += tmp[3];

			CLOG(INFO, "Client") << "Opponent move: " << move;

			this->movePiece(translateString(move.substr(0,2)), translateString(move.substr(2,2)), is_my_move);
			this->GameWindow::isKingsUnsafeFrom(move.substr(2,2));

			MyTurn();
		}
		break;
		}
	}
};
