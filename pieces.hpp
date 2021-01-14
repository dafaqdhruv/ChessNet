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

struct pos{
	int x;
	int y;
public: 
	pos(){
		x=y=0;
	}
	pos(int a, int b){
		x = a;
		y = b;
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

		next = nullptr;

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

class King : public piece
{
	public :
		King( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}


		vector<pos>  possible_moves()	 {

			vector<pos> out;

			int tmpX = getx();
			int tmpY = gety();
			
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back((getx()+i,gety()+j));
				}
			}
			return out;
		}
};
class Queen : public piece
{
	public :
		Queen( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}

		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;

			int tmpX = getx();
			int tmpY = gety();
			int flag = 1;

			for(int i = tmpY+1; i<8;i++){
				for(int j = tmpX+1; j<8;j++){
					out.emplace_back((i,j));
					
					if(i == j && flag) {
						out.emplace_back();
					}
					if(grid[i][j])	break;
				}
				if(grid[tmpX+i][tmpY+j])	break;
			}
			for(int i = 1; i<tmpY;i++){
				for(int j = 1; j<tmpX; j++){
					out.emplace_back((tmpX-i,tmpY-j));
				}
			}
			return out;
		}
};
class Rook : public piece
{
	public :
		Rook( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			int tmpX = getx();
			int tmpY = gety();

			for(int i = tmpY+1; i<8;i++){
				for(int j = tmpX+1; j<8;j++){
					out.emplace_back((i,j));
					if(grid[i][j])	break;
				}
				if(grid[tmpX+i][tmpY+j])	break;
			}
			for(int i = 1; i<tmpY;i++){
				for(int j = 1; j<tmpX; j++){
					out.emplace_back((tmpX-i,tmpY-j));
				}
			}

			return out;
		}
};
class Bishop : public piece
{
	public :
		Bishop( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}
};
class Knight : public piece
{
	public :
		Knight( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}
};
class Pawn : public piece
{
	public :
		Pawn( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{}
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}
};