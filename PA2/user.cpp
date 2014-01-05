/* Brandon Barber
 * bsbarber@usc.edu
 */
#include <string>
#include "user.h"
#include "mylist.h"

using namespace std;

/**
 * Initializes an empty user with default unset values
 */
User::User()
{
	name_ = "??";
	age_ = -1;
	zip_ = -1;
}

/**
 * Initializes user with the given values
 * @param name the name of the user
 * @param age the age of the user
 * @param zip the zipcode of the user
 */
User::User(string name, int age, string zip)
{
	name_ = name;
	age_ = age;
	zip_ = zip;
}

/**
 * Deconstructs the user
 */
User::~User() {}

/**
 * Gets the name of the user
 * @return the name of the user
 */
string User::getName() const
{
	return name_;
}

/**
 * Gets the age of the user
 * @return age of the user
 */
int User::getAge() const
{
	return age_;
}

/**
 * Gets the zip code of the user
 * @return the zip code of the user
 */
string User::getZip() const
{
	return zip_;
}

/**
 * Gets the friends list of the user
 * @return pointer to the friends list of the user
 */
MyList<int>* User::getFriends()
{
	return &data_;
}

/**
 * Sets name of the user to the given value
 * @param name the new name
 */
void User::setName(string name)
{
	name_ = name;
}

/**
 * Sets age of the user to the given value
 * @param age the new age
 */
void User::setAge(int age)
{
	age_ = age;
}

/**
 * Sets zip of the user to the given value
 * @param zip the new zip
 */
void User::setZip(string zip)
{
	zip_ = zip;
}

/**
 * Sets zip of the user to the given value
 * @param zip the new zip
 */
 void User::setZip(int zip)
 {
 	zip_ = ""+zip;
 }