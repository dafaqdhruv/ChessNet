#pragma once

#include <vector>

enum tilePiece : int {blackPawn = -6, blackBishop, blackKnight, blackRook, blackQueen, blackKing, nil, whiteKing, whiteQueen, whiteRook, whiteKnight, whiteBishop, whitePawn};

using enum tilePiece;
int chessBoard[8][8]  = {
	{blackRook, blackKnight,blackBishop,blackQueen,blackKing,blackBishop,blackKnight,blackRook},
	{blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn},
	{whiteRook, whiteKnight,whiteBishop,whiteQueen,whiteKing,whiteBishop,whiteKnight,whiteRook},
};

//int chessBoard[8][8]  = {
//	{tilePiece::blackRook, tilePiece::blackKnight,tilePiece::blackBishop,tilePiece::blackQueen,tilePiece::blackKing,tilePiece::blackBishop,tilePiece::blackKnight,tilePiece::blackRook},
//	{tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn,tilePiece::blackPawn},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn,tilePiece::whitePawn},
//	{tilePiece::whiteRook, tilePiece::whiteKnight,tilePiece::whiteBishop,tilePiece::whiteQueen,tilePiece::whiteKing,tilePiece::whiteBishop,tilePiece::whiteKnight,whiteRook},
//};


string intsToStringPos( int x, int y){

	string out = "";
	out += (x+'a');
	out += (y+'1');
	return out;
}

vector<pair<string,bool>> fillPawnMoves(string position, bool affiliation)
{

}
vector<pair<string,bool>> fillBishopMoves(string position, bool affiliation)
{

}
vector<pair<string,bool>> fillKnightMoves(string position, bool affiliation)
{

}
vector<pair<string,bool>> fillRookMoves(string position, bool affiliation)
{

}
vector<pair<string,bool>> fillQueenMoves(string position, bool affiliation)
{

}
vector<pair<string,bool>> fillKingMoves(string position, bool affiliation)
{
	vector<pair<int,bool>> out;
	int x = position[1] - '1';
	int y = position[0] - 'a';

	for(int i = -1; i<=1; i++){

		for(int j = -1; j<=1; j++){

			if(i || j){
				
				int temp = chessBoard[y][x] * chessBoard[y-j][x-i];
				if(temp <= 0) out.emplace_back({intsToStringPos(x-i, y-j), temp});
			}		
		}
	}
}
