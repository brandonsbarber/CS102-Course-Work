/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * A structure for an item
 */
template <typename T>
struct Item {
    T val;
    Item<T> *next;
};

/**
 * LinkedList!
 */
template <typename T>
class LList
{
	public:
		LList();
		~LList();
		bool empty() const;
    	int size() const;
    	void push_back(const T& new_val);
    	void pop_front();
    	T& peek_front() const;
    	T& at(int loc) const;
		bool remove(const T& val);
    	void clear();
    	T& operator[](int loc) const;
    	void insert(int loc, const T& val);
    private:
    	Item<T>* getNodeAt(int loc) const;
    	Item<T>* head_;
};

/**
 * Creates a new Linked List
 */
template <typename T> 
LList<T>::LList()
{
	head_ = NULL;
}

/**
 * Destroys the LinkedList
 */
template <typename T>
LList<T>::~LList()
{
	clear();
}

/**
 * Returns if the list is empty
 * @return if the list is empty
 */
template <typename T>
bool LList<T>::empty() const
{
	//If size() returns 0, a.k.a false, this method will return true
	return size() == 0;
}

/**
 * Gets the size of the list
 * @return the size of the list
 */
template <typename T>
int LList<T>::size() const
{
	int size = 0;
	Item<T>* temp = head_;
	//Loops through all nodes
	while(temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return size;
}

/**
 * Gets the node at the given index
 * @param the location to look to
 * @return the node
 */
template <typename T>
Item<T>* LList<T>::getNodeAt(int loc) const
{
	//if out of bounds
	if(loc >= size() || loc < 0)
	{
		throw invalid_argument("Index out of bounds!");
	}
	Item<T>* temp = head_;
	//loop through
	while(loc > 0 && temp != NULL)
	{
		temp = temp->next;
		loc--;
	}
	return temp;
}

/**
 * Pushes given value to the back of the list
 * @param new_val the value to be pushed
 */
template <typename T> 
void LList<T>::push_back(const T& new_val)
{
	Item<T>* toAdd = new Item<T>;
	toAdd->val = new_val;
	toAdd->next = NULL;
	//If there is nothing
	if(head_ == NULL)
	{
		head_ = toAdd;
	}
	else
	{
		Item<T>* temp = head_;
		//Loop to end
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = toAdd;
	}
} 

/**
 * Removes the front element
 */
template <typename T> 
void LList<T>::pop_front()
{
	if(head_ != NULL)
	{
		Item<T>* toDelete = head_;
		head_ = head_->next;
		delete toDelete;
	}
}

/**
 * Gets the front element
 * @return the front element
 */
template <typename T> 
T& LList<T>::peek_front() const
{
	if(head_ == NULL)
	{
		throw invalid_argument("Cannot peek_front on empty list");
	}
	return head_->val;
}

/**
 * Gets the value at the given index
 * @param loc the location to look at
 * @return the value
 */
template <typename T>
 T& LList<T>::at(int loc) const
 {
 	return getNodeAt(loc)->val;
 }
 
 /**
  * Removes the given value
  * @param the value to remove
  * @return if the value was removed
  */
 template <typename T>
 bool LList<T>::remove(const T& val)
 {
 	//if it is the head
 	if(head_ != NULL && head_->val == val)
 	{
 		pop_front();
 		return true;
 	}
 	Item<T>* temp = head_;
 	//loop through and stop one before
 	while(temp != NULL && temp->next != NULL && temp->next->val != val)
 	{
 		temp = temp->next;
 	}
 	if(temp == NULL || temp->next == NULL)
 	{
 		return false;
 	}
 	else
 	{
 		Item<T>* toDelete = temp->next;
 		temp->next = temp->next->next;
 		delete toDelete;
 		return true;
 	}
 }

/**
 * Deletes all values in the list
 */
template <typename T>
void LList<T>::clear()
{
	while(head_ != NULL)	//while there's still stuff in it
	{
		Item<T>* temp = head_->next;
		delete head_;
		head_ = temp;
	}
}

/**
 * See at(int loc)
 */
template <typename T>
T& LList<T>::operator[](int loc) const
{
	return at(loc);
}

/**
 * Inserts a value at the given index
 * @param loc the index to push to
 * @param val the value to push
 */
template <typename T>
void LList<T>::insert(int loc, const T& val)
{
	Item<T>* newItem = new Item<T>;
	newItem->val = val;
	//If pushing to front
	if(loc == 0)
	{
		newItem->next = head_;
		head_ = newItem;
	}
	else
	{
		Item<T>* temp = head_;
		//Stop one before
		while(loc > 1 && temp != NULL && temp->next != NULL)
		{
			temp= temp->next;
			loc--;
		}
		newItem->next = temp->next;
		temp->next = newItem;
	}
}
 
#endif