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
	
	void reset();
	
	void addMenu();

	
private : 
	
	// To-do
	// Layout chessGrid according to player color (Black/White)
	void createChessGrid(int chessBoard[8][8], bool isWhite)
	{	
		this->isPlayerWhite = isWhite;
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
		currentlySelectedTile = tiles[0][0];

		box->setLayout(chessGridLayout);
	}


	void selectTile(int pos)
	{
		currentlySelectedTile->unselect();
		auto selectedTile = tiles[abs(7*!isPlayerWhite-pos/8)][pos%8];
		selectedTile->select();
		currentlySelectedTile = selectedTile;
	
//		std::cout<<"Tile number selected :"<<pos<<"\t\t"<<selectedTile->height()<<"  "<<selectedTile->width()<<std::endl;
std::cout<<"Tile number selected :"<<selectedTile->name()<<"\t\t"<<selectedTile->height()<<"  "<<selectedTile->width()<<std::endl;

	}


	bool isPlayerWhite;	
	QGroupBox* box;
	gameTile* currentlySelectedTile;
	gameTile* tiles[8][8];	//  a -- h
					// 1
					// |
					// 8

};


#endif
