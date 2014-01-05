/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#include <QtGui/QApplication>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <string>
#include <stdexcept>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "mainwindow.h"

/**
 * Main method for executing the game
 * @param argc number of arguments supplied
 * @param argv the argument supplied
 */
int main(int argc, char* argv [])
{
	QApplication a(argc,argv);
	MainWindow w;
	w.show();
	return a.exec();
}
