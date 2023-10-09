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

class ChessServer :  public net::server_interface<GameMessage>		// The initialiser
{
	private:
		el::Logger* ServerLogger;
		gameWindow Player;
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
			Player(::chessBoard, affiliation), // init list >> calling func
			ServerLogger(el::Loggers::getLogger("Server"))
		{
			// Start the server with a validation key
			init = true;
			Start(validation);
			Player.show();
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

		// void BeginGame(std::shared_ptr<net::connection<GameMessage>> client) {
		// 	net::message<GameMessage> msg;
		// 	msg.header.id = GameMessage::YourTurn;

		// 	CLOG(INFO, "Server") << "Game Start.";
		// 	client->Send(msg);
		// }

		void MyTurn(std::shared_ptr<net::connection<GameMessage>> client) {
			Player.makeTilesSelectable(true);

			// TODO why call connect every turn??
			QObject::connect(
				&Player,	// sender
				&gameWindow::moved,
				[=] (const char* myMove) {
					net::message<GameMessage> msg;
					msg.header.id = GameMessage::YourTurn;

					for(uint8_t i = 0; i < 4; i++){
						msg << myMove[i];
					}

					client->Send(msg);
					Player.makeTilesSelectable(false);
				}
			);
		}

	protected:
		virtual bool OnClientConnect(std::shared_ptr<net::connection<GameMessage>> client)
		{
			if(opponent_active) return false;

			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Client_Accepted;

			CLOG(INFO, "Server") << "Client connect: " << client->GetID();

			client->Send(msg);
			opponent_active = true;
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
					char move[4];
					for(int8_t i = 3; i>=0; i--) {
						msg >> move[i];
					}

					CLOG(INFO, "Server") << "[" << client->GetID() << "] Opponent move received: " << move;

					Player.movePiece(translateString(&move[0]), translateString(&move[2]), false);
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


class ChessClient :  public net::client_interface<GameMessage>
{
public:
	el::Logger* ClientLogger;
	gameWindow Player;
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
	) : Player(::chessBoard, affiliation),
		ClientLogger(el::Loggers::getLogger("Client"))
	{
		init = true;
		Connect(IP, nPort, 7587303549);

		Player.show();
		QObject::connect(
			&Player,
			&gameWindow::moved,
			[=] (const char* move){
				net::message<GameMessage> msg;
				msg.header.id = GameMessage::YourTurn;

				for(uint8_t i = 0; i<4; i++){
					msg << move[i];
				}
				Send(msg);

				Player.makeTilesSelectable(false);
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
		Player.makeTilesSelectable(true);
	}


protected:
	// What to do when a message is recieved
	//
//		virtual void OnMessage( std::shared_ptr< net::connection<GameMessage> > client, net::message< GameMessage >& msg)
//		{
//			switch(msg.header.id)
//			{
//				// Return a unique value based on the board's state
//				// Like a parity function
//				// and match them to check if both boards are in sync.
//				// case GameMessage::GetStatus :
//				// {}
//				// break;
//
//
//				// Server has accepted the client
//				// Game may begin
//				case GameMessage::Client_Accepted :
//					{
//						std::cout<<"I HVE BEEN ACCEpTED\n";
//						net::message<GameMessage> msg;
//						msg.header.id = GameMessage::Game_BeginGame;
//						client->Send(msg);
//					}
//					break;
//
//
//					// Ping from server
//				case GameMessage::Ping :
//					{
//						std::cout << "[" << client->GetID() <<"] Ping Recieved.\n";
//						client->Send(msg);
//					}
//					break;
//
//
//					// Updates opponent's move locally and awaits player's move
//				case GameMessage::YourTurn :
//					{
//						std::cout << "[" << client->GetID() <<"] Move Recieved.\n";
//
//						std::string	move;
//						msg >> move;
//						Player.movePiece(translateString(move.substr(0,2)), translateString(move.substr(2,2)), false);
//						MyTurn();
//					}
//					break;
//
//
//					// Message recieved to start the game
//				case GameMessage::Game_BeginGame : {
//
//									     }			// Inform the other player about starting the game
//									     break;
//
//
//									     // Message recieved to end the game
//									     // display the result and exit
////				case GameMessage::Game_EndGame :
////									     {}
////									     break;
////
////
////									     // Updates opponent's move locally
////									     // ??  DUPLICATE ??
////				case GameMessage::Game_UpdatePlayer :
////									     {
////										     string moved;
////										     msg >> moved;
////									     }
////									     break;
//			}
//		}
};
