#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct moves{
	int up;
	int right;

	public : 
		moves(){
			up = right = 0;
		}
};


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
	virtual vector<int,int> possible_moves();
	void die();

};

class King :: public piece()
{
	public :
		King( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}


		vector<int,int>  possible_moves()	override {

			vector<int, int> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back((posx+i,posy+j));
				}
			}
			return out;
		}
}
class Queen :: public piece()
{
	public :
		Queen( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
}
class Rook :: public piece()
{
	public :
		Rook( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
}
class Bishop :: public piece()
{
	public :
		Bishop( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
}
class Knight :: public piece()
{
	public :
		Knight( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
}
class Pawn :: public piece()
{
	public :
		Pawn( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
}