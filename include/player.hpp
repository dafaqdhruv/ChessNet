#pragma once
#include <iostream>
#include <string>
#include "pieces.hpp"

using namespace std;

template <class PP>
void insert_pieces( PP** head, int posx, int posy, bool affiliation, int piece_type){

	PP* new_piece = new PP(affiliation, piece_type, posx, posy);

	PP* last = *head;

	new_piece->next = nullptr;

	if(*head == nullptr){
		*head = new_piece;
		return;
	}


	while (last->next != nullptr)   
      	last = last->next; 
	
	new_piece->prev = last;
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


	// int score;

	public :

	// player();
	player(bool affiliation){
		K = nullptr;Q = nullptr;R = nullptr;B = nullptr;N = nullptr;P = nullptr;
		set_pieces(affiliation);
		// score = 0;
	}
	~player(){}	

	bool black_or_white(){
		return (K->getType() > 0) ? true : false;
	}

	King* getKing() { return K;}
	Queen* getQueen() { return Q;}
	Rook* getRook() { return R;}
	Bishop* getBishop() { return B;}
	Knight* getKnight() { return N;}
	Pawn* getPawn() { return P;}



	template <class PP>
	void show_all_pieces(PP* head, int grid[8][8]){
		vector <pos> temp;
		while(head != nullptr){

			cout<<"\t"<<(char)(head->getx()+97)<<head->gety()+1<<"\n";
			head = head->next;

		}
	}

	template<class PP>
	PP* getPieceByIndex(PP* head, int pos){

		cout<<pos<<endl;
		for(int i = 1; i < pos  && head!=nullptr; i++){
			cout<<"YEEt"<<endl;
			head = head->next;
		}

		cout<<head->getx()<<" "<<head->gety()<<endl;
		return head;
	}

	template<class PP>
	PP* getPieceByPos(PP* head, pos place){

		while(head != nullptr){
			
			if(head->getx() == place.x){
				if(head->gety() == place.y){
					return head;
				}
			}
			head = head->next;
		}
		return nullptr;
	}


	void set_pieces(bool affiliation){

		if(affiliation){
			// WHITE CASE

			insert_pieces(&K, 4, 0, 1, 1);
			insert_pieces(&Q, 3, 0 ,1, 2);
																	insert_pieces(&Q, 3, 3,1, 2); 	// TEST 
													
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
									// insert_pieces(&Q, 5, 5,0, 2); 	// TEST 
			insert_pieces(&R, 0, 7,0, 3);
			insert_pieces(&R, 7, 7,0, 3);
										// insert_pieces(&R, 5, 5,0, 3);
			insert_pieces(&N, 1, 7,0, 4);
			insert_pieces(&N, 6, 7,0, 4);
			insert_pieces(&B, 2, 7,0, 5);
			insert_pieces(&B, 5, 7,0, 5);
											insert_pieces(&B, 5, 5,0, 5);

			for(int i = 0 ; i< 8; i++){
				insert_pieces(&P,i, 6,0, 6);
			}
		}
	}
};
