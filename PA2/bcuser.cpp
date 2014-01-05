/* Brandon Barber
 * bsbarber@usc.edu
 */
#include <string>
#include "bcuser.h"
#include "user.h"
#include "mylist.h"

using namespace std;

/**
 * Constructs a default BCUser
 */
BCUser::BCUser() : User()
{
	dist_ = -1;
	numsp_ = 0;
	delta_ = 0;
	bc_ = 0;
}

/**
 * Constructs a BCUser
 * @param name the name of the user
 * @param age the age of the user
 * @param zip the zip of the user
 */
BCUser::BCUser(string name, int age, string zip) : User(name,age,zip)
{
	dist_ = -1;
	numsp_ = 0;
	delta_ = 0;
	bc_ = 0;
}

/**
 * Destroys the user
 */
BCUser::~BCUser(){}

/**
 * Gets the distance of the user
 * @return the distance of the user
 */
int BCUser::getDist() const
{
	return dist_;
}

/**
 * Gets the number of paths of the user
 * @return the number of paths of the user
 */
int BCUser::getNumPath() const
{
	return numsp_;
}

/**
 * Gets the predecessors of the user
 * @return the predecessors of the user
 */
MyList<int>* BCUser::getPreds()
{
	return &preds_;
}

/**
 * Gets the delta of the user
 * @return the delta of the user
 */
double BCUser::getDelta() const
{
	return delta_;
}

/**
 * Gets the BC of the user
 * @return the BC of the user
 */
double BCUser::getBC() const
{
	return bc_;
}

/**
 * Sets the distance of the user
 * @param dist the distance of the user
 */
void BCUser::setDist(int dist)
{
	dist_ = dist;
}

/**
 * Sets the number of paths of the user
 * @param path the number of paths of the user
 */
void BCUser::setNumPath(int path)
{
	numsp_ = path;
}

/**
 * Sets the delta of the user
 * @param path the delta of the user
 */
void BCUser::setDelta(double delta)
{
	delta_ = delta;
}

/**
 * Sets the BC of the user
 * @param path the BC of the user
 */
void BCUser::setBC(double bc)
{
	bc_ = bc;
}