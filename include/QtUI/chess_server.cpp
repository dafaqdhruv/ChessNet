#include <QApplication>
#include "ChessCommon.hpp"

void *checkForUpdates(void* threadArg);
int main(int argc, char* argv[]){
    
    QApplication app(argc, argv);
    ChessServer *Server = new ChessServer(60000,7587303549);
    
    pthread_t serverThread;
    int rc = pthread_create(&serverThread, NULL, checkForUpdates, (void*)Server);

    return  app.exec();
}

void *checkForUpdates(void* threadArg){

    ChessServer* Server = (ChessServer*)threadArg;
    std::cout<<"Hello I am under the water\n";
    while(1){
        Server->Update(-1, false);
    }
    pthread_exit(NULL);
}
