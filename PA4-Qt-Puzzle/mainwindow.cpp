/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#include <QToolBar>
#include <QAction>
#include <QDockWidget>
#include <QLineEdit>
#include <iostream>
#include <sstream>
#include <QLabel>
#include <cstdlib>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

#include "mainwindow.h"
#include "userinputwidget.h"
#include "graphicswidget.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "mylist.h"

using namespace std;

/**
 * Constructs a new MainWindow
 */
MainWindow::MainWindow()
{
	QToolBar* myBar = new QToolBar();
	QAction* startBut = new QAction("StartGame",this);
	myBar->addAction(startBut);
	connect(startBut,SIGNAL(triggered()), this,SLOT(startGame()));
	
	QAction* quitBut = new QAction("QuitGame",this);
	myBar->addAction(quitBut);
	connect(quitBut,SIGNAL(triggered()), this,SLOT(quitGame()));
	
	addToolBar(myBar);
	QDockWidget* qdw = new QDockWidget();
	uiw = new UserInputWidget();
	qdw->setWidget(uiw);
	addDockWidget(Qt::TopDockWidgetArea,qdw);
	
	errorLabel = new QLabel("");
	QDockWidget* oBar = new QDockWidget();
	oBar->setWidget(errorLabel);
	addDockWidget(Qt::BottomDockWidgetArea,oBar);
	
	QWidget* sideHeuristic = new QWidget();
	QVBoxLayout* sideBox = new QVBoxLayout();
	QFormLayout* sideForm = new QFormLayout();
	
	manhattanRadio = new QRadioButton();
	oopRadio = new QRadioButton();
	sideForm->addRow(new QLabel("Manhattan Heuristic"),manhattanRadio);
	sideForm->addRow(new QLabel("Out of Place Heuristic"),oopRadio);
	sideBox->addLayout(sideForm);
	QPushButton *runButton = new QPushButton("Run Heuristic");
	sideBox->addWidget(runButton);
	connect(runButton, SIGNAL(clicked()),this,SLOT(runHeuristic()));
	heuristicResults = new QListView();
	sideBox->addWidget(heuristicResults);
	
	sideHeuristic->setLayout(sideBox);
	QDockWidget* hBar = new QDockWidget();
	hBar->setWidget(sideHeuristic);
	addDockWidget(Qt::RightDockWidgetArea,hBar);
	
	mainViewWidget = new GraphicsWidget(this,errorLabel);
	gameView = new QGraphicsView(mainViewWidget);
	gameView->setFixedSize(QSize(600,600));
	setCentralWidget(gameView);
	b = NULL;
}

/**
 * Destroys the main window
 */
MainWindow::~MainWindow()
{
	
}
 
 /**
  * Starts the game based on user input in boxes
  */
void MainWindow::startGame()
{
	errorLabel->setText(QString(""));
	stringstream ss;
	int dim;
	int seed;
	int numMoves;
	
	ss << uiw->getBoardSize();
	ss >> dim;
	
	if(ss.fail() || ss.rdbuf()->in_avail() != 0 || dim == 0 ||static_cast<int>(sqrt(dim)) != sqrt(dim))
	{
		errorLabel->setText(QString("Invalid value in dimension"));
		return;
	}
	
	stringstream ss2;
	
	ss2 << uiw->getNumMoves();
	ss2 >> numMoves;
	
	
	if(ss2.fail() || ss2.rdbuf()->in_avail() != 0)
	{
		errorLabel->setText(QString("Invalid value in num moves"));
		return;
	}
	
	stringstream ss3;
	
	ss3 << uiw->getSeed();
	ss3 >> seed;
	
	if(ss3.fail() || ss3.rdbuf()->in_avail() != 0)
	{
		errorLabel->setText(QString("Invalid value in seed"));
		return;
	}
	
	b = new Board(dim,numMoves,seed);
	mainViewWidget->assignBoard(b);
}

/**
 * Runs the selected heuristic method and outputs results
 */
void MainWindow::runHeuristic()
{
	if(b == NULL)
	{
		errorLabel->setText(QString("You need to start a game before running this."));
		return;
	}
	PuzzleHeuristic* heur;
	if(manhattanRadio->isChecked())
	{
		heur = new ManhattanHeuristic();
	}
	else if(oopRadio->isChecked())
	{
		heur = new OutOfPlaceHeuristic();
	}
	else
	{
		errorLabel->setText(QString("Please select a heuristic before running this."));
		return;
	}
	PuzzleSolver solver(*b);
	solver.run(heur);
	MyList<int>* solutionSet = solver.getSolutionSet();
	QStringList* stringList = new QStringList();

	for(int i = 0; i < solutionSet->size();i++)
	{
		stringList->push_back(QString::number(solutionSet->at(i)));
	}
	QStringListModel* stringModel = new QStringListModel(*stringList);
	heuristicResults->setModel(stringModel);
	
}

/**
 * Quits the game
 */
void MainWindow::quitGame()
{
	close();
}
