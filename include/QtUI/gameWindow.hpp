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
	gameWindow()
	{

		createChessGrid();		
	

		setCentralWidget(box);
		setWindowTitle(tr("ChessNet"));
		setMaximumSize(800, 800);
		setMinimumSize(800, 800);
	}
	
	void reset();
	
	void addMenu();

	
private : 
	void createChessGrid()
	{	
		gameWindow::box = new QGroupBox();
		QGridLayout* chessGridLayout = new QGridLayout();


		bool topLeftColor = true; 	// white true 
		for(int i = 0; i<8; i++ )
		{
			for(int j = 0; j<8; j++ )
			{
				gameWindow::tiles[i][j] = new gameTile((i*8)+j, topLeftColor ^ (j%2), 1);		// would give that alternating white/black pattern
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
		auto selectedTile = tiles[pos/8][pos%8];
		selectedTile->select();
		currentlySelectedTile = selectedTile;

	}


	
	QGroupBox* box;
	gameTile* currentlySelectedTile;
	gameTile* tiles[8][8];	//  a -- h
					// 1
					// |
					// 8

};


#endif
