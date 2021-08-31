#pragma once

#include <iostream>
#include <string>

#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"
#include "game.hpp"

#include "NetTranslator.h"

#include "network/NetCommon.h"
#include "network/NetConnection.h"
#include "network/Net_TSQueue.h"
#include "network/NetMessage.h"
#include "network/NetServer.h"
#include "network/NetClient.h"

#define connect_to_port 60000

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

class ChessServer :  public net::server_interface<GameMessage>		// The initialiser
{
	private:

		// Each game object stores opponent's game state.
		// hence the two player objects
		//
		player Player;
		player Opponent;
		bool opponent_active = 0;

		void check();
		void check_mate();
		void piece_moved();
		void piece_died();

	public:

		ChessServer(uint16_t nPort, uint64_t validation, bool affiliation = true) 
					: net::server_interface< GameMessage >(nPort), Player(affiliation), Opponent(!affiliation)
		{

			// Player(affiliation);
			// Opponent(!affiliation);
			// Player = player(true);
			// Opponent = player(false);

	
			// Start the server with a validation key
			Start(validation);
	
			// Prints the board accordingly
			if(affiliation)
				print_grid(true, &Player, &Opponent, local_grid);
			else
				print_grid(false,  &Opponent, &Player, local_grid);
		}

		~ChessServer(){}

	public:

		// Pings client
		//
		void Ping(std::shared_ptr<net::connection<GameMessage>> client)
		{
			// Creates data packet
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Ping;
	
			// Init with creation time
			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

			msg << timeNow;
			client->Send(msg);
		}


		// Server Starts a game 
		//
		void BeginGame(std::shared_ptr<net::connection<GameMessage>> client)
		{
			// Create data packet
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Game_BeginGame;

			// Tells opponent if player(server) has chosen black/white
			msg << Player.black_or_white();
			client->Send(msg);
		}


