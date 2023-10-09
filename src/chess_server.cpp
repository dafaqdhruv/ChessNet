#include <ctime>
#include <QApplication>

#include "../include/ChessCommon.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    ChessServer* Server = new ChessServer(DEFAULT_PORT,7587303549, WHITE);

    std::thread Serve([=](){
        while(1){
            Server->Update();
        }
    });

    sleep(2); // wait for processes to exit gracefully
    return app.exec();
}
