/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */

#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

	
/**
 * Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *	@param size Number of tiles for the game.	\
 *			Should be a perfect square (4, 16, 25)
 *	@param numInitMoves Number of tile moves to attempt to scramble the board
 *	@param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
	size_ = size;
	tiles_ = new int[size_];
	int dim = static_cast<int>(sqrt(size_));
	srand(seed);
	for(int i=0; i < size_; i++){
		tiles_[i] = i;
	}
	int blankLoc = 0;
	for(int i=0; i < numInitMoves; i++){
		int r = rand()%4;
		int randNeighbor = -1;
		if(r == 0)
		{
			int n = blankLoc - dim;
			if(n >= 0)
			{
				randNeighbor = n;
			}
		}
		else if(r == 1)
		{
			int w = blankLoc - 1;
			if(blankLoc % dim != 0)
			{
				randNeighbor = w;
			}
		}
		else if(r == 2)
		{
			int s = blankLoc + dim;
			if(s	< size_)
			{
				randNeighbor = s;
			}
		}
		else
		{
			int e = blankLoc + 1;
			if(blankLoc % dim != dim-1)
			{
				randNeighbor = e;
			}
		}
		if(randNeighbor > -1)
		{
			tiles_[blankLoc] = tiles_[randNeighbor];
			tiles_[randNeighbor] = 0;
			blankLoc = randNeighbor;
		}
	}
}


/**
 * Init a board of 4 and scramble it with 5 moves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 */
Board::Board()
{
	size_ = 4;
	tiles_ = new int[size_];
	int dim = static_cast<int>(sqrt(size_));
	srand(1000);
	for(int i=0; i < size_; i++){
		tiles_[i] = i;
	}
	int blankLoc = 0;
	for(int i=0; i < 5; i++){
		int r = rand()%4;
		int randNeighbor = -1;
		if(r == 0)
		{
			int n = blankLoc - dim;
			if(n >= 0)
			{
				randNeighbor = n;
			}
		}
		else if(r == 1)
		{
			int w = blankLoc - 1;
			if(blankLoc % dim != 0)
			{
				randNeighbor = w;
			}
		}
		else if(r == 2)
		{
			int s = blankLoc + dim;
			if(s	< size_)
			{
				randNeighbor = s;
			}
		}
		else
		{
			int e = blankLoc + 1;
			if(blankLoc % dim != dim-1)
			{
				randNeighbor = e;
			}
		}
		if(randNeighbor > -1)
		{
			tiles_[blankLoc] = tiles_[randNeighbor];
			tiles_[randNeighbor] = 0;
			blankLoc = randNeighbor;
		}
	}
}

/**
 * Destroys the board by deleting the array of tiles present.
 */
Board::~Board()
{
	delete [] tiles_;
}

/**
 * Creates a deep copy of the given board
 * @param b the board of which to make a copy
 */
Board::Board(const Board &b)
{
	size_ = b.size_;
	tiles_ = new int[b.size_];
	for(int i = 0; i < b.size_; i++)
	{
		tiles_[i] = b.tiles_[i];
	}
}

/**
 * Constructs a deep copy off of the given Board components as opposed
 * to a full Board object.
 * @param tiles the array of integers representing tiles for the board
 * @param size the size of the new board
 */
Board::Board(int *tiles, int size)
{
	size_ = size;
	tiles_ = new int[size_];
	for(int i = 0; i < size_; i++)
	{
		tiles_[i] = tiles[i];
	}
}

/**
 * Takes the value at the provided index and swaps it with the zero tile
 * @param tile the tile which shall be moved
 */
void Board::move(int tile)
{
	if(tile > size_)
	{
		throw invalid_argument("Tile out of range.");
	}
	for(int i = 0; i < size_; i++)
	{
		if(tiles_[i] == 0)
		{
			tiles_[i] = tiles_[tile];
			tiles_[tile] = 0;
		}
	}
}

/**
 * Generates a map of all potential moves, with keys
 * corresponding to the index moved and the data contained being a pointer
 * to a board with a state matching the moved piece
 * @return map of potential moves
 */
std::map<int, Board*> Board::potentialMoves()
{	
	std::map<int, Board*> potMoves;
	int index = -1;
	if((index = getNorth()) != -1)
	{
		Board* b = new Board(tiles_,size_);
		b->move(index);
		potMoves.insert(std::pair<int,Board*>(index,b));
	}
	if((index = getSouth()) != -1)
	{
		Board* b = new Board(tiles_,size_);
		b->move(index);
		potMoves.insert(std::pair<int,Board*>(index,b));
	}
	if((index = getWest()) != -1)
	{
		Board* b = new Board(tiles_,size_);
		b->move(index);
		potMoves.insert(std::pair<int,Board*>(index,b));
	}
	if((index = getEast()) != -1)
	{
		Board* b = new Board(tiles_,size_);
		b->move(index);
		potMoves.insert(std::pair<int,Board*>(index,b));
	}
	return potMoves;
}

