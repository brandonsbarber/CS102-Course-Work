/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef BCUSER_H
#define BCUSER_H

#include <string>
#include "user.h"
#include "mylist.h"

using namespace std;

/**
 * BCUser class
 */
class BCUser : public User
{
	public:
		BCUser();
		BCUser(string name, int age, string zip);
		~BCUser();
		
		int getDist() const;
		int getNumPath() const;
		MyList<int>* getPreds();
		double getDelta() const;
		double getBC() const;
		
		void setDist(int dist);
		void setNumPath(int path);
		void setDelta(double delta);
		void setBC(double bc);
	private:
		int dist_;
		int numsp_;
		MyList<int> preds_;
		double delta_;
		double bc_;
};

#endif
