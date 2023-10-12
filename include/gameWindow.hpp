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



class GameWindow : public QMainWindow
{
	Q_OBJECT

	public :
		GameWindow(int chessBoard[8][8], bool isPlayerWhite = true)
		{
			createChessGrid(chessBoard, isPlayerWhite);

			std::string kingPos = (isPlayerWhite) ? "e1" : "e8";
			this->myKing = getTileByPos(translateString(kingPos));

			QObject::connect(this, &GameWindow::check, this, &GameWindow::kingCompromised);

			setCentralWidget(box);
			setWindowTitle(tr("ChessNet"));
			setMaximumSize(800, 800);
			setMinimumSize(800, 800);
		}

		void makeTilesSelectable(bool selectable){
			this -> selectable = selectable;
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
				std::string out = "";
				out += translateInt(from);
				out += translateInt(to);
				emit moved(out);
			}
		}

		void kingCompromised(std::string pos) {
			gameTile* attacker = getTileByPos(translateString(pos));
			this->myKing->setCompromised();
		}

		bool isKingsUnsafeFrom(std::string pos)
		{
			bool out = false;

			switch(getPieceType(translateString(pos))){
				case whitePawn:
				case blackPawn:
					out = moves::canPawnKillPos(pos, myKing->name());
					break;

				case whiteRook:
				case blackRook:
					out = moves::canRookKillPos(pos, myKing->name());
					break;

				case whiteBishop:
				case blackBishop:
					out = moves::canBishopKillPos(pos, myKing->name());
					break;

				case whiteKnight:
				case blackKnight:
					out = moves::canKnightKillPos(pos, myKing->name());
					break;

				case whiteQueen:
				case blackQueen:
					out = moves::canQueenKillPos(pos, myKing->name());
					break;

				case whiteKing:
				case blackKing:
					out = moves::canKingKillPos(pos, myKing->name());
					break;
			}

			if (out) emit check(pos);
			return out;
		}

	signals :
		void moved(std::string str);
		void check(std::string str);

	private :

		// To-do
		// Layout chessGrid according to player color (Black/White)
		void createChessGrid(int chessBoard[8][8], bool isPlayerWhite)
		{
			this->isPlayerWhite = isPlayerWhite;
			this->selectable = isPlayerWhite;
			GameWindow::box = new QGroupBox();
			QGridLayout* chessGridLayout = new QGridLayout();

			bool topLeftColor = true; 	// white true
			for(int i = 0; i<8; i++ )
			{
				for(int j = 0; j<8; j++ )
				{
					auto y = abs(7*!isPlayerWhite-j);
					GameWindow::tiles[i][y] = new gameTile(
						abs(7*!isPlayerWhite - i)*8+y,
						topLeftColor ^ (j%2),
						chessBoard[abs((7*!isPlayerWhite)-i)][y]
					);

					GameWindow::tiles[i][y]->setMinimumSize(91,91);

					connect(GameWindow::tiles[i][y], &gameTile::clicked, this, &GameWindow::selectTile);
					chessGridLayout->addWidget(GameWindow::tiles[i][y], i+1, j+1);
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

		tilePiece getPieceType(int pos)
		{
			return getTileByPos(pos)->getPiece();
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
		gameTile* myKing;
		gameTile* tiles[8][8];	//  a -- h
		// 1
		// |
		// 8

};


#endif
