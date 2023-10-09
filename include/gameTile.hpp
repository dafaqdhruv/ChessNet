#ifndef GAMETILE_HPP
#define GAMETILE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"

#include <QtWidgets>
#include <QMainWindow>
#include <QLabel>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE

enum tileState : int { neutralTile = 0, selectedTile, underAttackTile, possibleMoveTile};
//enum tilePiece : int {blackPawn = -6, blackBishop, blackKnight, blackRook, blackQueen, blackKing, nil, whiteKing, whiteQueen, whiteRook, whiteKnight, whiteBishop, whitePawn};



const QColor selectedCol(255, 51, 0, 127);	// orange
//const QColor underAttack(255, 0, 0, 127);	// red
const QColor possibleMoveCol(0, 255, 0, 63);	// green

#define whitePawnPng		":/icons/whitePawn.png"
#define whiteRookPng		":/icons/whiteRook.png"
#define whiteBishopPng		":/icons/whiteBishop.png"
#define whiteKnightPng		":/icons/whiteKnight.png"
#define whiteQueenPng		":/icons/whiteQueen.png"
#define whiteKingPng		":/icons/whiteKing.png"

#define blackPawnPng	  	":/icons/blackPawn.png"
#define blackRookPng		":/icons/blackRook.png"
#define blackBishopPng		":/icons/blackBishop.png"
#define blackKnightPng		":/icons/blackKnight.png"
#define blackQueenPng		":/icons/blackQueen.png"
#define blackKingPng		":/icons/blackKing.png"


static std::string translateInt (int pos)
{
	std::string out = "";
	out += (char)(pos%8 + 'a');
	out += (char)(7 - pos/8 + '1');
	return out;
}

// Should be passed std::string or char*
template <typename T>
static int translateString(T pos)
{
	return (int)((pos[0]-'a') + (7-(pos[1]-'1'))*8);
}




// Basic game piece unit.
// Game Tile <--- Clickable QLabel
// ( 8x8 grid of gametiles makes up the chessBoard )
// can be different pieces, change states and colors.

class gameTile : public QLabel
{
	Q_OBJECT

public :

	explicit gameTile (int pos, bool color, int pieceType = 0, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() )
		: QLabel(parent, f)
	{

		// init tile
		this->state = tileState::neutralTile;
		this->piece = pieceType;
		this->color = color;
		this->position = pos;
		this->possibleMoves = std::vector<int>();
		this->possibleKillShots = std::vector<int>();

		setTileIcon(static_cast<tilePiece>(pieceType));

		if(!color)
		{
			QPalette pal;
			pal.setColor(QPalette::Window, Qt::darkGray);
			this->setPalette(pal);
		}

		// on mouse click, do <selected>
		// connect (this, &gameTile::clicked, parent, );	 // cant connect from inside child to parent.
	}

	~gameTile()
	{}

	void select()
	{
		state = tileState::selectedTile;
		QPalette pal;
		QColor col = selectedCol;
		if(!this->color)col = col.darker();
		pal.setColor(QPalette::Window, col);
		this->setPalette(pal);

		fillPossibleMoves();
	}

	void setPossible()
	{
		state = tileState::possibleMoveTile;
		QPalette pal;
		QColor col = possibleMoveCol;
		if(!this->color)col = col.darker();
		pal.setColor(QPalette::Window, col);
		this->setPalette(pal);
	}
	void unselect()
	{
		state = tileState::neutralTile;
		if(this->color)
			this->setPalette(QPalette(QPalette::Window, Qt::white));
		else
			this->setPalette(QPalette(QPalette::Window, Qt::darkGray));
	}

	std::string name()
	{

		return translateInt(position);
	}

//	void paintTile(tileState in_state)
//	{
//
//	}

	std::vector<int> getPossibleMoves (){
		return possibleMoves;
	}
	std::vector<int> getKillShots (){
		return possibleKillShots;
	}

