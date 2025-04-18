/*

  DONE : this header file has been fully written for you

*/

#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <memory>
#include <map>

class Person{

  public:
    static int population; // UPDATED: stored in the class to count total population of peoople; note that our destructor decrements on destructions
    std::string name = ""; // name of this person
    int id = -1; // a random "probably unique" integer id for this person
    int friendedByCount; // number People who have declared this person a friend
    std::map<int, std::weak_ptr<Person> > friends; // a std:map of friends, with Person id as the key and shared_ptr to the Person instances as its value
    

    Person(std::string _name); // our constructor
    ~Person(); // our destructor

    void printMe(); // diagnostic print out describing this person
};

#endif