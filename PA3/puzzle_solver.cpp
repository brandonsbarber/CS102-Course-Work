/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

/**
 * Constructs a new Puzzle Solver object that will solve the given board
 * @param b the board to solve
 */
PuzzleSolver::PuzzleSolver(const Board &b)
{
	solution_ = new MyList<int>();
	expansions_ = 0;
	b_ = new Board(b);
}

/**
 * Destroys the Puzzle Solver
 */
PuzzleSolver::~PuzzleSolver()
{
	delete solution_;
	delete b_;
}

/**
 * Solves the puzzle based on the given heuristic method
 * @param ph the heuristic method to use
 * @return the number of expansions checked to solve the problem
 */
int PuzzleSolver::run(PuzzleHeuristic *ph)
{
	expansions_ = 0;
	solution_->clear();
	
	PMMinList minList;
	BoardSet board;
	vector<Board*> garbage;
	set<PuzzleMove*> garbageMove;
	
	minList.push(new PuzzleMove(*b_));
	board.insert(b_);
	while(!minList.empty())
	{
		PuzzleMove* move = minList.top();minList.pop();
		garbage.push_back(new Board(*(move->b_)));
		garbageMove.insert(move);
		if(move->b_->solved())
		{
			while(move->prev_ != NULL)
			{
				solution_->push_back(move->prev_->b_->getValue(move->tileMove_));
				PuzzleMove* temp = move;
				garbageMove.erase(garbageMove.find(move));
				move = move->prev_;
				delete temp;
			}
			break;
		}
		map<int, Board*> potMoves = move->b_->potentialMoves();
		map<int, Board*>::iterator it;
		for(it= potMoves.begin(); it != potMoves.end(); it++)
		{
			Board* currentBoard = it->second;
			if(board.find(currentBoard) == board.end())
			{
				PuzzleMove* pMove = new PuzzleMove(it->first,currentBoard,move);
				pMove->h_ = ph->compute(pMove->b_->getTiles(),pMove->b_->getSize());
				board.insert(pMove->b_);
				delete currentBoard;
				minList.push(pMove);
				expansions_++;
			}
			else
			{
				delete currentBoard;
			}
		}
	}
	for(unsigned int i = 0; i < garbage.size(); i++)
	{
		delete garbage[i];
	}
	while(!minList.empty())
	{
		delete minList.top();
		minList.pop();
	}
	for(set<PuzzleMove*>::iterator it = garbageMove.begin(); it != garbageMove.end(); it++)
	{
		delete *it;
	}
	flipSolutionSet();
	delete ph;
	return expansions_;
}

/**
 * Allows acces to the MyList of the solution steps
 * @return MyList of solution steps
 */
MyList<int>* PuzzleSolver::getSolutionSet()
{
	return solution_;
}

/**
 * Gets the number of expansions taken in order to solve the problem
 * @return the number of expansions
 */
int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}

/**
 * Flips all values in the set (mirrors)
 */
void PuzzleSolver::flipSolutionSet()
{
	int front = 0, back = solution_->size()-1;
	while(front < back)
	{
		int temp = solution_->operator[](front);
		solution_->set(front,solution_->operator[](back));
		solution_->set(back,temp);
		front ++;
		back --;
	}
}
