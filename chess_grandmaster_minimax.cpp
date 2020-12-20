#include <iostream>
#include <string>

#include "pieces.hpp"
#include "player.hpp"
#include "board.hpp"
#include "game.hpp"

using namespace std;



struct moves{
	int up;
	int right;

	public : 
		moves(){
			up = right = 0;
		}
};

int main(){

	bool input;
	int weight;

	player*  white = new player(1);
	player*  black = new player(0);

	cout<<"Enter player color (1- white // 0 - black)\n";
	cin>> input;
	cout<<"Enter weight of minimax bias :\n";
	cin>>weight;

	// set_board();
	print_grid(input, white, black);
	parse_input(white);
	// input = game(input, weight);



	cout<<"You "<< (input ? "Won!!" : "lost :/");
	return 0;
}