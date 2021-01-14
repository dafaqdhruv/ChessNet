#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"

using namespace std;

void insert_pieces( piece** head, int posx, int posy, bool affiliation, int piece_type){

   piece* new_piece = new piece(affiliation, piece_type, posx, posy);

   piece* last = *head;

   new_piece->next = nullptr;
   
   if(*head == nullptr){
   		*head = new_piece;
   		return;
   }


    while (last->next != NULL)   
        last = last->next; 


    last->next = new_piece;   
    return; 
}

class player {

	King*	K;
	Queen* 	Q;
	Rook* 	R;
	Bishop* B;
	Knight* N;
	Pawn* 	P;

	public :

	player(bool affiliation){
		K = Q = R = B = N = P = nullptr;
		set_pieces(affiliation);
	}
	~player(){}	

	piece* getKing() { return K;}
	piece* getQueen() { return Q;}
	piece* getRook() { return R;}
	piece* getBishop() { return B;}
	piece* getKnight() { return N;}
	piece* getPawn() { return P;}

	void print_all_locations(piece* head, int grid[8][8]){
		while(head != NULL){

			cout<<"\t"<<(char)(head->getx()+97)<<head->gety()<<"\t\t";
			head->possible_moves(grid);
			cout<<'\n';
			head = head->next;

		}
	}

	void set_pieces(bool affiliation){

		if(affiliation){
			// WHITE CASE

			insert_pieces(&K, 4, 0, 1, 1);
			insert_pieces(&Q, 3, 0 ,1, 2);
			insert_pieces(&R, 0, 0 ,1, 3);
			insert_pieces(&R, 7, 0 ,1, 3);
			insert_pieces(&N, 1, 0,1, 4);
			insert_pieces(&N, 6, 0,1, 4);
			insert_pieces(&B, 2, 0,1, 5);
			insert_pieces(&B, 5, 0,1, 5);

			for(int i = 0 ; i< 8; i++){
				insert_pieces(&P,i,1,1, 6);
			}
		}
		else{
			// BLACK CASE

			insert_pieces(&K, 4, 7, 0, 1);
			insert_pieces(&Q, 3, 7 ,0, 2);
			insert_pieces(&R, 0, 7,0, 3);
			insert_pieces(&R, 7, 7,0, 3);
			insert_pieces(&N, 1, 7,0, 4);
			insert_pieces(&N, 6, 7,0, 4);
			insert_pieces(&B, 2, 7,0, 5);
			insert_pieces(&B, 5, 7,0, 5);

			for(int i = 0 ; i< 8; i++){
				insert_pieces(&P,i, 6,0, 6);
			}
		}
	}
};