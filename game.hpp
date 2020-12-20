#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;


void give_next_move(){}

void parse_input(player* Player){

	int i;
	char input;

	cout << "choose piece (K Q R B N P) : ";
	cin>>input;


	switch(input){

		case 'K' :
		case 'k' :	Player->print_all_locations(Player->getKing());
					break;
		case 'Q' :
		case 'q' :	Player->print_all_locations(Player->getQueen());
					break;
		case 'R' :
		case 'r' :	Player->print_all_locations(Player->getRook());
					break;
		case 'B' :
		case 'b' :	Player->print_all_locations(Player->getBishop());
					break;
		case 'N' :
		case 'n' :	Player->print_all_locations(Player->getKnight());
					break;
		case 'P' :
		case 'p' :	Player->print_all_locations(Player->getPawn());
					break;
		default : 	cout<<"INVALID.";	
	}	

	
}




bool game(bool affiliation, int weight){


	return 1;
}


