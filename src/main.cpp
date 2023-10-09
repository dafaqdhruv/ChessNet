#include <QApplication>

#include "../include/commonWindows.hpp"


void boom(){
  setupServer setupServerWindow;
  int scrambler;
  QObject::connect(&setupServerWindow, &setupServer::exportScrambler, [&scrambler](const int ret){scrambler = ret;});
  setupServerWindow.show();
  std::cout<<"Yo i just made a server type player "<<scrambler<<"\n";
  //        serverTypePlayer player(scrambler);
  //      player.show();
}
void baam(){
  ClientConnect clientConnectWin;
  std::string IP6;
  QObject::connect(&ClientConnectWin, &ClientConnect::exportIP6, [&IP6](const std::string ret){IP6 = ret;
  std::cout<<"Yo i just made a client type player "<<IP6<<"\n";
      });
  clientConnectWin.show();
  //        clientTypePlayer player(IP6);
  //      player.show();
}






int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  askMediumDialog medium;
  bool makeServer = false;
  medium.show();

  QObject::connect(&medium, &askMediumDialog::medium,[&makeServer,&medium](const bool ret){
      makeServer = ret;    //    medium.show();
//      medium.accept();
      if(makeServer){
      int ok;
      int text = QInputDialog::getInt(nullptr, "Get Scrambler",
          "Scrambler val : ",0, 1000,9999);
      std::cout<<text<<std::endl;

      boom();
      } else {

      baam();
      }
      });


  return app.exec();
}
