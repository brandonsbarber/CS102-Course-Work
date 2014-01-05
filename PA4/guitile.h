/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef GUITILE_H
#define GUITILE_H


#include <QGraphicsRectItem>
#include <QtGui>
#include <QGraphicsSimpleTextItem>

#include "board.h"

class GraphicsWidget;

class GUITile : public QGraphicsRectItem
{
	public:
		GUITile();
		GUITile(GraphicsWidget* p,int x, int y, int val);
		~GUITile();
		QGraphicsSimpleTextItem* textItem;
		void swap(int x, int y);
		bool animate();
		int value;
	private:
		GraphicsWidget* parent;
		int dx, dy;
		
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif
