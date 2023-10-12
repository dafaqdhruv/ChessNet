#ifndef BOARD_HPP
#define BOARD_HPP
#include<iostream>
#include<string>
#include<vector>
enum tilePiece : int {blackPawn = -6, blackBishop, blackKnight, blackRook, blackQueen, blackKing, nil, whiteKing, whiteQueen, whiteRook, whiteKnight, whiteBishop, whitePawn};

//using enum tilePiece;
//int chessBoard[8][8]  = {
//	{blackRook, blackKnight,blackBishop,blackQueen,blackKing,blackBishop,blackKnight,blackRook},
//	{blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn},
//	{whiteRook, whiteKnight,whiteBishop,whiteQueen,whiteKing,whiteBishop,whiteKnight,whiteRook},
//};



static int chessBoard[8][8]  = {
	{tilePiece::blackRook, tilePiece::blackKnight,tilePiece::blackBishop,tilePiece::blackQueen,tilePiece::blackKing,tilePiece::blackBishop,tilePiece::blackKnight,tilePiece::blackRook},
	{tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn},
	{0,tilePiece::whiteQueen,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,tilePiece::blackKnight,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn},
	{tilePiece::whiteRook, tilePiece::whiteKnight,tilePiece::whiteBishop,tilePiece::whiteQueen,tilePiece::whiteKing,tilePiece::whiteBishop,tilePiece::whiteKnight,whiteRook},
};


static void updateBoard(std::string pos, tilePiece updateVal)
{
	int x = pos[0]-'a';
	int y = 7 - pos[1]+'1';



//	std::cout<<chessBoard[y][x]<<"I CHANGED IT ";
	chessBoard[y][x] = updateVal;
//	std::cout<<chessBoard[y][x]<<" & y, x "<<y<<" "<<x<<std::endl;
}
namespace moves {
	static std::string intsToStringPos( int x, int y){
		std::string out = "";
		out += (x+'a');
		out += (y+'1');
		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillPawnMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7 - position[1] + '1';
		int x = position[0] - 'a';
		bool flag = true;

		int delta = 1, temp;
		if(affiliation) delta = -1;

		for(int i = -1; i<=1; i++){
			if(x+i >= 0 && x+i <8 && y+delta>=0 && y+delta<8){

				if(i) {
					temp = chessBoard[y][x] * chessBoard[y+delta][x+i];
					if(temp < 0)out.emplace_back(intsToStringPos(x+i, 7-y-delta), temp);
					//if(temp < 0)out.emplace_back(intsToStringPos(x+i, y+delta), temp);
				}
				else {
					temp = chessBoard[y][x] * chessBoard[y+delta][x+i];
					if(temp == 0)out.emplace_back(intsToStringPos(x+i, 7-y-delta), temp);
				}
			}
		}

		if(!affiliation && y == 1) {
			delta = 2;
			temp = chessBoard[y][x] * chessBoard[y+delta][x];
			if(temp == 0 && !chessBoard[y+delta-1][x]) out.emplace_back(intsToStringPos(x, 7-y-delta), temp);
		}
		else if( affiliation && y == 6) {
			delta = -2;
			temp = chessBoard[y][x] * chessBoard[y+delta][x];
			if(temp == 0 && !chessBoard[y+delta+1][x]) out.emplace_back(intsToStringPos(x, 7-y-delta), temp);
		}

		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillBishopMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7 - position[1] + '1';
		int x = position[0] - 'a';
		int counter = 1;
		int temp;

		for(int i = -1; i<=1; i+=2){
			for(int j = -1; j<=1; j+=2){

				counter = 0;
				do{
					counter++;
					if( x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8){
						temp = chessBoard[y][x] * chessBoard[y+counter*j][x+counter*i];
						if(temp <= 0)out.emplace_back(intsToStringPos(x+counter*i, 7-y-counter*j), temp);
						//if(temp < 0)out.emplace_back(intsToStringPos(x+i, y+delta), temp);
					}
				}while(temp == 0 && x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8);
			}
		}

		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillKnightMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7 - position[1] + '1';
		int x = position[0] - 'a';
		int counter = 1;
		int temp;

		std::vector<std::pair<int,int>> points = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};
		for( auto [i,j] : points){
			if( x+i >= 0 && x+i <8 && y+j>=0 && y+j<8){
				temp = chessBoard[y][x] * chessBoard[y+j][x+i];
				if(temp <= 0)out.emplace_back(intsToStringPos(x+i, 7-y-j), temp);
			}
		}

		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillRookMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7 - position[1] + '1';
		int x = position[0] - 'a';
		int counter = 1;
		int temp;

		for(int i = -1; i<=1; i++){
			for(int j = -1; j<=1; j++){

				if(!(i&&j)){
					counter = 0;
					do{
						counter++;
						if( x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8){
							temp = chessBoard[y][x] * chessBoard[y+counter*j][x+counter*i];
							if(temp <= 0)out.emplace_back(intsToStringPos(x+counter*i, 7-y-counter*j), temp);
							//if(temp < 0)out.emplace_back(intsToStringPos(x+i, y+delta), temp);
						}
					}while(temp == 0 && x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8);
				}
			}
		}

		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillQueenMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7 - position[1] + '1';
		int x = position[0] - 'a';
		int counter = 1;
		int temp;

