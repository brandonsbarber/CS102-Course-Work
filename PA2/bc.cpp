/* Brandon Barber
 * bsbarber@usc.edu
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "mylist.h"
#include "user.h"
#include "gmlreader.h"
#include "gmlwriter.h"
#include "llist.h"
#include "stack.h"
#include "queue.h"
#include "bcuser.h"
#include "bcalg.h"

using namespace std;

MyList<BCUser*> users; 

int readFile(char* fileName);
BCUser* parseUser(string line);
void parseEdge(string line);
void processTransactions(char* fileName);
int* findIndexes(string* names);
void removeFriends(int* friends);
void addFriends(int* friends);

/**
 * Runs the program
 * @param argc system argument
 * @param argv array of arguments
 * @return error code
 */
int main(int argc, char *argv[])
{
	//Takes two command line args
	if(argc < 3)	//Not all file names provides
	{
		cerr << "Please provide the input GML file and output file" << endl;
		return 1;
	}
	
	//Parses the input GML
	if(readFile(argv[1]))	//If there was an error in reading
	{
		return 1;
	}
	
 	for(int i = 0; i < users.size(); i++)				//Runs through for display of all friends
 	{
 		cout << "Friends of "<< users.at(i)->getName() << endl;
 	 	for(int in = 0; in < users.at(i)->getFriends()->size(); in++)
 	 	{
 	 		cout << users.at(users.at(i)->getFriends()->at(in))->getName() << endl;
		}
	}
	
	//Computes the BC scores of all users
	MyList<double>* results = BCAlg::computeBC(users);
	for(int i = 0; i < results->size(); i++)
	{
		cout << results->at(i)<<endl;
	}
	
 	GMLWriter::writeBC(argv[2],results);					//Writes to file
 	return 0;
}

/**
 * Reads in the given file and parses all information
 * @param fileName name of the file
 * @return error code
 */
int readFile(char* fileName)
{
	//Declaration of data
	vector<string> names;
	vector<string> edges;
	
	ifstream testIn(fileName);
	if(testIn.fail())			//Checks to see if file can be opened
	{
		cerr << "Cannot open GML input file." << endl;
  		return 1;
  	}
  
  	GMLReader::read(fileName,names,edges);	//Populates the two vectors
  
  	for(unsigned int i = 0; i < names.size(); i++)		//Parses all users
  	{
  		users.push_back(parseUser(names.at(i)));
  	}
  
  	for(unsigned int i = 0; i < edges.size() ; i++)		//Parses all edges
  	{
  		parseEdge(edges.at(i));
	}
	return 0;
}

/**
 * Takes in a line from a file and uses that to parse out a BCUser object
 * @param line the string from which to read
 * @return pointer to the BCUser read from the string
 */
BCUser* parseUser(string line)
{
	//Creating data to use
	stringstream ss(line);
	string garbage,name,zip;
	int age;
	
	while(ss.good())	//While there is still data in the string
	{
		string l;
		ss >> l;
		if(l == "id")	//If ID, read through ID# 
		{
			ss >> l;
		}
		else if( l == "name")
		{
			getline(ss,name,'\"'); 	//Clear first quotes
			getline(ss,name,'\"');	//Read name
		}
		else if(l == "age")	//Age
		{
			ss >> age;
			if(ss.fail())
			{
				age = 0;
				ss.clear();
			}
		}
		else if(l == "zip")	//Zipcode
		{
			ss >> zip;
		}
	}
	return new BCUser(name,age,zip);
}

/**
 * Used on startup to process the edges to be created by default from file. Uses given indexes
 * @param line the line of text to read edge from
 * @param users the MyList containing all users for the program
 */
void parseEdge(string line)
{
	stringstream ss(line);
	int source,target;
	
	while(ss.good())	//While line still contains data
	{
		string l;
		ss >> l;
		if(l == "source")
		{
			ss >> source;
		}
		else if(l == "target")
		{
			ss >> target;
		}
	}
	users[source]->getFriends()->push_back(target);		//Since each edge is listed going both ways, no need for reflexive call
}

/**
 * Reads from command file to process adding and removing of friends
 * @param fileName the name of the command file to be used
 * @param users the MyList of users in the program
 */
void processTransactions(char* fileName)
{
	ifstream in;
	in.open(fileName);
	if(in.fail())		//If no file, skip
	{
		cerr << "Cannot open the command file. Proceeding without it." << endl;
		return;
	}
	
	while(in.good())	//While there are still lines
	{
		try
		{
			string line;	//Use stringstream to prevent line overflow
			getline(in,line,'\n');
			if(line == "")	//If extra white space
			{
				break;
			}
			stringstream ss(line);
			
			char operation;
			string name1,name2;
			
			ss >> operation;	//Read in operation
			if(operation != 'a' && operation != 'r')	//If illegal operation, exception to skip line
			{
				throw invalid_argument("Command operator must be either an 'a' or an 'r'");
			}
			getline(ss,name1,'\"');		//Clear "
			getline(ss,name1,'\"');		//Read name1
			getline(ss,name2,'\"');		//Clear "
			getline(ss,name2,'\"');		//Read name2
			
			string names[] = {name1,name2};
			int* indexes = findIndexes(names);	//Finds user indexes in MyList
			
			switch(operation)		//Determine operation
			{
				case 'a':addFriends(indexes);break;
				case 'r':removeFriends(indexes);break;
			}
		}
		catch(invalid_argument e)	//If invalid in any way
		{
			cout << e.what() << endl;
			cout << "Skipping line." << endl;
		}
	}
}

/**
 * Given a list and an array of names, finds the given indexes of both names and places them in an array of ints
 * @param users the MyList of users in the program
 * @param names the names to look for
 * @return the indexes of the names in the list
 */
int* findIndexes(string* names)
{
	int* indexes = new int[2];
	indexes[0] = -1; indexes[1] = -1;	//Initialize values to something that cannot be reached otherwise
	for(int p = 0; p < 2; p++)		//Loop through given names
	{
		for(int i = 0; i < users.size(); i++)	//Find in list
		{
			if(names[p] == users[i]->getName())
			{
				indexes[p] = i;
				break;
			}
		}
	}
	if(indexes[0] == -1 || indexes[1] == -1)	//If nothing was found
	{
		throw invalid_argument("BCUser cannot be found.");
	}
	return indexes;
}

/**
 * Removes the relationship at the given index
 * @param users the MyList of users
 * @param the indexes of the two users
 */
void removeFriends(int* friends)
{
	//cout << "Defriending: " << users.at(friends[0])->getName() << " and " << users.at(friends[1])->getName()<< endl;
	users.at(friends[0])->getFriends()->remove(friends[1]);
	users.at(friends[1])->getFriends()->remove(friends[0]);
}

/**
 * Adds a relationship at the given index
 * @param users the MyList of users
 * @param the indexes of the two users
 */
void addFriends(int* friends)
{
	//cout << "Friending: " << users.at(friends[0])->getName() << " and " << users.at(friends[1])->getName()<< endl;
	users.at(friends[0])->getFriends()->push_back(friends[1]);
	users.at(friends[1])->getFriends()->push_back(friends[0]);
}