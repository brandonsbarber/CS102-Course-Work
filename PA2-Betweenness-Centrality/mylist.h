/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

//List Class Declaration
template <typename T> class MyList
{
	public:
		MyList<T>();
		~MyList<T>();
		void push_back(T val);
		int size();
		T& at(int loc);
		bool remove(T val);
		T& pop(int loc);
		T& operator[](int loc);
		void clear();
		static const int INIT_SIZE = 10;
	private:
		int size_;
		int capacity_;
		T* data_;
};

/**
 * Constructs a MyList with the default capacity
 */
template<typename T> MyList<T>::MyList()
{
	data_ = new T[INIT_SIZE];
	capacity_ = INIT_SIZE;
	size_ = 0;
}

/**
 * Destructor of MyList
 */
template<typename T> MyList<T>::~MyList()
{
	delete [] data_;
}

/**
 * Adds the given value to the end of the list, resizing if necessary
 * @param val the value to add
 */
template<typename T> void MyList<T>::push_back(T val)
{
	//If size will be out of bounds
	if(size_ == capacity_)
	{
		//Creating a copy
		T* data_clone = new T[capacity_*2];
		//Loop to copy all values to new array
		for(int i = 0; i < capacity_; i++)
		{
			data_clone[i] = data_[i];
		}
		//Deallocate the memory for data_
		delete [] data_;
		//Make data_ the other array
		data_ = data_clone;
		capacity_ *= 2;
	}
	data_[size_++] = val;
}

/**
 * Gets the size of the list
 * @return size of the list
 */
template<typename T> int MyList<T>::size()
{
	return size_;
}

/**
 * Returns a reference to the piece of data at the given location
 * @param loc the index to reference
 * @return the piece of data
 */
template<typename T> T& MyList<T>::at(int loc)
{
	if(loc >= size_  || loc < 0)		//If out of bounds
	{
		throw invalid_argument("Index Out of Bounds in At");
	}
	return data_[loc];
}

/**
 * Removes the given value
 * @param val the value to remove
 * @return whether or not the item was removed
 */
template<typename T> bool MyList<T>::remove(T val)
{
	for(int i = 0; i < size_; i++)
	{
		if(data_[i] == val)
		{
			for(int deleteIndex = i; deleteIndex < size_-1; deleteIndex++)		//Shift all values
			{
				data_[deleteIndex] = data_[deleteIndex+1];
			}
			size_--;
			return true;
		}
	}
	return false;
}

/**
 * Removes and returns the object at the given location
 * @param loc the location to access
 * @return the object removed
 */
template<typename T> T& MyList<T>::pop(int loc)
{
	if(loc >= size_ || loc < 0)		//If out of bounds
	{
		throw invalid_argument("Index Out of Bounds in Pop");
	}
	T object = data_[loc];
	remove(object);
	return object;
}

/**
 * Same as at() with [] syntax
 * @param loc the location to access
 * @return the object at the location
 */
template<typename T> T& MyList<T>::operator[](int loc)
{
	return at(loc);
}

/**
 * Clears all values from the data structure and reinitializes it
 */
template<typename T> void MyList<T>::clear()
{
	delete [] data_;
	data_ = new T[INIT_SIZE];
	capacity_ = INIT_SIZE;
	size_ = 0;
}
#endif