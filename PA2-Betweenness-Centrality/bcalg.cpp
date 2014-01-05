/**
 * Brandon Barber
 * bsbarber@usc.edu
 */
#include "bcalg.h"
#include "bcuser.h"
#include "mylist.h"
#include "stack.h"
#include "queue.h"

/**
 * Computes the BC values for all BCUsers supplied by using the provided algorithm
 * @param userList list of all the users
 * @return a MyList of all BC values
 */
MyList<double>* BCAlg::computeBC(MyList<BCUser*> &userList)
{
	//Set all values to 0
	for(int i = 0; i < userList.size() ; i++)
	{
		userList.at(i)->setBC(0);
	}
	
	//Breadth first search
	for(int i = 0; i < userList.size() ; i++)
	{
		BCUser* source = userList.at(i);
		//loops through all children
		for(int traverse = 0; traverse < userList.size() ; traverse++)
		{
			BCUser* user = userList.at(traverse);
			user->getPreds()->clear();
			user->setNumPath(0);
			user->setDist(-1);
			user->setDelta(0);
		}
		source->setNumPath(1);
		source->setDist(0);
		
		Stack<BCUser*> stack;
		Queue<BCUser*> queue;
		
		queue.push_back(source);
		
		//While you haven't navigated the graph
		while(!queue.empty())
		{
			BCUser* current = queue.front();
			queue.pop_front();
			stack.push(current);
			MyList<int>* friends = current->getFriends();
			for(int friendTraverse = 0; friendTraverse <  friends->size(); friendTraverse++)
			{
				BCUser* myFriend = userList.at(friends->at(friendTraverse));
				if(myFriend->getDist() == -1)
				{
					myFriend->setDist(current->getDist() + 1);
					queue.push_back(myFriend);
				}
				if(myFriend->getDist() == current->getDist() + 1)
				{
					myFriend->setNumPath(myFriend->getNumPath() + current->getNumPath());
					myFriend->getPreds()->push_back(findNum(userList,current));
				}
			}
		}
		
		//Allows for backwards traversal
		while(!stack.empty())
		{
			BCUser* current = stack.front();
			stack.pop();
			MyList<int>* preds = current->getPreds();
			for(int friendTraverse = 0; friendTraverse < preds->size(); friendTraverse++)
			{
				BCUser* myFriend = userList.at(preds->at(friendTraverse));
				double newDelta = myFriend->getDelta() + (1.0*myFriend->getNumPath()/current->getNumPath())*(1 + current->getDelta());
				myFriend->setDelta(newDelta);
			}
			current->setBC(current->getBC() + current->getDelta());
		}
	}
	
	//Find min and max
	MyList<double>* deltaVals = new MyList<double>();
	double min = -1;
	double max = -1;
	for(int i = 0; i < userList.size() ; i++)
	{
		double val = userList.at(i)->getBC();
		if(min == -1 || min > val)
		{
			min = val;
		}
		if(max == -1 || max < val)
		{
			max = val;
		}
	}
	
	//Normalize values
	for(int i = 0; i < userList.size() ; i++)
	{
		double normVal = (userList.at(i)->getBC() - min) / (max - min);
		userList.at(i)->setBC(normVal);
		deltaVals->push_back(userList.at(i)->getBC());
	}
	
	return deltaVals;
}

/**
 * Finds the given user in the list
 * @param userList the list to search through
 * @param user the user to find
 * @return the index of the user
 */
int BCAlg::findNum(MyList<BCUser*> &userList, BCUser* user)
{
	for(int i = 0; i < userList.size(); i++)
	{
		if(userList.at(i) == user)
		{
			return i;
		}
	}
	return -1;
}