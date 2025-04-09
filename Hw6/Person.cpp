/*

 DONE : This class file has been fully implemented for you.

*/

#include <iostream>
#include <string>
#include <map>
#include "Person.h"

int Person::population = 0; // UPDATED: must perform static initialization of .h member out of class initialization in cpp file

Person::Person(std::string _name) : name(_name), friendedByCount(0), id( rand()%1000000) {  // UPDATED S24 - increased from 10000 to 1000000
  // nothing to do
}  // end constructor

Person::~Person() { 
  std::cout << " ~Person(): destroying Person " << name << std::endl;
} // end destructor

void Person::printMe(){
  std::cout << "\n" << name << "(id=" << id << ") has a friends map with " << friends.size() << " friends: ";
    for(auto & thisFriend : friends ){
      std::shared_ptr<Person> sp = thisFriend.second.lock(); // attempt to get a "lock' on the weak pointer so we can inspect it; 
      if (sp ) {  // if the pointer exists
        std::cout << sp->name << ", ";
      }
      else {
          std::cout << "(id#" << thisFriend.first << " was deleted), "; // print tne name of the friend from the key, indicating it has been deleted
      }

    } // done search through all friends
    std::cout << std::endl;

    std::cout << "    and has been friended " << friendedByCount << " times by other people" << std::endl;
} // end printMe()