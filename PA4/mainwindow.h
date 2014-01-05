/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QGraphicsView>
#include <QListView>
#include "graphicswidget.h"
#include "userinputwidget.h"


class MainWindow : public QMainWindow
{ Q_OBJECT
	public:
		MainWindow();
		~MainWindow();
	private slots:
		void startGame();
		void quitGame();
		void runHeuristic();
	private:
		GraphicsWidget* mainViewWidget;
		QGraphicsView* gameView;
		Board* b;
		UserInputWidget* uiw;
		QLabel* errorLabel;
		QRadioButton *manhattanRadio, *oopRadio;
		QListView* heuristicResults;
};
#endif
