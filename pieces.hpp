#pragma once
#include <iostream>
#include <string>

using namespace std;

class piece {

	int posx;
	int posy;

	int type;
	bool affiliation;												// True for white  False for Black
	

	

	public :

	piece* next;													//  Pawns, Bishop, Knight, Rook, Queen, King.
	
	piece();
	piece(bool blk_or_white, int piece_type, int x, int y){

		posx = x;
		posy = y;

		type = piece_type;
		affiliation = blk_or_white;

		
	}

	int getx(){return	posx;}
	int gety(){return	posy;}

	void setx(int x){posx = x;}
	void sety(int y){posy = y;}



	int getType(){	return (affiliation) ? (type) : (-1 * type);	}

	void move();
	void die();

};
