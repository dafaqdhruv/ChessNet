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
	player Player;
	player Opponent;
	bool opponent_active = 0;

	void check();
	void check_mate();
	void piece_moved();
	void piece_died();

public:
	ChessServer(uint16_t nPort, uint64_t validation, bool affiliation = true) : net::server_interface<GameMessage>(nPort), Player(affiliation), Opponent(!affiliation)
	{

		// Player(affiliation);
		// Opponent(!affiliation);

		// Player = player(true);
		// Opponent = player(false);


		Start(validation);	
		if(affiliation)
			print_grid(true, &Player, &Opponent, local_grid);
		else
			print_grid(false,  &Opponent, &Player, local_grid);
	}

	~ChessServer(){}

public: 
	void Ping(std::shared_ptr<net::connection<GameMessage>> client)
	{
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Ping;

		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

		msg << timeNow;
		client->Send(msg);
	}

	void BeginGame(std::shared_ptr<net::connection<GameMessage>> client){
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Game_BeginGame;
		msg << Player.black_or_white();
		client->Send(msg);
	}

	void MyTurn(std::shared_ptr<net::connection<GameMessage>> client)
	{
		// get move input 
		// move piece
		// notify other player about move and wait for his move

		net::message<GameMessage> msg;
		msg.header.id = GameMessage::YourTurn;

		auto temp = parse_input(&Player, &Opponent, local_grid);

		std::cout<<"Server SIDE ::\n";
		std::cout<<"The string is "<<temp;

		msg << (char)temp[0];
		msg << (char)temp[1];
		msg << (char)temp[2];
		msg << (char)temp[3];
		msg << (char)temp[4];

		client->Send(msg);

		for( auto i = 0; i<msg.body.size(); i++){
			std::cout<<msg.body[i];
		}

		print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);

	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<net::connection<GameMessage>> client)
	{
		if(!opponent_active){
			net::message<GameMessage> msg;
			msg.header.id = GameMessage::Client_Accepted;
			client->Send(msg);
			opponent_active = 1;
			return true;
		}
		else return false;
	}
	virtual void OnClientDisconnect(std::shared_ptr<net::connection<GameMessage>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
		opponent_active = 0;
	}

	virtual void OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
	{
		switch(msg.header.id)
		{
			case GameMessage::GetStatus : {}			// Return a unique value based on the board's state (Using some intricate funtion) and match them to check if both boards are synced.
			break;

			case GameMessage::Ping :
			{
				std::cout << "[" << client->GetID() <<"] Ping Recieved.\n";
				client->Send(msg);
			}			// Simply ping the other player
			break;

			case GameMessage::YourTurn :
			{
				std::cout << "[" << client->GetID() <<"] Move Recieved.\n";
				cout<<(int)msg.header.id<<endl;
				cout<<msg.size()<<endl;
				std::string move = "";

				for( int i = 0; i<msg.body.size(); i++){
					cout<<msg.body[i];
					move += msg.body[i];
				}
								
				
				std::cout<<"CLIENT SENT ME THIS : "<<move<<endl;
				parse_input(&Opponent, &Player, local_grid, move);
				print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);
				MyTurn(client);
			}
			break;
	
			case GameMessage::Game_BeginGame : {
				MyTurn(client);
			}			// Inform the other player about starting the game
			break;

			// case GameMessage::Game_EndGame : {}				// Game is over. Display result and wait for exit / new game
			// break;

			// case GameMessage::Game_UpdatePlayer :
			// {
			// 	// string moved;
			// 	// msg >> moved;
			// }		// Update the local board according to opponent's move
			// break;	
		}
	}

public:

};












class ChessClient :  public net::client_interface<GameMessage>
{
private:
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

		Connect(IP, nPort, 7587303549);
		if(affiliation)
			print_grid(true, &Player, &Opponent, local_grid);
		else
			print_grid(false,  &Opponent, &Player, local_grid);

	}

	virtual ~ChessClient(){}			// VIRTUAL BECAUSE WITHOUT IT GCC GIVES LINKER ERROR  [undef reference to vtable for ~client()]

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
		// get move input 
		// move piece
		// notify other player about move and wait for his move

		net::message<GameMessage> msg;
		msg.header.id = GameMessage::YourTurn;


		auto temp = parse_input(&Player, &Opponent, local_grid);
		
		std::cout<<"CLIENT SIDE ::\n";
		std::cout<<"The string is ::::: "<<temp<<endl;

		msg << (char)temp[0];
		msg << (char)temp[1];
		msg << (char)temp[2];
		msg << (char)temp[3];
		msg << (char)temp[4];

		Send(msg);

		std::cout<<"CLIENT HAS SENT THE MESSAGE ::\n";
		std::cout<<(int)msg.header.id<<"\n";
		
		cout<<msg.size()<<endl;
		for( auto i = 0; i<msg.body.size(); i++){
			std::cout<<msg.body[i];
		}
		std::cout<<endl;
		// cout<<(std::string)msg.body<<endl;

		print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);

	}

	
	void do_this(string move){

		parse_input(&Opponent, &Player, local_grid, move);
		print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);	
	}

protected:
	virtual void OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
	{
		switch(msg.header.id)
		{
			// case GameMessage::GetStatus : {}			// Return a unique value based on the board's state (Using some intricate funtion) and match them to check if both boards are synced.
			// break;

			case GameMessage::Client_Accepted : {

				// net::message<GameMessage> msg;
				// msg.header.id = GameMessage::Game_BeginGame;
				// Send(msg);
				std::cout<<"I HVE BEEN ACCEpTED\n";
				MyTurn();
			}			// client is accepted. Game may begin.
			break;

			case GameMessage::Ping :
			{
				std::cout << "[" << client->GetID() <<"] Ping Recieved.\n";
				client->Send(msg);
			}			// Simply ping the other player
			break;

			case GameMessage::YourTurn :
			{
				std::cout << "[" << client->GetID() <<"] Move Recieved.\n";
				
				std::string	move;
				msg >> move;
				do_this(move);
				MyTurn();
			}
			break;
	
			case GameMessage::Game_BeginGame : {
				MyTurn();
			}			// Inform the other player about starting the game
			break;

			case GameMessage::Game_EndGame : {}				// Game is over. Display result and wait for exit / new game
			break;

			case GameMessage::Game_UpdatePlayer :
			{
				string moved;
				msg >> moved;
			}		// Update the local board according to opponent's move
			break;	
		}
	}

};


