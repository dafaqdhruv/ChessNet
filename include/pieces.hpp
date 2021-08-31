#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struct definition for a board move
// ( move piece up by 3 units and right by 2)
// like that
//
struct moves
{
	int up;
	int right;

	public : 
		moves(){
			up = right = 0;
		}
};

// struct definition for piece position on the board
// x -> column number (0-7)
// y -> row number (0-7)
// did i ever use this?
//
struct pos
{
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


// Class definition for a chess piece
//
class piece 
{
		// Type : piece type ( Pawn, Rook, Knight, Bishop, Queen, King)
		// Will be Enum Later
		int type;

	protected :

		// True -> white  
		// False -> Black
		bool affiliation;
		
		// Position on the board
		pos position;

	public :
	
		// Why did I use linked lists?!
		// piece* next;													//  Pawns, Bishop, Knight, Rook, Queen, King.
		
		piece();
		piece(bool blk_or_white, int piece_type, int x, int y)
		{
			position(x,y);

			type = piece_type;
			affiliation = blk_or_white;
		}

		// Get Position
		int getx() {return position.x;}
		int gety() {return position.y;}

		// Set Position
		void setx(int x) {position.x = x;}
		void sety(int y) {position.y = y;}

		// Get Piece Type along with its affiliation
		// White Pawn (6) // Black Pawn (-6)
		int getType()
		{
			return (affiliation) ? (type) : (-1 * type); 
		}

		// Moves the piece 
		void move(pos to, int grid[8][8])
		{
			grid[to.x][to.y] = grid[posx][posy];
			grid[posx][posy] = 0;
			position =  to;
		}
};

class King : public piece
{
	public :
		King (bool blk_or_white, int piece_type, int x, int y) 
			: piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		King* next;
		King* prev;

