/*

 DONE : This header file has been fully written for you.

*/

#ifndef FACEBOOK_H
#define FACEBOOK_H
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "Person.h"

class Facebook{
    std::map<std::string, std::shared_ptr<Person> > people; // a std:map of people, with key name and value a shared_ptr

  public:


    void listPeople(); // DONE FOR YOU:  print statistics method for entire Facebook instance
    bool testMe( std::string fileName = ""); // DONE FOR YOU : reads data from a specified fileName and AUGMENTS the current Facebook database.

    // default constructor does not need to be written

    // the following bool methods should return true if successful, else false
    bool existsPerson( std::string personName ); // TODO: return true if this person exists in the current people map, else false
    bool printPerson( std::string personName ); // TODO: print a short description of this person, return true if this person exists, else false
    bool addPerson( std::string personName); // TODO: add the existing person as a key-value pair the people map. Return true if successful
    bool deletePerson( std::string personName ); // TODO: delete the existing named person's key-value pair from the people map.
    bool updatePerson( std::string personName, std::string updateName ); // TODO: update existing person's name (key), preserving its existing shared_ptr (value).
    bool addFriend( std::string personName, std::string friendName ); // TODO: add this existing friend to the this existing person's friend map as a key-value pair.
    int totalFriends( ); // TODO: return the integer total number of existing friends (by adding up the size of all friend maps)
    std::vector<std::string> getPersonFriends( std::string personName ); // TODO: return a vector of strings of the names of an existing person
    bool clearPeople() ; // TODO: clear the entire people map, triggering automatic destruction of all Person instances already added.

     ~Facebook(); // TODO: destructor for the the class.  Erase the contents of the people map and ensure (through visual inspection of console output) that all Person instances are automatically destructed.
};

#endif