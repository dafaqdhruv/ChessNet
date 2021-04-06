#include "../include/ChessCommon.hpp"


int main(int argc, char *argv[]){

	// std::string server_IP = "192.168.29.166";
	std::string server_IP;
	// if(argc>1) server_IP = argv[1];
	// else server_IP = "127.0.0.1";

	std::cout << "Enter IP addr to connect to : ";
	std::cin >> server_IP;

	ChessClient Client(server_IP, 60000, false);



	while(1){

		if (Client.IsConnected())
		{
			if (!Client.Incoming().empty())
			{


				auto message_packet = Client.Incoming().pop_front();
				auto source = message_packet.remote;
				auto message = message_packet.msg;


				cout<<"MEssafe ahas arrived :: "<<(int)message.header.id<<endl;
				switch (message.header.id)
				{
					// case GameMessage::GetStatus : {}			// Return a unique value based on the board's state (Using some intricate funtion) and match them to check if both boards are synced.
					// break;

					case GameMessage::Client_Accepted : {

						net::message<GameMessage> msg;
						msg.header.id = GameMessage::Game_BeginGame;
						Client.Send(msg);
						// std::cout<<"CLIENTE TURN\n";
						// Client.MyTurn();
					}			// client is accepted. Game may begin.
					break;

					case GameMessage::Ping :
					{
						// std::cout << "[" << source->GetID() <<"] Ping Recieved.\n";
						source->Send(message);
					}			// Simply ping the other player
					break;

					case GameMessage::YourTurn :
					{
						// std::cout << "[" << source->GetID() <<"] Move Recieved.\n";
						cout<<(int)message.header.id<<endl;
						cout<<message.size()<<endl;
						
						std::string move = "";
						for( int i = 0; i<message.body.size(); i++){
							cout<<message.body[i];
							move += message.body[i];
						}
								
						std::cout<<"SERVER SENT ME THIS : "<<move<<endl;

						Client.do_this(move);
						Client.MyTurn();
					}
					break;
			
					case GameMessage::Game_BeginGame : {
						Client.MyTurn();
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
		}
		else
		{
			std::cout << "Server Down\n";
			return -1;
		}
	}
	return 0;
}