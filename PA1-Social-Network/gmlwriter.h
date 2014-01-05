/* Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef GML_WRITER_H
#define GML_WRITER_H
#include "user.h"
#include "mylist.h"

//Class declaration for the GMLWriter
class GMLWriter
{
	public:
		static void write(char* fn, MyList<User*>* users);
		static string toNode(int id, User* u);
		static string toEdge(int id, User* u);
};

#endif
