/*
 * @author Brandon Barber
 * bsbarber@usc.edu
 */

#include <cmath>
#include "puzzle_heur.h"

using namespace std;

/**
 * Computes the h value based on the Manhattan Heuristic approach
 * @param tiles the board to look through
 * @param size the size of the array
 * @return total manhattan value for the entire array
 */
int ManhattanHeuristic::compute(int *tiles, int size)
{
	int dim = static_cast<int>(sqrt(size));
	int score = 0;
	for(int i = 0; i < size; i++)
	{
		if(tiles[i] == 0)
		{
			continue;
		}
		int number = tiles[i];
		score += static_cast<int>(abs(1.0*(i%dim - number%dim))) + static_cast<int>(abs(1.0*(i/dim - number/dim)));
	}
	return score;
}

/**
 * Computes the h value based on the OutOfPlaceHeuristic approach
 * @param tiles the board to look through
 * @param size the size of the array
 * @return total out of place value for the entire array
 */
int OutOfPlaceHeuristic::compute(int *tiles, int size)
{
	int number = 0;
	for(int i = 0; i < size; i++)
	{
		if(tiles[i] != i)
		{
			number++;
		}
	}
	return number;
}