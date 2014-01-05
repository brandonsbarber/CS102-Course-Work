# Design Document for PA1

## Purpose/Overview
>This program will provide an interface for User friendship interactions on a social networking site. It will allow for connections to be made between multiple Users.


## Requirements
> This program will allow for the reading in of friendships between Users while allowing for manipulation of these (forming and removing friendships).
> It will also allow for the export of these interactions to a file.


## Classes
> ###Classes to Define:
> ####MyList
>   Dynamical templated array-based list for the holding of Users
>
>**Member Data:**
>   1. size_: the number of items currently in the List
>   2. capacity_: the maximum number of items for the current array size
>   3. data_: array containing the proper data for the List
>   4. INIT_SIZE: base size of 10
>**Functions:**
>   1. push_back: places the given parameter item at the back of the array
>   2. at: returns the data at the given index
>   3. remove: removes the data at the given index or the given piece of data
>   4. size: returns the size of the array
>   5. pop: removes and returns the object at the given location
>   6. operator[]: calls "at()" at the given index
>
> ####User
>   Class for containing information on a User including name, age, zipcode and friends
>
>**Member Data:**
>   1. name_: string of the name of the User
>   2. age_: int of the age of the User
>   3. zip_: int of the zipcode of the User
>   4. friends_: MyList of ints to store friend IDs
>
>**Functions:**
>   1. getName and setName: access and manipulate name field
>   2. getAge and setAge: access and manipulate age field
>   3. getZip and setZip: access and manipulate zip field
>   4. getFriends: access the friends field of the User
> 
> ####GMLWriter
>**Member Data:
>   **None**
>
>**Functions**:
>   1. write: primary method that calls for the conversion and saving of a User save file
>   2. toNode: converts the given User object into text
>   3. toEdge: converts the relationships of the given User to text


## Global Data/Functions
>**Global Data**
>   1. users: the MyList of User pointers
>**Global Functions:**
>   1. readFile: reads in data from the file usign GMLReader and processes it into users
>   2. parseUser: converts a line of text into a User
>   3. parseEdge: converts a line of text into a User relationship
>   4. processTransactions: runs through and processes a list of commands given in a file
>   5. findIndexes: finds the two given Users in the MyList
>   6. addFriend: makes the two users friends
>   7. removeFriend: removes the relationship between the two users

## High-level Architecture
> Everything in this will be governed primarily from the main method. File reading and writing will be called in the main, and the primary set of data, the MyList of User*, will be housed there as well. Other methods to be called from the main will exist for repetitive actions, such as adding and removing User connections.
> 

## User Interface
> User interactions will be severely limited and dealt with solely through command line arguments and file reading. Information on Users will be stored into text files to be read and to be used following execution of the program.
> Other than this and error output, there will not be interaction with the program.
> At the end of the program, a list of the friends each User has will be displayed.


##Test Cases
> + I will test the system by modifying the files given and supplying different arguments to the command line.
> + Problem cases include invalid commands, invalid names, and invalid files. These are each handled in their own way in the program.
> + Test cases will involve a variety of user name layouts and sequencing of parameters. I will experiment with the different parsing functions in order to make sure that they work as expected.