#include <QApplication>

#include "../include/ChessCommon.hpp"
#include "../include/commonWindows.hpp"

INITIALIZE_EASYLOGGINGPP

void  *checkServerForUpdates(void *threadArg){
	ChessServer* Server = (ChessServer*) threadArg;

	while(1){
		Server->Update();
	}
}

void  *checkClientForUpdates(void *threadArg){
	ChessClient* Client = (ChessClient*) threadArg;

	while(1){
		Client->Update();
	}
}

void CreateNewGame(){
    ChessServer* Server = new ChessServer(DEFAULT_PORT,7587303549, WHITE);

    pthread_t serverThread;
    int rc = pthread_create(&serverThread, NULL, checkServerForUpdates, (void*)Server);
}

void ConnectToGame(std::string ip){
    ChessClient* Client = new ChessClient(ip, DEFAULT_PORT, BLACK);

    pthread_t clientThread;
    int rc = pthread_create(&clientThread, NULL, checkClientForUpdates, (void*)Client);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    uint8_t x = 0;
    GameDialog dialog;

    QObject::connect(
        &dialog,
        &GameDialog::medium,
        [=](const bool makeServer) {
            if(makeServer){
                CreateNewGame();
            } else{
                ClientConnect getIpDialog;
                QObject::connect(
                    &getIpDialog,
                    &ClientConnect::exportIP6,
                    [](const std::string serverIP){
                        ConnectToGame(serverIP);
                    }
                );
                getIpDialog.exec();
            }
        }
    );

    dialog.show();
    app.exec();

    sleep(2);
    return 0;
}
