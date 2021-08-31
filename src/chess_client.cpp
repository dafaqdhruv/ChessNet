#include "../include/ChessCommon.hpp"


int main(int argc, char *argv[]){

	std::string server_IP;

	if(argc>1) {
		server_IP = argv[1];
	} else {
		std::cout << "Enter IP addr to connect to : ";
		std::cin >> server_IP;
	}


	// Initialise the Client Game Object  with args
	// (#serverIP, #serverPort, Affiliation)
	// { true/false : white/black }
	ChessClient Client(server_IP, 60000, false);


	// While game runs
	while(1){
	
		// If the client is connected
		if (Client.IsConnected())
		{
			// if there is an incoming message in queue 
			if (!Client.Incoming().empty())
			{

				// Fetch the message and parse it
				auto message_packet = Client.Incoming().pop_front();
				auto source = message_packet.remote;
				auto message = message_packet.msg;

				// Debug message
				cout<<"Message has arrived :: "<<(int)message.header.id<<endl;
				

				switch (message.header.id)
				{

					// Return a unique value based on the board's state (Using some intricate funtion) and match them to check if both boards are synced.
					// case GameMessage::GetStatus : 
					// {}			
					// break;
					
					
					// case is accepted and verified by the server. 
					// The game may begin
					case GameMessage::Client_Accepted : 
					{
						net::message<GameMessage> msg;
						msg.header.id = GameMessage::Game_BeginGame;
						Client.Send(msg);
						// Client.MyTurn();
					}
					break;
					
					
					// Ping message from the server
					// sends back the message.
					case GameMessage::Ping :
					{
						// std::cout << "[" << source->GetID() <<"] Ping Recieved.\n";
						source->Send(message);
					}
					break;

					
					// Message with Opponent's move
					// parses the contents and processes accordingly
					case GameMessage::YourTurn :
					{
						std::string move = "";
						for( auto i : message.body ){
							cout<<i;
							move += i;
						}
								
						// Debug messages
						// std::cout << "[" << source->GetID() <<"] Move Recieved.\n";
						//cout<<(int)message.header.id<<endl;
						//cout<<message.size()<<endl;
						cout<<"Server sent me this : "<<move<<endl;

						// updates player's board with opponent's move
						Client.do_this(move);
						// time for player to make a move 
						Client.MyTurn();
					}
					break;
		
					
					// Opponent has instructed the player to start the game
					case GameMessage::Game_BeginGame : 
					{
						Client.MyTurn();
					}
					break;
					

					// Game is over. Display result and wait for exit / new game
					// case GameMessage::Game_EndGame : 
					// {}	
					// break;

				}
			}
		} 
		
		// If the connection does not exist
		// Throw error and exit
		else {
			cout << "Server Down\n";
			return -1;
		}
	}

	return 0;

}
