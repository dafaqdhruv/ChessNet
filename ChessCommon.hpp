#pragma once

#include <iostream>
#include <string>

#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"
#include "game.hpp"

#include "network/NetCommon.h"
#include "network/NetConnection.h"
#include "network/Net_TSQueue.h"
#include "network/NetMessage.h"
#include "network/NetServer.h"
#include "network/NetClient.h"

#define connect_to_port 60000

int local_grid = {
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
	chess::player Player;
	chess::player Opponent;
	bool opponent_active = 0;

	void check();
	void check_mate();
	void piece_moved();
	void piece_died();

public:
	ChessServer(uint16_t nPort, uint64_t validation, bool affiliation = 1) : net::server_interface<GameMessage>(nPort)
	{

		Player(affiliation);
		Opponent(!affiliation);

		Start(validation);
		
	}

	~ChessServer();

public: 
	void Ping()
	{
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Ping;

		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

		msg << timeNow;
		Send(msg);
	}

	void BeginGame(){
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Game_BeginGame;
		msg << affiliation
	}

	void MyTurn()
	{
		// get move input 
		// move piece
		// notify other player about move and wait for his move

		net::message<GameMessage> msg;
		msg.header.id = GameMessage::YourTurn;
		msg << parse_input(&Player, &Opponent, local_grid);
		Send(msg);

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
	virtual bool OnClientDisconnect()
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
		opponent_active = 0;
	}

	virtual bool OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
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
				
				std::string	move;
				msg >> move;

				parse_input(&Opponent, &Player, local_grid, move);
				print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);
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

public:

};












class ChessClient :  public net::client_interface<GameMessage>
{
private:
	chess::player Player;
	chess::player Opponent;
	bool opponent_active = 0;

	void check();
	void check_mate();
	void piece_moved();
	void piece_died();

public:
	ChessClient(string IP, uint16_t nPort, bool affiliation){

		Player(affiliation);
		Opponent(!affiliation);
		Connect(IP, nPort);
	}

	~ChessClient();

public: 
	Ping()
	{
		net::message<GameMessage> msg;
		msg.header.id = GameMessage::Ping;

		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

		msg << timeNow;
		Send(msg);
	}

	// YourTurnNow()
	// {
	// 	net::message<GameMessage> msg;
	// 	msg.header.id = GameMessage::YourTurn;

	// 	std::string out = "";
	// 	out += piece_name();
	// }
	MyTurn()
	{
		// get move input 
		// move piece
		// notify other player about move and wait for his move

		net::message<GameMessage> msg;
		msg.header.id = GameMessage::YourTurn;
		msg << parse_input(&Player, &Opponent, local_grid);
		Send(msg);

		print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);

	}

protected:
	virtual bool OnMessage(std::shared_ptr<net::connection<GameMessage>> client, net::message<GameMessage>& msg)
	{
		switch(msg.header.id)
		{
			case GameMessage::GetStatus : {}			// Return a unique value based on the board's state (Using some intricate funtion) and match them to check if both boards are synced.
			break;

			case GameMessage::Client_Accepted : {

				net::message<GameMessage> msg;
				msg.head.id = GameMessage::Game_BeginGame;
				Send(msg);
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

				parse_input(&Opponent, &Player, local_grid, move);
				print_grid(Player.black_or_white(), nullptr, nullptr, local_grid);
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


