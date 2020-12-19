#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"
#include "player.hpp"

using namespace std;

#define cls cout<<"\033[2J"<<"\n";



int board[8][8] = {
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0}
					};




int piece_at_pos(int num){

	switch(num){

		case 4 :	return 1;

		case 3 :	return 2;

		case 0 :
		case 7 :	return 3;
		
		case 1 :
		case 6 :	return 4;

		case 2 :
		case 5 :	return 5;

	}
}

string piece_name(int type){

	switch(type){
		case  0 : 	return " __ ";
		case  6	:
		case -6	:	return "Pawn";
		case  5	:
		case -5	:	return "Bish";
		case  4	:
		case -4	:	return "Kni8";
		case  3	:
		case -3	:	return "Rook";
		case  2	:
		case -2	:	return "Quen";
		case  1	:
		case -1	:	return "King";
	}
}

void copy_list(piece* temp){

	int x = 0; 
	int y = 0;
	while(temp != NULL){

		x = temp->getx();
		y = temp->gety();

		board[x][y] = temp->getType();
		temp = temp->next;
	} 
}

void print_grid(bool affiliation, player* White, player* Black){
	cls


	piece* temp = NULL;

	temp = White->getKing();
	copy_list(temp);
	temp = White->getQueen();
	copy_list(temp);
	temp = White->getRook();
	copy_list(temp);
	temp = White->getKnight();
	copy_list(temp);
	temp = White->getBishop();
	copy_list(temp);
	temp = White->getPawn();
	copy_list(temp);



	temp = Black->getKing();
	copy_list(temp);
	temp = Black->getQueen();
	copy_list(temp);
	temp = Black->getRook();
	copy_list(temp);
	temp = Black->getKnight();
	copy_list(temp);
	temp = Black->getBishop();
	copy_list(temp);
	temp = Black->getPawn();
	copy_list(temp);




	string cols = 	"\t\ta\tb\tc\td\te\tf\tg\th    \n\n";

	cout << cols;

	if (affiliation){			// true for white prints 1 2 3 4 5 6 7 8 !!
	
		for( int x = 7; x>=0; x--){

			cout<<"\t"<<x+1<<"  ";

			for( int y = 0; y<8; y++){
				cout<<"  "<<piece_name(board[y][x])<<"  ";
			}
			cout<<" "<<x+1<<" \n\n\n";
		}	
		
	}
	else{			// Black case prints 8 7 6 5 4 3 2 1 !!
		
		for( int x = 0; x<8; x++){

			cout<<"\t"<<x+1<<"  ";

			for( int y = 0; y<8; y++){
				cout<<"  "<<piece_name(board[y][x])<<"  ";
			}
			cout<<" "<<x+1<<" \n\n\n";
		}
	}

	cout << cols;
}