/**
 * Returns if the board is solved (in ascending order)
 * @return whether the board is solved
 */
bool Board::solved()
{
	for(int i = 0; i < size_; i++)
	{
		if(i != tiles_[i])
		{
			return false;
		}
	}
	return true;
}

/**
 * Enables output through streams
 * @param os the stream to write to
 * @param b the board to write
 * @return the completed output stream
 */
std::ostream& operator<<(std::ostream &os, const Board &b)
{
	int dimension = b.getDim();
	int width = 2;
	int factor = 10;
	while(b.getSize() >= factor)
	{
		width++;
		factor *= 10;
	}
	for(int i = 0; i < dimension; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			if(b.tiles_[i*dimension + j] != 0)
			{
				os << setw(width) << b.tiles_[i * dimension + j];
			}
			else
			{
				os << setw(width) << "";
			}
		}
		if(i != dimension - 1)
		{
			os << endl;
		}
	}
	return os;
}

/**
 * Determines if two boards are equal (all values match)
 * @param rhs board to compare with
 * @return whether the boards are equal
 */
bool Board::operator==(const Board& rhs) const
{
	if(size_ != rhs.size_)
	{
		return false;
	}
	for(int i = 0; i < size_; i++)
	{
		if(tiles_[i] != rhs.tiles_[i])
		{
			return false;
		}
	}
	return true;
}

/**
 * Determines if two boards are not equal (not all values match)
 * @param rhs board to compare with
 * @return whether the boards not are equal
 */
bool Board::operator!=(const Board& rhs) const
{
	return !operator==(rhs);
}

/*
 * Returns array of the tiles of the board
 * @return the tiles of the board
 */
int* Board::getTiles()
{
	return tiles_;
}

/**
 * Returns the size of the board
 * @return size of the board
 */
int Board::getSize() const
{
	return size_;
}

/**
 * Gets the index of the given value
 * @param value the value to search for
 * @return the index that value lives at
 */
int Board::getTile(int value) const
{
	for(int i = 0; i < size_; i++)
	{
		if(tiles_[i] == value)
		{
			return i;
		}
	}
	return -1;
}

/**
 * Gets the value at the given index
 * @param tile the index to look at
 * @return the value contained there
 */
int Board::getValue(int tile) const
{
	return tiles_[tile];
}

/**
 * Gets the index of the zero (blank tile)
 * @return index of blank tile
 */
int Board::getZero() const
{
	for(int i = 0; i < size_;i++)
	{
		if(tiles_[i] == 0)
		{
			return i;
		}
	}
	return -1;
}

/**
 * Gets the index of the tile to the North of the blank tile (or -1 if none exists)
 * @return index of northern tile
 */
int Board::getNorth() const
{
	int zero = getZero();
	if(zero / getDim() == 0)
	{
		return -1;
	}
	return zero - getDim();
}

/**
 * Gets the index of the tile to the South of the blank tile (or -1 if none exists)
 * @return index of southern tile
 */
int Board::getSouth() const
{
	int zero = getZero();
	if(zero / getDim() == getDim() - 1)
	{
		return -1;
	}
	return zero + getDim();
}

/**
 * Gets the index of the tile to the West of the blank tile (or -1 if none exists)
 * @return index of western tile
 */
int Board::getWest() const
{
	int zero = getZero();
	if(zero % getDim() == 0)
	{
		return -1;
	}
	return zero - 1;
}

/**
 * Gets the index of the tile to the East of the blank tile(or -1 if none exists)
 * @return index of eastern tile
 */
int Board::getEast() const
{
	int zero = getZero();
	if(zero % getDim() == getDim() - 1)
	{
		return -1;
	}
	return zero + 1;
}

/**
 * Gets the dimension of the board
 * @return the board's dimension
 */
 int Board::getDim() const
 {
 	return static_cast<int>(sqrt(size_));
 }

/**
 * Determines if one board is less than another
 * @param rhs the board to compare with
 * @return if the board is less than the given
 */
bool Board::operator<(const Board& rhs) const
{
	if(size_ < rhs.size_){
		return true;
	}
	bool val = false;
	for(int i=0; i < size_; i++){
		if(tiles_[i] < rhs.tiles_[i]){
			 //val = true;
			 //break;
			 return true;
		 }
		 else if(tiles_[i] > rhs.tiles_[i]){
			 //break;
			 return false;
		 }
	}
	return val;
}


