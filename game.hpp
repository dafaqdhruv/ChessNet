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

	cout<<"MOTHERFUCKER I STUBBED MY TOE";
	// if(piece->getType()>0)
	// 	print_grid( 1, nullptr, nullptr, grid);
	// else 
	// 	print_grid( 0, nullptr, nullptr, grid);

	cin>>input;
	shift_to = temp.at(input-1);

	piece->move(shift_to,grid);

	if(piece->getType()>0)
		print_grid( 1, nullptr, nullptr, grid);
	else 
		print_grid( 0, nullptr, nullptr, grid);

}


string parse_input(player* Player, player* Enemy, int grid[8][8], string msg="NULL"){

	char input_piece, beforeX,beforeY, afterX,afterY;
	std::string out = "";
	pos from, to;
		
	if(msg=="NULL")
	{
		cout<<"Enter Piece, original pos, new pos (example -> K e6 f5) :\n\t";
		cin>>input_piece;
		cin>>beforeX;
		cin>>beforeY;
		cin>>afterX;
		cin>>afterY;

		// scanf("%c %c%c %c%c", &input_piece, &beforeX, &beforeY, &afterX, &afterY);
		cout<<input_piece<<beforeX<<beforeY<<afterX<<afterY<<endl;
		cout<<out<<endl;


		toLower(beforeX);
		toLower(afterX);

		out+=input_piece;
		out+=beforeX;		// translation for characters and
		out+=beforeY;
		out+=afterX;
		out+=afterY;
	}
	else{
		input_piece = msg[0];
		beforeX = msg[1];
		beforeY = msg[2];
		afterX = msg[3];
		afterY = msg[4];
	}


		from.x = beforeX-97;	// TRANSLATION FROM a-h TO 0-7	
		to.x = afterX-97;		// TRANSLATION FROM a-h TO 0-7

		from.y = beforeY-49;	// TRANSLATION FROM 1-8 TO 0-7
		to.y = afterY-49;		// TRANSLATION FROM 1-8 TO 0-7
		cout<<from.x<<from.y<<to.x<<to.y<<grid[from.x][from.y]<<grid[to.x][to.y]<<endl;

	switch(input_piece){

		case 'K' :
		case 'k' :	if(Player->getKing()->getType() == grid[from.x][from.y]){

						auto piece = Player->getPieceByPos(Player->getKing(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								
								if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}
					
								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		case 'Q' :
		case 'q' :	if(Player->getQueen()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getQueen(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){

								if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}

								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		case 'R' :
		case 'r' :	if(Player->getRook()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getRook(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){

								cout<<"Okay this is valid\n";
																if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}

								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		case 'B' :
		case 'b' :	if(Player->getBishop()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getBishop(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){

								cout<<"Okay this is valid\n";
								if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}

								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		case 'N' :
		case 'n' :	if(Player->getKnight()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getKnight(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){
								cout<<"Okay this is valid\n";

								if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}
								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
							else cout <<"INVALID\n";
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		case 'P' :
		case 'p' :	if(Player->getPawn()->getType() == grid[from.x][from.y]){
						auto piece = Player->getPieceByPos(Player->getPawn(),from);			// CHECK IF FROM POSITION HAS A PIECE OF GIVEN TYPE. IF YES-->CHECK IF TO POSITION IS VALID MOVE OR NOT. IF YES-->MOVE
						if(piece != nullptr){
							if(piece->isMoveValid(to,grid)){

								cout<<"Okay this is valid\n";
								
								if(piece->isKillShot(to,grid)){									

									switch(grid[to.x][to.y]){
										// case  1 :
										// case -1 :
										case  2 :
										case -2 :	Enemy->getPieceByPos(Enemy->getQueen(),to)->die();
													break;
										case  3 :
										case -3 :	Enemy->getPieceByPos(Enemy->getRook(),to)->die();
													break;
										case  4 :
										case -4 :	Enemy->getPieceByPos(Enemy->getKnight(),to)->die();
													break;
										case  5 :
										case -5 :	Enemy->getPieceByPos(Enemy->getBishop(),to)->die();
													break;
										case  6 :
										case -6 :	Enemy->getPieceByPos(Enemy->getPawn(),to)->die();
													break;
									}
								}

								piece->move(to,grid);
								cout<<"VALID&&MOVED";
							}
						}
						else cout<<"No piece found with matching position.";
					}
					break;

		default : 	cout<<"INVALID.";	
	}	

	return out;
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




bool game(bool affiliation, player* White, player* Black, int board[8][8], int weight = 0){

	bool count = true;

	while(1){
		if(count){			 /*&& !Win */

			parse_input(White, Black, board);	
			print_grid(affiliation, nullptr, nullptr, board);
			count = !count;
		}
		else{
			parse_input(Black, White, board);	
			print_grid(affiliation, nullptr, nullptr, board);
			count = !count;
		}
	}
	return 1;
}




// class gameclass : public net::clientinterface<GameMessage> {


// 	bool onGameInit( depending on initiator or responder ){} //INIT CONNECTION AND READY THE GAME
	

// };