	tilePiece getPiece(){
		return (tilePiece)piece;
	}
	void setTileIcon(tilePiece in_piece, int id = 0)
	{
		QPixmap tempPixmap;

		piece = in_piece;
		// to-do
		// Messy, might add exception handling later
		switch(in_piece)
		{
			case tilePiece::blackPawn :	 if(!tempPixmap.load(blackPawnPng)) {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::blackBishop :	 if(!tempPixmap.load(blackBishopPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::blackRook : 	 if(!tempPixmap.load(blackRookPng))  {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::blackKnight :	 if(!tempPixmap.load(blackKnightPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::blackQueen : 	 if(!tempPixmap.load(blackQueenPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::blackKing : 	 if(!tempPixmap.load(blackKingPng))  {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whitePawn :  	 if(!tempPixmap.load(whitePawnPng))  {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whiteBishop :	 if(!tempPixmap.load(whiteBishopPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whiteRook : 	 if(!tempPixmap.load(whiteRookPng)) {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whiteKnight :	 if(!tempPixmap.load(whiteKnightPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whiteQueen : 	 if(!tempPixmap.load(whiteQueenPng))   {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
			case tilePiece::whiteKing : 	 if(!tempPixmap.load(whiteKingPng))  {qDebug()<<"Error Loading tile type " << in_piece;}
				break;
		}

		setAutoFillBackground(true);
		setPixmap(tempPixmap);
		setScaledContents(true);
	}

	void reset()
	{
		piece = tilePiece::nil;
		possibleMoves.clear();
		setPixmap(QPixmap());
		unselect();
	}

	// only to be called when piece is selected
	void fillPossibleMoves()
	{
		std::vector<std::pair<std::string,bool>> tempList;

		switch(piece){

			case tilePiece::blackPawn :	tempList = moves::fillPawnMoves(name(), 0);
				break;
			case tilePiece::blackBishop :	tempList = moves::fillBishopMoves(name(), 0);
				break;
			case tilePiece::blackRook : 	tempList = moves::fillRookMoves(name(), 0);
				break;
			case tilePiece::blackKnight :	tempList = moves::fillKnightMoves(name(), 0);
				break;
			case tilePiece::blackQueen : 	tempList = moves::fillQueenMoves(name(), 0);
				break;
			case tilePiece::blackKing : 	tempList = moves::fillKingMoves(name(), 0);
				break;
			case tilePiece::whitePawn :  	tempList = moves::fillPawnMoves(name(), 1);
				break;
			case tilePiece::whiteBishop :	tempList = moves::fillBishopMoves(name(), 1);
				break;
			case tilePiece::whiteRook : 	tempList = moves::fillRookMoves(name(), 1);
				break;
			case tilePiece::whiteKnight :	tempList = moves::fillKnightMoves(name(), 1);
				break;
			case tilePiece::whiteQueen : 	tempList = moves::fillQueenMoves(name(), 1);
				break;
			case tilePiece::whiteKing : 	tempList = moves::fillKingMoves(name(), 1);
				break;
			default : std::cout<<"gabagooee\n";
		}

		for(auto [pos, attack] : tempList){

			if(attack) possibleKillShots.push_back(translateString(pos));
			possibleMoves.push_back(translateString(pos));
		}
	}

protected :

	// used mouseRelease instead of mousePress
	// !!ISSUE
	// release not recorded on the tile on which click was released
	// but the one that was pressed.
	void mouseReleaseEvent(QMouseEvent *event){
		emit clicked(position);
	}


signals :
	void clicked(int pos);


private :

	int state; 			// state of current tile -> neutral/selected/threatened/etc
	bool color;			// is Tile black/white
	int piece;			// is there a piece on the tile? if yes which?

	int position;		// 0-63 translated to a1 --> h8

	std::vector<int> possibleMoves;
	std::vector<int> possibleKillShots;
};

#endif
