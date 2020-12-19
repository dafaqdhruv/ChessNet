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

	piece* King;
	piece* Queen;
	piece* Rook;
	piece* Bishop;
	piece* Knight;
	piece* Pawn;

	public :

	player(bool affiliation){
		King = Queen = Rook = Bishop = Knight = Pawn  = nullptr;
		set_pieces(affiliation);
	}
	~player(){}	

	piece* getKing() { return King;}
	piece* getQueen() { return Queen;}
	piece* getRook() { return Rook;}
	piece* getBishop() { return Bishop;}
	piece* getKnight() { return Knight;}
	piece* getPawn() { return Pawn;}

	void set_pieces(bool affiliation){

		if(affiliation){
			// WHITE CASE

			insert_pieces(&King, 4, 0, 1, 1);
			insert_pieces(&Queen, 3, 0 ,1, 2);
			insert_pieces(&Rook, 0, 0 ,1, 3);
			insert_pieces(&Rook, 7, 0 ,1, 3);
			insert_pieces(&Knight, 1, 0,1, 4);
			insert_pieces(&Knight, 6, 0,1, 4);
			insert_pieces(&Bishop, 2, 0,1, 5);
			insert_pieces(&Bishop, 5, 0,1, 5);

			for(int i = 0 ; i< 8; i++){
				insert_pieces(&Pawn,i,1,1, 6);
			}
		}
		else{
			// BLACK CASE

			insert_pieces(&King, 4, 7, 0, 1);
			insert_pieces(&Queen, 3, 7 ,0, 2);
			insert_pieces(&Rook, 0, 7,0, 3);
			insert_pieces(&Rook, 7, 7,0, 3);
			insert_pieces(&Knight, 1, 7,0, 4);
			insert_pieces(&Knight, 6, 7,0, 4);
			insert_pieces(&Bishop, 2, 7,0, 5);
			insert_pieces(&Bishop, 5, 7,0, 5);

			for(int i = 0 ; i< 8; i++){
				insert_pieces(&Pawn,i, 6,0, 6);
			}
		}
	}
};