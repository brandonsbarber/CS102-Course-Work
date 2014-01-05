/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef BCALG_H
#define BCALG_H

#include "mylist.h"
#include "bcuser.h"

/**
 * Class for computing BC values
 */
class BCAlg
{
	public:
		static MyList<double>* computeBC(MyList<BCUser*> &userList);
		static int findNum(MyList<BCUser*> &userList, BCUser* user);
};

#endif