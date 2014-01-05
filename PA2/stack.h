/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef STACK_H
#define STACK_H

#include "llist.h"

/**
 * Declaration of Stack LIFO ADT
 */
template <typename T>
class Stack : public LList<T>
{
	public:
		Stack();
		~Stack();
		void push(const T& val);
		void pop();
		T& front();
};

/**
 * Creates a new stack
 */
template <typename T>
Stack<T>::Stack() : LList<T>()
{
	
}

/**
 * Destroys the stack
 */
template <typename T>
Stack<T>::~Stack()
{
	this->clear();
}

/**
 * Pushes the given value on top
 * @param val the value to put on top
 */
template <typename T>
void Stack<T>::push(const T& val)
{
	this->insert(0,val);
}

/**
 * Removes the top value
 */
template <typename T>
void Stack<T>::pop()
{
	this->pop_front();
}

/**
 * Gets the top value
 * @return the top value
 */
template<typename T>
T& Stack<T>::front()
{
	return this->peek_front();
}

#endif