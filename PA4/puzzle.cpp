/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */
#include <iostream>
#include <cstdlib>
#include <deque>
#include <string>
#include <stdexcept>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

/*int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cerr << "Usage: ./puzzle size initMoves seed" << endl;
		return 1;
	}
	
	int size, initMoves, seed;
	
	size = atoi(argv[1]);
	initMoves = atoi(argv[2]);
	seed = atoi(argv[3]);
	
	Board b(size,initMoves,seed);
	//Implementation of gameplay
	while(!b.solved())
	{
		cout << b << endl << endl;
		int move;
		
		while(true)
		{
			cout << "Enter tile number to move or -1 for a cheat: ";
			cin >> move;
		
			if(cin.fail() || move > b.getSize() || move < -1)
			{
				cin.clear();
				cin.ignore(100000,'\n');
				if(move > b.getDim() || move < -1)
				{
					cout << "Value out of range. Please try again."<<endl;
				}
				else
				{
					cout << "Invalid value. Please try again."<<endl;
				}
				continue;
			}
			else if( move != -1 && (b.getTile(move) != b.getNorth() && b.getTile(move) != b.getWest() && b.getTile(move) != b.getEast() && b.getTile(move) != b.getSouth()))
			{
				cout << "Invalid move. Tile locked. Try again." << endl;
				continue;
			}
			break;
		}
		cout << endl;
		if(move == -1)
		{
			cout << "Try this sequence: ";
			PuzzleSolver pSolve(b);
			pSolve.run(new OutOfPlaceHeuristic());
			MyList<int>* solutionSet = pSolve.getSolutionSet();
			for(int i = 0; i < solutionSet->size();i++)
			{
				int indexMove = solutionSet->operator[](i);
				cout << indexMove << " ";
			}
			cout << endl << "(Expansions = "<<pSolve.getNumExpansions() << ")"<<endl<<endl;
			continue;
		}
		b.move(b.getTile(move));
	}
	
	cout << "Congratulations! You have completed the puzzle."<<endl;
	return 0;
}*/
