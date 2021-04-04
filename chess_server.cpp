#include "ChessCommon.hpp"


int main(){

	// std::string server_IP = "192.168.29.166";
	// std::string server_IP = "127.0.0.1";
	// std::cout << "Enter IP addr to connect to : ";
	// std::cin >> server_IP;

	ChessServer Server(60000, 7587303549);

	while(1){
		Server.Update(-1, true);
	}
	return 0;
}	