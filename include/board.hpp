#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"
#include "player.hpp"

using namespace std;

#define cls cout<<"\n\n\n\n";	
// #define cls cout<<"\033[2J"<<"\n";	


// Layout for chess-board 
// (initialised later on)
int grid[8][8] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}
				};


 namespace board
 {
	
	// Resets board to null values
	void init_board(int board[8][8]){

		for(int i =0;i<8;i++){
			for (int j=0;j<8;j++){
				board[i][j] = 0;
			}
		}

	}


	// Default pieces at column num 
	//
	//  0     1		2	3	4	5	6	7
	// pawn  pawn   pawn  pawn  pawn  pawn   pawn  pawn
	// rook knight bishop queen king bishop knight rook
	int piece_at_pos(int num){

		switch(num){

			case 4 :	return 1;		// king

			case 3 :	return 2;		// queen

			case 0 :
			case 7 :	return 3;		// rook
			
			case 1 :	
			case 6 :	return 4;		// knight

			case 2 :
			case 5 :	return 5;		// bishop

		}
		return 999;
	}
	

	// Returns name of the pieces 
	//
	string piece_name(int type){					//						 --	 --	 @@	 --    --
										//						 ##	 --	 @@	 --	 ##
		switch(type){						//						 --	 ##	 @@	 ##	 --
			case  42:	return "  @@  ";			// 		Highlight case		 @@	 @@	Quen   @@	 @@
			case  0 : 	return "  __  ";			//						 --	 ##	 @@	 ##	 --
			case  6	:	return "W_Pawn";		//						 ##	 --	 @@	 --	 ##
			case -6	:	return "B_Pawn";		//						 --	 --	 @@	 --	 --
			case  5	:	return "W_Bish";
			case -5	:	return "B_Bish";
			case  4	:	return "W_Kni8";
			case -4	:	return "B_Kni8";
			case  3	:	return "W_Rook";
			case -3	:	return "B_Rook";
			case  2	:	return "W_Quen";
			case -2	:	return "B_Quen";
			case  1	:	return "W_King";
			case -1	:	return "B_King";
		}
		return "err0";
	}


	// Recieves a vector of piece objects (Hence the template) 
	// and copies them on the grid accordingly
	template<class PP>
	void copy_list(PP* temp, int grid[8][8]){

		int x = 0; 
		int y = 0;
		while(temp != nullptr){

			x = temp->getx();
			y = temp->gety();

			grid[x][y] = temp->getType();										//	STORING [X][Y]??			
			temp = temp->next;
		} 
	}


	// Prints the chessBoard's given state
	// (affiliation -> is the board to be printed acc to white player's view or black's)

	void print_grid(bool affiliation, player* White, player* Black, int board[8][8])
	{

		cls
	
		// Copies all the available pieces (alive)
		// of both the players' pieces on the board 
		if(White != nullptr && Black != nullptr)
		{
			copy_list(White->getKing(),board);
			copy_list(White->getQueen(),board);
			copy_list(White->getRook(),board);
			copy_list(White->getKnight(),board);
			copy_list(White->getBishop(),board);
			copy_list(White->getPawn(),board);

			copy_list(Black->getKing(),board);
			copy_list(Black->getQueen(),board);
			copy_list(Black->getRook(),board);
			copy_list(Black->getKnight(),board);
			copy_list(Black->getBishop(),board);
			copy_list(Black->getPawn(),board);
		}
		

		// printed to aid locating the columns.
		string cols = 	"\t\ta         b         c         d         e         f         g         h\n\n";

		cout << cols;

		// true for white 
		// prints 1 2 3 4 5 6 7 8 !!
		if (affiliation)
		{
			for( int x = 7; x>=0; x--)
			{
				cout<<"\t"<<x+1<<"  ";

				for( int y = 0; y<8; y++)
				{
					// PRINTING [Y][X] FOR VERTICAL BOARD 
					// DATA STORED IN X,Y FORMAT THO
					cout<<"  "<<piece_name(board[y][x])<<"  ";			
				}

				cout<<" "<<x+1<<" \n\n\n";
			}	
			
		}	
		// Black case prints 
		// 8 7 6 5 4 3 2 1 !!
		else
		{	
			for( int x = 0; x<8; x++)
			{
				cout<<"\t"<<x+1<<"  ";

				for( int y = 0; y<8; y++)
				{
					// PRINTING [Y][X] FOR VERTICAL BOARD 
					cout<<"  "<<piece_name(board[y][x])<<"  ";
				}

				cout<<" "<<x+1<<" \n\n\n";
			}
		}

		cout << cols;

	}
 }