		vector<pos>  possible_moves (int grid[8][8])
		{
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

			int flag = true;

			if(to.x-posx == 1 || to.x-posx == -1){
				if( to.y-posy == 1 || to.y-posy == -1){
					if(grid[to.x][to.y] * getType() <= 0)	return true;
					else cout<<"Invalid move due to presence of same team piece at target.";
				}
			}

			cout<<"Invalid move";
			return false;
		}


		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die();
};



class Queen : public piece
{
	public :
		Queen( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		Queen* next;
		Queen* prev;

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

			if(grid[to.x][to.y] * getType() > 0)	{cout<<"Invalid move due to presence of same team piece at target.";return false;}		// CHECK FOR SAME TEAM PIECE AT POS

			// Moved in Y axis
			if(to.x == getx()){
				if( gety() < to.y ){
					for(int i = gety()+1; i<to.y; i++){
						if(grid[getx()][i] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
				else {
					for(int i = gety()-1; i>to.y; i--){
						if(grid[getx()][i] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}
			}

			// Moved in X axis
			else if( to.y == gety()){
				if( getx() < to.x ){
					for(int i = getx()+1; i<to.x; i++){
						if(grid[i][gety()] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
				else {
					for(int i = getx()-1; i>to.x; i--){
						if(grid[i][gety()] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
			}

			// Moved to the right not on axes
			else if( to.x > getx()){

				if(to.x-getx() == to.y-gety()){		// 1st quadrant
					
					for(int i = getx()+1, j = gety()+1; i<to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i++;
						j++;

					}
				}
				else if (to.x-getx() == gety()-to.y){					// 4th quadrant

					for(int i = getx()+1, j = gety()-1; i<to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i++;
						j--;

					}
				}
				else { cout<<"Invalid move due to Not diagonal"; return false;}		// random slop val
			}


			// Moved to the left not on axes
			else {
				if(to.x-getx() == gety()-to.y){		// 2nd quadrant
					
					for(int i = getx()-1, j = gety()+1; i>to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i--;
						j++;

					}
				}
				else if (to.x-getx() == to.y-gety()){					// 3rd quadrant

					for(int i = getx()-1, j = gety()-1; i>to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i--;
						j--;

					}
				}
				else { cout<<"Invalid move due to Not diagonal";return false;}		// random slop val
			}


			cout<<"FLAG IS "<<flag<<endl;		// prints only when wrong piece in between or when true.

			return flag;
		}


		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die(){
			prev-> next = next;
			if(next != nullptr) next->prev = prev;
			cout<<"Quen Ded\n";
		}
};
class Rook : public piece
{
	public :
		Rook( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		Rook* next;
		Rook* prev;

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
			bool flag = true;

			if(grid[to.x][to.y] * getType() > 0)	{cout<<"Invalid move due to presence of same team piece at target.";return false;}		// CHECK FOR SAME TEAM PIECE AT POS

			// Moved in Y axis
			if(to.x == getx()){
				if( gety() < to.y ){
					for(int i = gety()+1; i<to.y; i++){
						if(grid[getx()][i] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
				else {
					for(int i = gety()-1; i>to.y; i--){
						if(grid[getx()][i] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}
			}

			// Moved in X axis
			else if( to.y == gety()){
				if( getx() < to.x ){
					for(int i = getx()+1; i<to.x; i++){
						if(grid[i][gety()] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
				else {
					for(int i = getx()-1; i>to.x; i--){
						if(grid[i][gety()] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
					}
				}	
			}

			else cout<<"Invalid move for Rook.";
			return false;
		}


		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die(){

			prev->next = next;
			if(next != nullptr)	next->prev = prev;
			cout<<"Rook Ded\n";
		}
};
class Bishop : public piece
{
	public :
		Bishop( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		Bishop* next;
		Bishop* prev;

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
			bool flag = true;

			if(grid[to.x][to.y] * getType() > 0)	{cout<<"Invalid move due to presence of same team piece at target.";return false;}		// CHECK FOR SAME TEAM PIECE AT POS

			// Moved to the right not on axes
			else if( to.x > getx()){

				if(to.x-getx() == to.y-gety()){		// 1st quadrant
					
					for(int i = getx()+1, j = gety()+1; i<to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i++;
						j++;

					}
				}
				else if (to.x-getx() == gety()-to.y){					// 4th quadrant

					for(int i = getx()+1, j = gety()-1; i<to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i++;
						j--;

					}
				}
				else { cout<<"Invalid move due to Not diagonal"; return false;}		// random slop val
			}


			// Moved to the left not on axes
			else {
				if(to.x-getx() == gety()-to.y){		// 2nd quadrant
					
					for(int i = getx()-1, j = gety()+1; i>to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i--;
						j++;

					}
				}
				else if (to.x-getx() == to.y-gety()){					// 3rd quadrant

					for(int i = getx()-1, j = gety()-1; i>to.x;){

						if(grid[i][j] != 0)	{
							cout<<"Invlaid move due to Path blocked by other piece.";
							return false;
						}
						i--;
						j--;

					}
				}
				else { cout<<"Invalid move due to Not diagonal";return false;}		// random slop val
			}

			return flag;
		}

		
		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die(){

			prev-> next = next;
			if(next != nullptr)	next->prev = prev;
			
			cout<<"Bishop Ded\n";
		}
};
class Knight : public piece
{
	public :
		Knight( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		Knight* next;
		Knight* prev;

		vector<pos>  possible_moves(int grid[8][8])	 {	

			vector<pos> out;
			for(int i = -1;i<2;i++){
				for(int j =-1; j<2;j++){
					if(i || j)		out.emplace_back(getx()+i,gety()+j);
				}
			}
			return out;
		}


		bool isMoveValid(pos to, int grid[8][8]){	///MAKE AFFILIATION CHECK SO AS TO NOT ALLOW MOVEMENT OF OPPONENT'S PIECE
			bool flag = true;

			if(grid[to.x][to.y] * getType() > 0)	{cout<<"Invalid move due to presence of same team piece at target.";return false;}		// CHECK FOR SAME TEAM PIECE AT POS

			if(to.x-posx == 2 || to.x-posx ==-2){
				if(to.y-posy == 1 || to.y-posy == -1){
					return true;
				}
			}

			else if(to.y-posy == 2 || to.y-posy == -2){
				if(to.x-posx == 1 || to.x-posx ==-1){
					return true;
				}
			}

			cout<<"Invalid move for Knight.";
			return false;
		}

		
		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die(){
			prev-> next = next;
			if(next != nullptr)	next->prev = prev;
			cout<<"Knight Ded\n";
		}
};
class Pawn : public piece
{
	public :
		Pawn( bool blk_or_white, int piece_type, int x, int y) : piece(blk_or_white, piece_type, x, y)
		{
			next = nullptr;
			prev = nullptr;
		}

		Pawn* next;
		Pawn* prev;

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

			bool flag = true;

			if(grid[to.x][to.y] * getType() > 0)	{cout<<"Invalid move due to presence of same team piece at target.";return false;}		// CHECK FOR SAME TEAM PIECE AT POS

			if(to.x == posx){
				if(to.y-posy == 1 && affiliation)	return true;		// WHITE CASE

				else if(to.y-posy == -1 && !affiliation)	return true;		// BLACK CASE

				else if(to.y-posy == 2 && affiliation && posy == 1)	return true;
				else 	if(to.y-posy == -2 && affiliation && posy == 6)	return true;
			}
			else if( to.x-posx ==1 || to.x-posx ==-1){
				if(to.y-posy == 1 && affiliation && grid[to.x][to.y]*getType() < 0)	return true;		// WHITE CASE

				if(to.y-posy == -1 && !affiliation && grid[to.x][to.y]*getType() < 0)	return true;		// BLACK CASE
			}
			else cout<<"Invalid move for Pawn.";
			return false;
		}

		bool isKillShot(pos to, int grid[8][8]){

			if(grid[to.x][to.y]*getType() < 0)	return true;
			else return false;
		}

		void die(){

			prev-> next = next;
			if(next != nullptr)	 next->prev = prev;
			cout<<"Pawn Ded\n";
		}
};
