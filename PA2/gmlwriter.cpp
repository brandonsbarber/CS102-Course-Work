/* Brandon Barber
 * bsbarber@usc.edu
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mylist.h"
#include "user.h"
#include "gmlwriter.h"
#include "bcuser.h"

using namespace std;

/**
 * Converts an int into a string
 * @param i the int to convert
 * @return the converted string
 */
string toString(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

/**
 * Base method for writing to file
 * @param fn the name of the file
 * @param users the list of users to write to file
 */
void GMLWriter::write(char* fn, MyList<User*>* users)
{
	//cout << "Writing to file!"<< endl;
	
	ofstream out;
	
	out.open(fn);
	out << "graph [\n";
	for(int i = 0 ; i < (*users).size(); i ++)		//write nodes
	{
		out << toNode(i,(*users).at(i));
	}
	for(int i = 0 ; i < (*users).size(); i ++)		//write edges
	{
		out << toEdge(i,(*users).at(i));
	}
	out << "]";
}

/**
 * Converts a User to a string node
 * @param id the id number of the user
 * @param u the user to write to node
 * @return converted user
 */
string GMLWriter::toNode(int id, User* u)
{
	string nodeString = "    node [\n",spaces = "        ";
	
	nodeString += spaces + "id " + toString(id) + "\n";
	nodeString += spaces + "name \"" + u->getName() + "\"\n";
	nodeString += spaces + "age "  + toString(u->getAge()) + "\n";
	nodeString += spaces + "zip "  + u->getZip() + "\n";
	nodeString += "    ]\n";
	return nodeString;
}

/**
 * Extracts all user relationships for edge nodes
 * @param id the id number of the user
 * @param u the user to write to node
 * @return all edges for given user
 */
string GMLWriter::toEdge(int id, User* u)
{
	string outputString = "";
	string edgeString = "    edge [\n",spaces = "        ";
	for(int i = 0; i < u->getFriends()->size(); i++)		//Loop through all relationship
	{
		
		outputString += edgeString;
		outputString += spaces + "source "+toString(id)+"\n";
		outputString += spaces + "target "+toString(u->getFriends()->at(i))+"\n";
		outputString += "    ]\n";
	}
	return outputString;
}



/**
 * Base method for writing to file
 * @param fn the name of the file
 * @param users the list of users to write to file
 */
void GMLWriter::write(char* fn, MyList<BCUser*>* users)
{
	//cout << "Writing to file!"<< endl;
	
	ofstream out;
	
	out.open(fn);
	out << "graph [\n";
	for(int i = 0 ; i < (*users).size(); i ++)		//write nodes
	{
		out << toNode(i,(*users).at(i));
	}
	for(int i = 0 ; i < (*users).size(); i ++)		//write edges
	{
		out << toEdge(i,(*users).at(i));
	}
	out << "]";
}

/**
 * Converts a User to a string node
 * @param id the id number of the user
 * @param u the user to write to node
 * @return converted user
 */
string GMLWriter::toNode(int id, BCUser* u)
{
	string nodeString = "    node [\n",spaces = "        ";
	
	nodeString += spaces + "id " + toString(id) + "\n";
	nodeString += spaces + "name \"" + u->getName() + "\"\n";
	nodeString += spaces + "age "  + toString(u->getAge()) + "\n";
	nodeString += spaces + "zip "  + u->getZip() + "\n";
	nodeString += "    ]\n";
	return nodeString;
}

/**
 * Extracts all user relationships for edge nodes
 * @param id the id number of the user
 * @param u the user to write to node
 * @return all edges for given user
 */
string GMLWriter::toEdge(int id, BCUser* u)
{
	string outputString = "";
	string edgeString = "    edge [\n",spaces = "        ";
	for(int i = 0; i < u->getFriends()->size(); i++)		//Loop through all relationship
	{
		
		outputString += edgeString;
		outputString += spaces + "source "+toString(id)+"\n";
		outputString += spaces + "target "+toString(u->getFriends()->at(i))+"\n";
		outputString += "    ]\n";
	}
	return outputString;
}

/**
 * Writes out the BC scores to a file
 * @param fn the name of the file
 * @param users the users to loop through
 */
void GMLWriter::writeBC(char* fn, MyList<double>* results)
{
	ofstream out;
	out.open(fn);
	
	for(int i = 0; i < results->size(); i++)
	{
		double bc = results->at(i);
		out << i << " " << bc;
		if(i != results->size() -1)
		{
			out << endl;
		}
	}
}