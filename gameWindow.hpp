#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP


#include <iostream>
#include <string>

#include <QtWidgets>
#include <QLabel>
#include <QtNetwork/QHostAddress>

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
class QMenu;
class QMenuBar;
class QPushButton;
QT_END_NAMESPACE



#include "gameTile.hpp"

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



class gameWindow : public QMainWindow

{

	Q_OBJECT

	public :
		gameWindow(int chessBoard[8][8], bool isPlayerWhite = true)
		{

			createChessGrid(chessBoard, isPlayerWhite);

			setCentralWidget(box);
			setWindowTitle(tr("ChessNet"));
			setMaximumSize(800, 800);
			setMinimumSize(800, 800);
		}

		void myTurn(){
		//	std::cout<<"Monseur jem apalle MYTURN\n";
			selectable = true;
		}
		void notMyTurn(){
		//	std::cout<<"Ayo the not my turn fucn\n";
			selectable = false;
		}

		void reset();

		void addMenu();
		bool getPlayerAffiliation(){ return isPlayerWhite;}

		void movePiece(int from, int to, bool myMove = true)
		{	
			auto fromTile = getTileByPos(from);
			auto toTile = getTileByPos(to);

			if(!myMove)std::cout<<"FROM "<<from<<" TO "<<to<<std::endl;
			auto pieceType = fromTile->getPiece();

			fromTile->reset();
			toTile-> reset();


			toTile->setTileIcon(pieceType);

			updateBoard(translateInt(from), tilePiece(0));
			updateBoard(translateInt(to), pieceType);
			
			if(myMove){
				char out[4];
				out[0] = translateInt(from)[0];
				out[1] = translateInt(from)[1];
				out[2] = translateInt(to)[0];
				out[3] = translateInt(to)[1];
				emit moved(out);
			}
		}
	signals :
		void moved(const char arr[4]);

	private : 

		// To-do
		// Layout chessGrid according to player color (Black/White)
		void createChessGrid(int chessBoard[8][8], bool isWhite)
		{	
			this->isPlayerWhite = isWhite;
			this->selectable = isWhite;
			gameWindow::box = new QGroupBox();
			QGridLayout* chessGridLayout = new QGridLayout();

			bool topLeftColor = true; 	// white true 
			for(int i = 0; i<8; i++ )
			{
				for(int j = 0; j<8; j++ )
				{
					gameWindow::tiles[i][j] = new gameTile( abs(7*!isPlayerWhite - i)*8+j, topLeftColor ^ (j%2), chessBoard[abs((7*!isPlayerWhite)-i)][j]);		// would give that alternating white/black pattern
					gameWindow::tiles[i][j]->setMinimumSize(91,91);
					connect(gameWindow::tiles[i][j], &gameTile::clicked, this, &gameWindow::selectTile);
					chessGridLayout->addWidget(gameWindow::tiles[i][j], i+1, j+1);
				}
				topLeftColor = !topLeftColor;
			}

			if(isPlayerWhite){
				currentlySelectedTile = tiles[7][7];
			} else {
				currentlySelectedTile = tiles[7][0];
			}
			std::cout<<"CURRENTLY SELECTED TILE ==> "<<currentlySelectedTile->name()<<std::endl;
			box->setLayout(chessGridLayout);
		}

		gameTile* getTileByPos(int pos){
			return tiles[abs(7*!isPlayerWhite-pos/8)][pos%8];
		}

		void selectTile(int pos)
		{
			// If it is Player's turn 
			if(selectable){

				auto temp = currentlySelectedTile->getPossibleMoves();
				bool isMovePossible =  false;

				for(auto i : temp) if(i == pos) isMovePossible = true;
				for(auto i : temp)
					getTileByPos(i)->unselect();
				currentlySelectedTile->unselect();

				if(isMovePossible){
					movePiece(translateString(currentlySelectedTile->name()), pos);
					currentlySelectedTile = getTileByPos(pos);
				}
				else { 
					auto selectedTile = getTileByPos(pos);
					//if(selectedTile->getPiece()*currentlySelectedTile->getPiece()>0){
					if(((selectedTile->getPiece()>0) && isPlayerWhite) || ((selectedTile->getPiece() < 0) && !isPlayerWhite)){
						selectedTile->select();
						currentlySelectedTile = selectedTile;

						showPossibleMoves(selectedTile);
					}

					//std::cout<<"Tile number selected :"<<pos<<"\t\t"<<selectedTile->height()<<"  "<<selectedTile->width()<<std::endl;
					//std::cout<<"Tile number selected :"<<selectedTile->name()<<"\t\t"<<translateString(selectedTile->name())<<"    "<<selectedTile->height()<<"  "<<selectedTile->width()<<std::endl;
					std::cout<<"Tile number selected :"<<selectedTile->name()<<"\t\t"<<translateString(selectedTile->name())<<std::endl;
				}
			}

		}

		void showPossibleMoves(gameTile* tile){

			for(auto i : tile -> getPossibleMoves()){
				getTileByPos(i)->setPossible();
			}
		}


		bool isPlayerWhite;	
		bool selectable;
		QGroupBox* box;
		gameTile* currentlySelectedTile;
		gameTile* tiles[8][8];	//  a -- h
		// 1
		// |
		// 8

};


#endif
