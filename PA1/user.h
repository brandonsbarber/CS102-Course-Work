/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef USER_H
#define USER_H
#include <string>
#include "mylist.h"

using namespace std;

/**
 * User class with fields for name, age, and zip code
 */
class User
{
	public:
		User();
		User(string name, int age, int zip);
		~User();
		string getName() const;
		int getAge() const;
		int getZip() const;
		MyList<int>* getFriends();
		
		void setName(string name);
		void setAge(int age);
		void setZip(int zip);
		
	private:
		string name_;
		int age_, zip_;
		MyList<int> data_;
};

#endif
