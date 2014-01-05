/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QMainWindow>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <vector>
#include <QLabel>


#include "board.h"
#include "guitile.h"

class GraphicsWidget : public QGraphicsScene {
    Q_OBJECT
    
	public:
 	   	GraphicsWidget(QMainWindow* parent,QLabel* output);
   		~GraphicsWidget();
   		void assignBoard(Board* b);
   		void moveTile(GUITile* tile);
   	private slots:
   		void handleTimer();
   	private:
   		Board* board;
   		QLabel* out;
   		GUITile* moving;
   		QTimer* timer;
};

#endif
