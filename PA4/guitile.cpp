/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
 #include <iostream>
#include <sstream>
#include <QBrush>
#include <string>
#include <QtGui>
#include "guitile.h"
#include "graphicswidget.h"

using namespace std;

/**
 * Constructs a GUITile object for use in a puzzle game
 * @param p the owner of this tile
 * @param x the x position (in board coordinates)
 * @param y the y position (in board coordinates)
 * @param val the value held by the tile
 */
GUITile::GUITile(GraphicsWidget * p,int x, int y, int val) : QGraphicsRectItem(x*50,y*50,50,50)
{
	QBrush brush(QColor(187,222,253));
	parent = p;
	dx = x;
	dy = y;
	value = val;
	
	setBrush(brush);
	if(val == 0)
	{
		setBrush(Qt::white);
		textItem = NULL;
	}
	else
	{
		textItem = new QGraphicsSimpleTextItem();
		textItem->setPos(QPointF(x*50+10,y*50+20));
		stringstream ss;
		ss << val;
		string toDisp;
		ss >> toDisp;
		textItem->setText(QString(toDisp.c_str()));
	}
}

/**
 * Causes the tile to move as the result of a mouse click by signaling parent
 * @param event the mouse event
 */
void GUITile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	(void)event;
	parent->moveTile(this);
}

/**
 * Arranges for the tile to move based on 2d vector of the given x and y
 * @param x the x value to add
 * @param y the y value to add
 */
void GUITile::swap(int x, int y)
{
	dx+=x;
	dy+=y;
}

/**
 * Animates the tile by 5px/call
 * @return if the tile moves
 */
bool GUITile::animate()
{
	QRectF r(rect());
	QPointF currentPos(r.topLeft());
	
	int moveSpeed = 5;
	if(dx*50 != currentPos.x() || dy*50 != currentPos.y())
	{
		if(dx*50 < currentPos.x())
		{
			r.moveTo(QPointF(currentPos.x()-moveSpeed,currentPos.y()));
		}
		else if(dx*50 > currentPos.x())
		{
			r.moveTo(QPointF(currentPos.x()+moveSpeed,currentPos.y()));
		}
		else if(dy*50 > currentPos.y())
		{
			r.moveTo(QPointF(currentPos.x(),currentPos.y()+moveSpeed));
		}
		else if(dy*50 < currentPos.y())
		{
			r.moveTo(QPointF(currentPos.x(),currentPos.y()-moveSpeed));
		}
		setRect(r);
		textItem->setPos(r.topLeft().x()+10,r.topLeft().y()+20);
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Destroys the tile
 */
GUITile::~GUITile()
{
	
}
