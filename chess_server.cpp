#include <QApplication>
#include "ChessCommon.hpp"
#include <ctime>


struct args{
    int argc;
    char** argv;
};


void *checkForUpdates(void* threadArg);
void *execThread(void* threadArgs);


int main(int argc, char* argv[]){
    
    //args input = {argc, argv};
    QApplication app(argc, argv);
    ChessServer* Server = new ChessServer(60000,7587303549, true);
    std::cout<<"main thread "<<Server<<std::endl;

    pthread_t updateThread;
    int rc1 = pthread_create(&updateThread, NULL, checkForUpdates, (void*)Server);

    sleep(2);
    return app.exec();
}

void *checkForUpdates(void* threadArg){

    ChessServer* Server = (ChessServer*)threadArg;
    std::cout<<"slave thread "<< Server<<std::endl;
    std::cout<<"Hey a new thread is created\n";
//    ChessServer *Server = new ChessServer(60000,7587303549, true);
    std::cout<<"Hello I am under the water\n";
    while(1){
        Server->Update(-1, false);
    }
    pthread_exit(NULL);
}

void *execThread(void* threadArgs){
    std::cout<<"Hey a new thread is created\n";
    
    args *temp = (args*) threadArgs;

    QApplication *app = new QApplication(temp->argc, temp->argv);
    //QApplication *app  = (QApplication*)threadArgs;    
    app->exec();

    pthread_exit(NULL);

}
