#include <iostream>
#include <string>

#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"
#include "game.hpp"

using namespace std;



int main(){

	bool input;
	int weight;

	int board[8][8];
	init_board(board);

	player*  white = new player(1);
	player*  black = new player(0);

	cout<<"Enter player color (1- white // 0 - black)\n";
	cin>> input;
	cout<<"Enter weight of minimax bias :\n";
	cin>>weight;

	// set_board();
	print_grid(input, white, black, board);

	input_player_move(white,board);	
	// print_grid(input, white, black, board);
	
	// parse_input(black,grid);	
	// input = game(input, weight);



	cout<<"You "<< (input ? "Won!!" : "lost :/") << "\n";
	return 0;
}
