#include "ChessCommon.hpp"


int main(){

	// std::string server_IP = "192.168.29.166";
	std::string server_IP = "127.0.0.1";
	std::cout << "Enter IP addr to connect to : ";
	// std::cin >> server_IP;

	ChessClient Client(server_IP, 60000, false);

	return 0;
}