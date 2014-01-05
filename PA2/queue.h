/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "llist.h"

using namespace std;

/**
 * FIFO ADT
 */
template <typename T>
class Queue : public LList<T>
{
	public:
		Queue();
		~Queue();
		void push_back(const T& new_val);
		void pop_front();
		T& front() const;
		T& back() const;
};

/**
 * Creates a new Queue
 */
template <typename T>
Queue<T>::Queue() : LList<T>()
{

}

/**
 * Deletes all contents of Queue
 */
template <typename T>
Queue<T>::~Queue()
{
	this->clear();
}

/**
 * Pushes a value to the back of the Queue
 * @param new_val value to be added
 */
template <typename T>
void Queue<T>::push_back(const T& new_val)
{
	LList<T>::push_back(new_val);
}

/**
 * Removes the front value of the queue
 */
template <typename T>
void Queue<T>::pop_front()
{
	LList<T>::pop_front();
}

/**
 * Returns the value at the front of the Queue
 * @return the front of the queue
 */
template <typename T>
T& Queue<T>::front() const
{
	try
	{
		return this->at(0);
	}
	catch(invalid_argument e)
	{
		throw invalid_argument("No front to an empty queue.");
	}
}

/**
 * Returns the back of the Queue
 * @return the back of the Queue
 */
template <typename T>
T& Queue<T>::back() const
{
	try
	{
		return at((this->size())-1);
	}
	catch(invalid_argument e)
	{
		throw invalid_argument("No back to an empty queue.");
	}
}
#endif