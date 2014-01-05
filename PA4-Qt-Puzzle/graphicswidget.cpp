/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#include <vector>
#include <iostream>
#include <cstdlib>
#include <QtAlgorithms>
#include <QTimer>

#include "graphicswidget.h"

using namespace std;

/**
 * Constructs a GraphicsWidget responsible for managing and rendering a board for the game
 * @param parent the parent of this scene
 * @param output the label which this will output results to
 */
GraphicsWidget::GraphicsWidget(QMainWindow* parent, QLabel* output) : QGraphicsScene(parent)
{
	board = NULL;
	out = output;
	moving = NULL;
	timer = new QTimer(this);
	timer->setInterval(5);
	connect(timer, SIGNAL(timeout()),this,SLOT(handleTimer()));
}

/**
 * Sets the board to the one that is given and creates the display
 * @param b the board to use
 */
void GraphicsWidget::assignBoard(Board* b)
{
	out->setText(QString(""));
	qDeleteAll(items());
	if(b == NULL){return;}
	if(board != NULL){delete board;}
	board = b;
	QBrush brush(QColor(187,222,253));
	for(int i = 0; i < b->getDim(); i++)
	{
		for(int j = 0; j < b->getDim(); j++)
		{
			if(b->getValue(i*b->getDim()+j) == 0)
			{
				continue;
			}
			GUITile* newItem = new GUITile(this,j,i,b->getValue(i*b->getDim()+j));
			addItem(newItem);
			if(newItem->textItem != NULL)
			{
				addItem(newItem->textItem);
			}
		}
	}
}

/**
 * Moves the given tile assuming it is a valid move
 * @param tile the tile to move
 */
void GraphicsWidget::moveTile(GUITile* tile)
{
	
	if(board->solved())
	{
		return;
	}
	out->setText(QString(""));
	
	int val = tile->value;
	int bIndex = board->getTile(val);
	if(bIndex == board->getNorth())
	{
		tile->swap(0,1);
	}
	else if(bIndex == board->getSouth())
	{
		tile->swap(0,-1);
	}
	else if(bIndex == board->getEast())
	{
		tile->swap(-1,0);
	}
	else if(bIndex == board->getWest())
	{
		tile->swap(1,0);
	}
	else
	{
		out->setText(QString("Invalid move!"));
		return;
	}
	moving = tile;
	timer->start();
	
	board->move(bIndex);
	
	if(board->solved())
	{
		out->setText(QString("******Congratulations! You won!*******"));
	}
}

/**
 * Manages the timer for tile animation
 */
void GraphicsWidget::handleTimer()
{
	if(moving->animate())
	{
		timer->start();
	}
	else
	{
		timer->stop();
	}
}

/**
 * Destroys the graphics widget
 */
GraphicsWidget::~GraphicsWidget()
{
}

