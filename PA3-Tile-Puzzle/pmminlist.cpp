/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */

#include <iostream>
#include "puzzle_move.h"
#include "pmminlist.h"

using namespace std;

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_()
{

}

/**
 * Destructor
 */
PMMinList::~PMMinList()
{

}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest (if 
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::push(PuzzleMove* pm)
{
	std::list<PuzzleMove*>::iterator it = slist_.begin();
	while(it != slist_.end())
	{
		PuzzleMove* move = *it;
		//int f = move->g_ + move->h_;
		if((*pm) < (*move))
		{
			break;
		}
		it++;
		continue;
	}
	slist_.insert(it,pm);
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::pop()
{
	slist_.pop_front();
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return reference to the minimum-scored PuzzleMove*
 */
PuzzleMove* PMMinList::top()
{
	return slist_.front();
}

