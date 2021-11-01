#include <QApplication>
#include "ChessCommon.hpp"
#include "clientConnect.hpp"

void* checkForUpdates(void* threadArg);

int main(int argc, char *argv[]){
	
	QApplication app(argc, argv);
	std::string server_IP;
//	if(argc>1) {
//		server_IP = argv[1];
//	} else {
//		std::cout << "Enter IP addr to connect to : ";
//		std::cin >> server_IP;
//	}


	clientConnect dialog;
	QObject::connect(&dialog, &clientConnect::exportIP6, [=](const std::string ip){

		// Initialise the Client Game Object  with args
		// (#serverIP, #serverPort, Affiliation)
		// { true/false : white/black }
		ChessClient* Client = new ChessClient(server_IP, 60000, false);

		// create new thread for this.
		pthread_t clientThread;
		int rc = pthread_create(&clientThread, NULL, checkForUpdates, (void*)Client);
	});

	dialog.show();
	// GUI runs in main thread
	app.exec();

	return 0;
}

void  *checkForUpdates(void *threadArg){
	
	ChessClient* Client = (ChessClient*) threadArg;

	while(1){
//		std::cout<<"waiting\n";
		// If the client is connected
		if (Client->IsConnected())
		{
			// if there is an incoming message in queue 
			if (!Client->Incoming().empty())
			{

				// Fetch the message and parse it
				auto message_packet = Client->Incoming().pop_front();
				auto source = message_packet.remote;
				auto message = message_packet.msg;

				// Debug message
				std::cout<<"Message has arrived :: "<<(int)message.header.id<<std::endl;
				
				switch(message.header.id)
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
							net::message<GameMessage> msg;
							msg.header.id = GameMessage::Game_BeginGame;
							Client->Send(msg);
						}	
						break;


						// Ping from server
					case GameMessage::Ping :
						{
					std::cout<<"Hey!, I'm inside the switch statement\n.";
						//	std::cout << "[" << source->GetID() <<"] Ping Recieved."<<std::endl;
				//for(auto i : message.body)std::cout<<(std::chrono::system_clock::time_point)i;
							Client->Send(message);
						}
						break;


						// Updates opponent's move locally and awaits player's move
					case GameMessage::YourTurn :
						{
						//	std::cout << "[" << source->GetID() <<"] Move Recieved.\n";

							std::string	move = "";
							char temp;
							for(int i = 0; i<4; i++){
								message >> temp;
								move = temp+move;
							}
							std::cout << " Move Recieved."<<move<<std::endl;
							Client->Player.movePiece(translateString(move.substr(0,2)), translateString(move.substr(2,2)), false);
							Client->MyTurn();
						}
						break;


						// Message recieved to start the game
					case GameMessage::Game_BeginGame : {
											    Client->MyTurn();
										     }			// Inform the other player about starting the game
										     break;
				}
			}
		} 
		
		// If the connection does not exist
		// Throw error and exit
		else {
			std::cout << "Server Down\n";
			pthread_exit(NULL);
		}
	}
}
