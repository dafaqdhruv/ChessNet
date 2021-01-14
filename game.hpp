#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;


void give_next_move(){}

void parse_input(player* Player, int grid[8][8]){

	int i;
	char input;

	cout << "choose piece (K Q R B N P) : ";
	cin>>input;


	switch(input){

		case 'K' :
		case 'k' :	Player->print_all_locations(Player->getKing(), grid);
					break;
		case 'Q' :
		case 'q' :	Player->print_all_locations(Player->getQueen(), grid);
					break;
		case 'R' :
		case 'r' :	Player->print_all_locations(Player->getRook(), grid);
					break;
		case 'B' :
		case 'b' :	Player->print_all_locations(Player->getBishop(), grid);
					break;
		case 'N' :
		case 'n' :	Player->print_all_locations(Player->getKnight(), grid);
					break;
		case 'P' :
		case 'p' :	Player->print_all_locations(Player->getPawn(), grid);
					break;
		default : 	cout<<"INVALID.";	
	}	

	
}




bool game(bool affiliation, int weight){


	return 1;
}


