#include <iostream>
#include <string>

using namespace std;

#define cls cout<<"\033[2J"<<"\n";


struct moves{
	int up;
	int right;

	public : 
		moves(){
			up = right = 0;
		}
};

class piece {

	bool affiliation;												// True for white  False for Black
	int type;
	string name;
	piece* next;													//  Pawns, Bishop, Knight, Rook, Queen, King.
	// moves* possible_moves[8] =  {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

	public :
	piece();
	piece(bool blk_or_white, int piece_type){

		type = piece_type;
		affiliation = blk_or_white;

		switch (type){
			case 1:		name = "King";
				break;
			case 2:		name = "Quen";
				break;
			case 3:		name = "Rook";
				break;
			case 4:		name = "Kni8";
				break;
			case 5:		name = "Bish";	
				break;
			case 6:		name = "Pawn";
				break;

			default : 	name = " __ ";
		}

	}
	void move();
	void die();
	string piece_name(){ return name;}
};

class player {

	piece* King;
	piece* Queen;
	piece* Rook;
	piece* Bishop;
	piece* Knight;
	piece* Pawn;
	public :

	player(){
		King = Queen = Rook = Bishop = Knight = Pawn  = nullptr;
	}
};
int board[8][8];

int piece_at_pos(int num){

	switch(num){

		case 4 :	return 1;

		case 3 :	return 2;

		case 0 :
		case 7 :	return 3;
		
		case 1 :
		case 6 :	return 4;

		case 2 :
		case 5 :	return 5;

	}
}

void set_board(){

	// Numbering 1 starts from White side!
	for(int i = 0; i<8; i++){
		board[0][i] = new piece(1,piece_at_pos(i));		// gives pieces for 1 (WHITE) 
	}

	for(int i = 0; i<8; i++){
		board[1][i] = new piece(1,6);		// 6 for Pawn
	}

	for(int i = 2; i<6; i++){
		for(int j = 0; j< 8; j++){
			board[i][j] = new piece(0, 0);	// 0 for " __ "
		}
	}

	for(int i = 0; i<8; i++){
		board[6][i] = new piece(0,6);		// 6 for Pawn
	}

	for(int i = 0; i<8; i++){
		board[7][i] = new piece(1,piece_at_pos(i));		// gives piecs for 0 (BLACK)
	}
}

void print_grid(bool affiliation){
	cls

	string rows = 	"\t\ta\tb\tc\td\te\tf\tg\th    \n\n";

	cout<<rows;

	if (affiliation){			// true for white prints 1 2 3 4 5 6 7 8 !!
	
		for( int i = 0; i<8; i++){

			cout<<"\t"<<i+1<<"  ";

			for( int j = 0; j<8; j++){
				cout<<"  "<<board[i][j]->piece_name()<<"  ";
			}
			cout<<" "<<i+1<<" \n\n\n";
		}
		
	}
	else{			// Black case prints 8 7 6 5 4 3 2 1 !!
	
	for( int i = 7; i>=0; i--){

			cout<<"\t"<<i+1<<"  ";

			for( int j = 7; j>=0; j--){
				cout<<"  "<<board[i][j]->piece_name()<<"  ";
			}
			cout<<" "<<i+1<<" \n\n\n";
		}
		
	}

	cout<<rows;
}





void give_next_move(){}

void parse_Input(){

	string input;

	cout<<"choose piece : ";
	ci>>
}




bool game(bool affiliation, int weight){


	return 1;
}




int main(){

	bool input;
	int weight;

	cout<<"Enter player color (1- white // 0 - black)\n";
	cin>> input;
	cout<<"Enter weight of minimax bias :\n";
	cin>>weight;

	set_board();
	print_grid(input);

	// input = game(input, weight);

	cout<<"You "<< (input ? "Won!!" : "lost :/");
	return 0;
}