		// Handles player move
		//
		void MyTurn(std::shared_ptr<net::connection<GameMessage>> client)
		{
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::YourTurn;

			// Gets console input
			auto temp = parse_input(&Player, &Opponent, local_grid);
	

			// Message body structure
			// { T, x1,  y1, x2, y2 }
			// T  : Piece type {Pawn/Rook/Bishop/Knight/Queen/King}
			// x1&2 : initial & final column of piece
			// y1&2 : initial & final row of piece
			msg << (char)temp[0]; 		// T
			msg << (char)temp[1];		// x1
			msg << (char)temp[2];		// y1
			msg << (char)temp[3];		// x2
			msg << (char)temp[4];		// y2

			client->Send(msg);

			// Debug messages
			std::cout<<"Server SIDE ::\n";
			std::cout<<"The string is "<<temp;
			for( auto i = msg.body){
				cout<<i;
			}cout<<endl;
		
			print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);

		}

	protected:

		// Stuff to do when a client is connected
		//
		virtual bool OnClientConnect(std::shared_ptr<net::connection<GameMessage>> client)
		{	
			// if there is not an ongoing game 
			// (server is ready to play)
			if(!opponent_active)
			{
				net::message<GameMessage> msg;
				msg.header.id = GameMessage::Client_Accepted;
				client->Send(msg);
				opponent_active = true;
				return true;
			}
			else return false;
		}


		// When a client disconnects, stop the game
		//
		virtual void OnClientDisconnect(std::shared_ptr<net::connection<GameMessage>> client)
		{
			std::cout << "Removing client [" << client->GetID() << "]\n";
			opponent_active = 0;
		}

		
		// When a message is recieved
		//
		virtual void OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
		{
			switch(msg.header.id)
			{
				// Return a unique value based on the board's state 
				// like a parity function
				// and match them to check if both boards are in sync
				// case GameMessage::GetStatus : 
				// {}
				// break;

				
				// Reply to a Ping
				case GameMessage::Ping :
				{
					std::cout << "[" << client->GetID() <<"] Ping Recieved.\n";
					client->Send(msg);
				}
				break;


				// Handles player's move
				case GameMessage::YourTurn :
				{
					std::cout << "[" << client->GetID() <<"] Move Recieved.\n";
				
					std::string move = "";

					for( int i = 0; i<msg.body.size(); i++){
						cout<<msg.body[i];
						move += msg.body[i];
					}
									
					//debug message	
					//	std::cout<<"CLIENT SENT ME THIS : "<<move<<endl;
					//	cout<<(int)msg.header.id<<endl;
					//	cout<<msg.size()<<endl;

					// parse console input
					parse_input(&Opponent, &Player, local_grid, move);
				
					print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);

					MyTurn(client);
				}
				break;
		

				// Message recieved to start the game
				case GameMessage::Game_BeginGame : 
				{
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
	private:

		// Each game object stores opponent's game state.
		// hence the two player objects
		player Player;
		player Opponent;
		bool opponent_active = 0;
		
		void check();
		void check_mate();
		void piece_moved();
		void piece_died();


	public:


		ChessClient(string IP, uint16_t nPort, bool affiliation) : Player(affiliation), Opponent(!affiliation)
		{
			// Player(affiliation);
			// Opponent(!affiliation);
			// Player = player(false);
			// Opponent = player(true);

			
			// Establish a connection to the given IP & Port using a validation key
			Connect(IP, nPort, 7587303549);

			if(affiliation)
				print_grid(true, &Player, &Opponent, local_grid);
			else
				print_grid(false,  &Opponent, &Player, local_grid);

		}

		virtual ~ChessClient(){}			// VIRTUAL BECAUSE WITHOUT IT GCC GIVES LINKER ERROR  [undef reference to vtable for ~client()]
									// yo how did I figure this out??!

	public: 
		
		// Send a ping message up the connection
		//
		void Ping()
		{	
			// Create message packet
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Ping;
			
			// Initialise with time of creation
			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
			
			msg << timeNow;
			Send(msg);
		}
	

		// Handles player move
		//
		void MyTurn()
		{
			// Create message packet
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::YourTurn;
			
			// Parse console Input
			auto temp = parse_input(&Player, &Opponent, local_grid);
			
			// Debug messages
			cout<<"CLIENT SIDE ::\n";
			cout<<"The string is ====> "<<temp<<endl;

			
			// Message body structure
			// { T, x1,  y1, x2, y2 }
			// T  : Piece type {Pawn/Rook/Bishop/Knight/Queen/King}
			// x1&2 : initial & final column of piece
			// y1&2 : initial & final row of piece
			msg << (char)temp[0]; 		// T
			msg << (char)temp[1];		// x1
			msg << (char)temp[2];		// y1
			msg << (char)temp[3];		// x2
			msg << (char)temp[4];		// y2

			Send(msg);
			
			// Update player's board 
			print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);
	

			// Debug messages
			//cout<<"CLIENT HAS SENT THE MESSAGE ::\n";
			//for( auto i = 0; i<msg.body.size(); i++){
			//	std::cout<<msg.body[i];
			//}
			//std::cout<<endl;

		}

		
		// this is temporary ??
		//
		void do_this(string move){

			parse_input(&Opponent, &Player, local_grid, move);
			print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);	
		}

	protected:
		

		// What to do when a message is recieved
		//
		virtual void OnMessage( std::shared_ptr< net::connection<GameMessage> > client, net::message< GameMessage >& msg)
		{
			switch(msg.header.id)
			{
				// Return a unique value based on the board's state 
				// Like a parity function 
				// and match them to check if both boards are in sync.
				// case GameMessage::GetStatus : 
				// {}	
				// break;
		

				// Server has accepted the client
				// Game may begin
				case GameMessage::Client_Accepted : 
				{
					std::cout<<"I HVE BEEN ACCEpTED\n";
					MyTurn();
				}	
				break;
			

				// Ping from server
				case GameMessage::Ping :
				{
					std::cout << "[" << client->GetID() <<"] Ping Recieved.\n";
					client->Send(msg);
				}
				break;

				
				// Updates opponent's move locally and awaits player's move
				case GameMessage::YourTurn :
				{
					std::cout << "[" << client->GetID() <<"] Move Recieved.\n";
					
					std::string	move;
					msg >> move;
					do_this(move);
					MyTurn();
				}
				break;
	
				
				// Message recieved to start the game
				case GameMessage::Game_BeginGame : {
					MyTurn();
				}			// Inform the other player about starting the game
				break;

				
				// Message recieved to end the game
				// display the result and exit
				case GameMessage::Game_EndGame : 
				{}
				break;

				
				// Updates opponent's move locally 
				// ??  DUPLICATE ??
				case GameMessage::Game_UpdatePlayer :
				{
					string moved;
					msg >> moved;
				}
				break;	
			}
		}
};


