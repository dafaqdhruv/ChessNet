#include <QApplication>


#include "../include/board.hpp"
#include "../include/gameTile.hpp"
#include "../include/gameWindow.hpp"


/// To-DO
//auto resize tiles on window resize??
//or let them stay the same?
//
//center align window


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

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	gameWindow mainWindow(::chessBoard, false);
#ifdef Q_OS_ANDROID
	mainWindow.showMaximized();
#else
	mainWindow.show();
#endif

	return app.exec();
}

