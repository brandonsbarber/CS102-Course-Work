/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */

#include "puzzle_move.h"

/**
 * Creates a default puzzle move based on the initial board
 * @param b the board to use
 */
PuzzleMove::PuzzleMove(Board &b)
{
	tileMove_ = -1;
	b_ = new Board(b);
	g_ = 0;
	h_ = 0;				//doesn't initialize due to need for heuristic
	prev_ = NULL;
}

/**
 * Creates a puzzle move based on the previous move
 * @param tile the tile moved
 * @param b the updated board based on that move
 * @param parent the previous move
 */
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
	prev_ = parent;
	tileMove_ = tile;
	b_ = new Board(*b);
	g_ = prev_->g_ + 1;
	h_ = 0;				//doesn't initialize due to need for heuristic
}

/**
 * Destroys the object
 */
PuzzleMove::~PuzzleMove()
{
	delete b_;
	//doesn't delete prev_ because then we get multiple delete errors
}

/**
 * Determines if this move is less than the given move
 * @param p the move to compare to
 * @return whether move is less
 */
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
	if((g_ + h_) < (p.g_ + p.h_))
	{
		return true;
	}
	else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Determines if this move is more than the given move
 * @param p the move to compare to
 * @return whether move is more
 */
bool PuzzleMove::operator>(const PuzzleMove& p) const
{
	if( (g_ + h_) > (p.g_ + p.h_) )
	{
		return true;
	}
	else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Determines if move is same as this one
 * @param p the move to compare
 * @return if move is the same
 */
bool PuzzleMove::operator==(const PuzzleMove& p) const
{
	return tileMove_ == p.tileMove_ && *(p.b_) == *b_ && g_ == p.g_ && h_ == p.h_;
}