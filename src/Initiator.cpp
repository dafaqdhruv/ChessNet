#include "../include/ChessCommon.hpp"


bool initialise_connection()


int main(){

	// ChessClient Playerboi;
	uint32_t passcode = 0;
	char temp = '0';

	bool game_running = true;


	// Ask If player is initiator or responder

		//A. 	Create an open connection and wait for player
		//B.	Check if game exists Then Connect and start game.

	cout<<"1. Create Connection and wait for opponent?\n";
	cout<<"2. Connect to a game and start playing?\n";
	cin>>client_type;


	if(client_type == 1){
		
		// create a passcode to validate connection
		cout << "Create a 4-digit passcode to validate opponent : ";
		for(int i = 0; i<4 && (temp>47 && temp<58); i++){
		    temp = getchar();
		    passcode = passcode *10 + (c-48);
		}

		// initialise and wait for connection
		auto Playerboi = ChessServer(connect_to_port, 1);		
		Playerboi.Start(passcode);

		// if succeeds, start game
		while(game_running) 
		{
			
		}

	}
	else if(client_type == 2){

		string ip_addr;
		// get initiator IP, attempt connection with passcode
		cout << "Enter IP to connect to : ";
		cin >> ip_addr;

		Playerboi.Connect(ip_addr, connect_to_port)

		// if connection succeeds, start game

	}



	return 0;
}