		for(int i = -1; i<=1; i++){
			for(int j = -1; j<=1; j++){

				counter = 0;
				do{
					counter++;
					if( x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8){
						temp = chessBoard[y][x] * chessBoard[y+counter*j][x+counter*i];
						if(temp <= 0)out.emplace_back(intsToStringPos(x+counter*i, 7-y-counter*j), temp);
						//if(temp < 0)out.emplace_back(intsToStringPos(x+i, y+delta), temp);
					}
				}while(temp == 0 && x+counter*i >= 0 && x+counter*i <8 && y+counter*j>=0 && y+counter*j<8);
			}
		}

		return out;
	}

	static std::vector<std::pair<std::string,bool>> fillKingMoves(std::string position, bool affiliation)
	{
		std::vector<std::pair<std::string,bool>> out;
		int y = 7-position[1] + '1';
		int x = position[0] - 'a';

		for(int i = -1; i<=1; i++){

			for(int j = -1; j<=1; j++){

				if((i || j) && y+j >=0 && y+j<8 && x+i<8 && x+i>=0){

					int temp = chessBoard[y][x] * chessBoard[y+j][x+i];
					if(temp <= 0) out.emplace_back(intsToStringPos(x+i, 7-y-j), temp);
				}
			}
		}
		return out;
	}

	static bool canPawnKillPos(std::string pawnAt, std::string pos)
	{
		int pawnAtX = pawnAt[0]-'a';
		int pawnAtY = pawnAt[1]-'1';

		int posX = pos[0]-'a';
		int posY = pos[1]-'1';

		bool L = (abs(posX - pawnAtX) == 1);
		bool R = ((chessBoard[pawnAtY][pawnAtX] > 0) ? ((posY - pawnAtY) == 1) : ((posY - pawnAtY) == -1));

		return  L && R;
	}

	static bool canRookKillPos(std::string rookAt, std::string pos)
	{
		int rookAtX = rookAt[0]-'a';
		int rookAtY = rookAt[1]-'1';

		int posX = pos[0]-'a';
		int posY = pos[1]-'1';


		int l, r;
		if(posX == rookAtX){
			if(rookAtY < posY) {
				l = rookAtY+1;
				for(; l< posY; l++){
					if(chessBoard[l][rookAtX]) return false;
				}
			} else {
				l = rookAtY-1;
				for(; l > posY; l--){
					if(chessBoard[l][rookAtX]) return false;
				}
			}
		} else if (posY == rookAtY){
			if(rookAtX < posX) {
				l = rookAtX+1;
				for(; l< posX; l++){
					if(chessBoard[rookAtY][l]) return false;
				}
			} else {
				l = rookAtX-1;
				for(; l > posX; l--){
					if(chessBoard[rookAtY][l]) return false;
				}
			}
		} else {
			return false;
		}

		return true;
	}

	static bool canBishopKillPos(std::string bishopAt, std::string pos)
	{
		int bishopAtX = bishopAt[0]-'a';
		int bishopAtY = bishopAt[1]-'1';

		int posX = pos[0]-'a';
		int posY = pos[1]-'1';

		int diffX = bishopAtX-posX;
		int diffY = bishopAtY-posY;

		if(abs(diffX/(double)diffY) != 1.0) return false;

		int x, y;
		if(bishopAtX < posX) {
			if(bishopAtY < posY){
				// +1 +1
				x = bishopAtX+1;
				y = bishopAtY+1;

				for(int i = 1; i<diffX; i++){
					if(chessBoard[y+i][x+i]) return false;
				}
			} else{
				// +1 -1
				x = bishopAtX+1;
				y = bishopAtY-1;

				for(int i = 1; i<diffX; i++){
					if(chessBoard[y-i][x+i]) return false;
				}
			}
		} else {
			if(bishopAtY < posY){
				// -1 +1
				x = bishopAtX-1;
				y = bishopAtY+1;

				for(int i = 1; i<diffX; i++){
					if(chessBoard[y+i][x-i]) return false;
				}
			} else {
				// -1 -1
				x = bishopAtX-1;
				y = bishopAtY-1;

				for(int i = 1; i<diffX; i++){
					if(chessBoard[y-i][x-i]) return false;
				}
			}
		}

		return true;
	}

	static bool canKnightKillPos(std::string knightAt, std::string pos)
	{
		int knightAtX = knightAt[0]-'a';
		int knightAtY = knightAt[1]-'1';

		int posX = pos[0]-'a';
		int posY = pos[1]-'1';

		int diffX = knightAtX-posX;
		int diffY = knightAtY-posY;

		if(abs(diffX) == 2){
			if(abs(diffY) == 1){
				return true;
			}
		} else if(abs(diffY == 2)){
			if(abs(diffX) == 1){
				return true;
			}
		}
		return false;
	}

	static bool canQueenKillPos(std::string queenAt, std::string pos)
	{
		bool b = canBishopKillPos(queenAt, pos);
		bool r = canRookKillPos(queenAt, pos);

		return  b || r;
	}

	static bool canKingKillPos(std::string kingAt, std::string pos)
	{
		int kingAtX = kingAt[0]-'a';
		int kingAtY = kingAt[1]-'1';

		int posX = pos[0]-'a';
		int posY = pos[1]-'1';

		int diffX = kingAtX-posX;
		int diffY = kingAtY-posY;

		if(abs(diffX) <=1  && abs(diffY) <= 1)	return true;

		return false;
	}

}
#endif
