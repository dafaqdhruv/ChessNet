#include <QApplication>

#include "../include/ChessCommon.hpp"
#include "../include/clientConnect.hpp"

INITIALIZE_EASYLOGGINGPP

void* checkForUpdates(void* threadArg);

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	ClientConnect dialog;
	QObject::connect(
		&dialog,
		&ClientConnect::exportIP6,
		[=](const std::string SERVER_IP){
			ChessClient* Client = new ChessClient(SERVER_IP, DEFAULT_PORT, BLACK);

			CLOG(INFO, "Client") << "Connection established to: " + SERVER_IP;

			pthread_t clientThread;
			int rc = pthread_create(&clientThread, NULL, checkForUpdates, (void*)Client);
		}
	);

	dialog.show();
	app.exec();

	return 0;
}

void  *checkForUpdates(void *threadArg){

	ChessClient* Client = (ChessClient*) threadArg;

	while(1){
		if (!Client -> IsConnected())
		{
			CLOG(FATAL, "Client") << "Server Down";
			pthread_exit(NULL);
		}

		if (!Client->Incoming().empty())
		{
			auto message_packet = Client->Incoming().pop_front();
			auto source = message_packet.remote;
			auto message = message_packet.msg;

			CLOG(INFO, "Client") <<"Message received: "<<(int)message.header.id;

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
				Client->Send(msg);
			}
			break;

			case GameMessage::Ping : {
				CLOG(INFO, "Client") << "Server Ping. Pinging back.";
				Client->Send(message);
			}
			break;

			case GameMessage::YourTurn : {
				bool is_my_move = false;


				char move[4];
				for(int8_t i = 3; i>=0; i--){
					message >> move[i];
				}

				CLOG(INFO, "Client") << "Opponent move: " << std::string(move);

				Client -> Player.movePiece(translateString(&move[0]), translateString(&move[2]), is_my_move);
				Client -> MyTurn();
			}
			break;
			}
		}
	}
}
