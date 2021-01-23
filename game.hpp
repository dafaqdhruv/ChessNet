#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;

void toLower(char &A){

	if(A>=65 && A<=90){
		A = A+32;
	}
}


void give_next_move(){}

template <class PP>
void choose_move(PP* piece, int grid[8][8], int new_val = 0){

	int input;
	vector<pos> temp = piece->possible_moves(grid);
	pos shift_to;

	print_grid((piece->getType()>0) ? 1 : 0, nullptr, nullptr, grid);

	cin>>input;
	shift_to = temp.at(input-1);

	piece->move(shift_to,grid);
	print_grid((piece->getType()>0) ? 1 : 0, nullptr, nullptr, grid);

}


void parse_input(player* Player, int grid[8][8]){

	char piece, beforeX,beforeY, afterX,afterY;
	pos from, to;
	
	cout<<"Enter Piece, original pos, new pos (example -> K e6 f5) :\n\t";
	scanf("%c %c%c %c%c",piece, beforeX,beforeY, afterX,afterY);

	toLower(beforeX);
	toLower(afterX);

	from.x = beforeX-97;	// TRANSLATION FROM a-h TO 0-7	
	to.x = afterX-97;		// TRANSLATION FROM a-h TO 0-7

	from.y = beforeY-49;	// TRANSLATION FROM 1-8 TO 0-7
	to.y = afterY-49;		// TRANSLATION FROM 1-8 TO 0-7



	switch(piece){

		case 'K' :
		case 'k' :	if(Player->getKing()->getType() == grid[from.x][from.y]){

						auto piece = Player->getPieceByPos(Player->getKing(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		case 'Q' :
		case 'q' :	if(Player->getQueen()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getQueen(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		case 'R' :
		case 'r' :	if(Player->getRook()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getRook(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		case 'B' :
		case 'b' :	if(Player->getBishop()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getBishop(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		case 'N' :
		case 'n' :	if(Player->getKnight()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getKnight(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		case 'P' :
		case 'p' :	if(Player->getPawn()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getPawn(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								piece->move(to,grid);
							}
						}
					}
					break;

		default : 	cout<<"INVALID.";	
	}	
}

void input_player_move(player* Player, int grid[8][8]){

	int input;
	char i;

	cout << "choose piece (K Q R B N P) : ";
	cin >> i;


	switch(i){

		case 'K' :
		case 'k' :	Player->show_all_pieces(Player->getKing(), grid);
					// cout<<head->getx ()<<" "<<head->gety()<<endl;
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getKing(),input),grid);
					break;
		case 'Q' :
		case 'q' :	Player->show_all_pieces(Player->getQueen(), grid);
					cout<<"enter input"<<endl;
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getQueen(),input),grid);
					break;
		case 'R' :
		case 'r' :	Player->show_all_pieces(Player->getRook(), grid);
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getRook(),input),grid);
					break;
		case 'B' :
		case 'b' :	Player->show_all_pieces(Player->getBishop(), grid);
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getBishop(),input),grid);
					break;
		case 'N' :
		case 'n' :	Player->show_all_pieces(Player->getKnight(), grid);
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getKnight(),input),grid);
					break;
		case 'P' :
		case 'p' :	Player->show_all_pieces(Player->getPawn(), grid);
					cin>>input;
					choose_move(Player->getPieceByIndex(Player->getPawn(),input),grid);
					break;
		default : 	cout<<"INVALID.";	
	}	

	
}




bool game(bool affiliation, int weight){


	return 1;
}


