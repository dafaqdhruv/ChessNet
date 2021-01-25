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

	// piece* next;													//  Pawns, Bishop, Knight, Rook, Queen, King.
	
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

	void move(pos to, int grid[8][8]){

		grid[to.x][to.y] = grid[posx][posy];
		grid[posx][posy] = 0;
		posx = to.x;
		posy = to.y;
	}

	void die();

};

class King : public piece
{
	public :
		King( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;

		}

		King* next;
		vector<pos>  possible_moves(int grid[8][8]){

			vector<pos> out;

			int tmpX = getx();
			int tmpY = gety();
			
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)	out.emplace_back(tmpX+i,tmpY+j);
				}
			}
			return out;
		}

		bool isMoveValid(pos to, int grid[8][8]){
			 return false;
		}
};



class Queen : public piece
{
	public :
		Queen( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
		}

		Queen* next;
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;

			int posX = getx();
			int posY = gety();
			int flag = 1;
			int count = 1;

			cout<<'\t';
			// cout<<count++<<"MOTHERFUCKER"<<posX<<posY<<flag;

			// X axis
			for(int i = posX+1; i<8 && flag; i++){
				if (grid[i][posY] == 0)
				{
					out.emplace_back(i,posY);
					cout<<count++<<")\t"<<(char)(i+97)<<posY+1<<"\n\t";
				}
				else{

					if(grid[i][posY] * getType() < 0){
						out.emplace_back(i, posY);						
						cout<<count++<<")\t"<<(char)(i+97)<<posY+1<<"\n\t";
					}	

					flag = 0;
				}
			}

			flag = 1;
			for(int i = posX-1; i>=0 && flag; i--){
				if (grid[i][posY] == 0)
				{
					cout<<count++<<")\t"<<(char)(i+97)<<posY+1<<"\n\t";
					out.emplace_back(i,posY);
				}
				else{

					if(grid[i][posY] * getType() < 0){
						out.emplace_back(i, posY);
						cout<<count++<<")\t"<<(char)(i+97)<<posY+1<<"\n\t";
					}

					flag = 0;
				}
			}

			// Y axis
			flag = 1;
			for(int i = posY+1; i<8 && flag; i++){
				if (grid[posX][i] == 0)
				{
					cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<"\n\t";
						// cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<" "<<grid[posX][i]<<getType()<<"\n\t";
					out.emplace_back(posX,i);	
				}
				else{

					if(grid[posX][i] * getType() < 0){
						cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<"\n\t";
						// cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<" "<<grid[posX][i]<<getType()<<"\n";
						out.emplace_back(posX,i);
					}

					flag = 0;
				}
			}

			flag = 1;
			for(int i = posY-1; i>=0 && flag; i--){
				if (grid[posX][i] == 0)
				{
						// cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<" "<<grid[posX][i] * getType()<<"\n\t";
					cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<"\n\t";
					out.emplace_back(posX,i);
				}
				else{

					if(grid[posX][i] * getType() < 0){
						out.emplace_back(posX,i);
					cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<"\n\t";
						// cout<<count++<<")\t"<<(char)(posX+97)<<i+1<<" "<<grid[posX][i] * getType()<<"\n\t";
					}

					flag = 0;
				}

			}

			// Positive X==Y side
			flag = 1;
			for(int i = posY+1, j = posX+1;  i<8 && j<8 && flag;){

					if(grid[i][j] == 0){
						cout<<count++<<")\t"<<(char)(i+97)<<j+1<<"\n\t";
						out.emplace_back(i,j);
					}
					else{
						flag = 0;
					}

					i++;
					j++;
			}

			// Negative X==Y side
			flag = 1;
			for(int i = posY-1, j = posX-1;  i>=0 && j>=0 && flag;){

					if(grid[i][j] == 0){
						cout<<count++<<")\t"<<(char)(i+97)<<j+1<<"\n\t";
						out.emplace_back(i,j);
					}
					else{
						flag = 0;
					}

					i--;
					j--;
			}

			return out;
		}



		bool isMoveValid(pos to, int grid[8][8]){

			bool flag = true;
			if(to.x == getx()){}
			else if( to.y == gety()){
				
			}
			else if( to.x > getx()){

				if(to.x-getx() == to.y-gety()){		// 1st quadrant
					
					for(int i = getx()+1, j = gety()+1; i<=to.x;){

						if(grid[i][j] != 0)	{
							if(grid[i][j] * getType() > 0)
								flag = false;
							break;
						}
						i++;
						j++;

					}
				}
				else if (to.x-getx() == gety()-to.y){					// 4th quadrant

					for(int i = getx()+1, j = gety()-1; i<=to.x;){

						if(grid[i][j] != 0)	{
							if(grid[i][j] * getType() > 0)
								flag = false;
							break;
						}
						i++;
						j--;

					}
				}
				else return false;		// random slop val
			}

			else {
				if(to.x-getx() == gety()-to.y){		// 2nd quadrant
					
					for(int i = getx()-1, j = gety()+1; i>=to.x;){

						if(grid[i][j] != 0)	{
							if(grid[i][j] * getType() > 0)			/// POSSIBLE ERROR LOGIC :: IF A PIECE APPEARS BEFORE to.x,to.y VALUE IS TRU/FLAS
								flag = false;
							break;
						}
						i--;
						j++;

					}
				}
				else if (to.x-getx() == to.y-gety()){					// 3rd quadrant

					for(int i = getx()-1, j = gety()-1; i>=to.x;){

						if(grid[i][j] != 0)	{
							if(grid[i][j] * getType() > 0)
								flag = false;
							break;
						}
						i--;
						j--;

					}
				}
				else return false;		// random slop val
			}



			return flag;
		}

};
class Rook : public piece
{
	public :
		Rook( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
		}

		Rook* next;
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			// 	int tmpX = getx();
			// 	int tmpY = gety();

			// 	for(int i = tmpY+1; i<8;i++){
			// 		for(int j = tmpX+1; j<8;j++){
			// 			out.emplace_back((i,j));
			// 			if(grid[i][j])	break;
			// 		}
			// 		if(grid[tmpX+i][tmpY+j])	break;
			// 	}
			// 	for(int i = 1; i<tmpY;i++){
			// 		for(int j = 1; j<tmpX; j++){
			// 			out.emplace_back((tmpX-i,tmpY-j));
			// 		}
			// 	}

			return out;
		}


		bool isMoveValid(pos to, int grid[8][8]){
			 return false;
		}
};
class Bishop : public piece
{
	public :
		Bishop( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
		}

		Bishop* next;
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}


		bool isMoveValid(pos to, int grid[8][8]){
			 return false;
		}
};
class Knight : public piece
{
	public :
		Knight( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
		}

		Knight* next;
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}


		bool isMoveValid(pos to, int grid[8][8]){
			 return false;
		}
};
class Pawn : public piece
{
	public :
		Pawn( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
		}

		Pawn* next;
		vector<pos>  possible_moves(int grid[8][8])	 {

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}


		bool isMoveValid(pos to, int grid[8][8]){
			 return false;
		}
};