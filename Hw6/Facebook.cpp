/*

  This class file has been partially written for you.
  You must finish implementaiton of all of its methods according to its associated header file

   Please note restriction: you may NOT use the find() function in your methods below
   
*/

#include <iostream>
#include <string>
#include <fstream>

#include "Facebook.h"


  // DONE FOR YOU: LIST PEOPLE
  // Goal: print out a description of the entire "Facebook database" along with useful statistics about pointer use

   void Facebook::listPeople(){
      if ( people.size() == 0 ) {
        std::cout << std::endl << "**** The Facebook database is empty ****" << std::endl;
        return;
      }
     
      std::cout << "\n\nFacebook Database: " << people.size() << " entries: " << std::endl;

      int sum_of_use_count = 0;

      for(auto & person : people){

        person.second->printMe(); // we need to access the second of the Pair construct to get the Perons pointer
        //std::cout << "    and from Facebook: the person shared_ptr use_count = " << person.second.use_count() << std::endl;
        sum_of_use_count += person.second.use_count();
      }

      std::cout << "Total shared_ptr use_count = " << sum_of_use_count << std::endl;
   } // end Facebook::listPeople()


    // TODO: EXISTS PERSON
    // Goal: return true if the person exists in the "people" map (true) or not (false)
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    bool Facebook::existsPerson( std::string personName) {
        return people.count(personName) > 0;
    }

    // TODO: ADD PERSON:
    // Goal: Add a new (non-existent) person as a key-value pair to the people map.
    // If the person already exists in the people map, return false.
    // Use the make_shared< ?? > ( ) templated function to call the Person constructor.  The returned value will be a shared_ptr.
    // Storing the shared pointer to the new Person instance as the "value" portion of a key-value pair in the people map.
    // Use the name of the new person as the "key" of the key-value pair that you store.
    // Return true if successful
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    bool Facebook::addPerson( std::string personName) {
        if (existsPerson(personName)) {
            return false;
        }
        people[personName] = std::make_shared<Person>(personName);
        return true;
    }

    // TODO: PRINT PERSON DESCRIPTION
    // Goal: Print a short descrption of an existing person from the "people" map, including their list of friends.
    // If the person does not exist in the people map, return false.
    // Note that the Person class already supports a printMe() method!
    // Return true if successful
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    bool Facebook::printPerson( std::string personName) {
        if (existsPerson(personName)) {
            std::shared_ptr person = people[personName];
            person -> printMe();
            return true;
        }
        return false;
    }


    // TODO: DELETE PERSON
    // Goal: Delete an existing person's key-value pair from the people map of the Facebook class.
    // Find a key-value pair for specified person by using the people map of key-value pairs in the Facebook class
    // Erase the entire key-value pair from the people map
    // Note that by erasing the key-value pair, including the shared_ptr from the people map, 
    // ... the Person instance managed by the shared_ptr will automatically destruct (we should see the Person destructor called)
    //  ... also, all weak references to the Person instance by friends will become invalid 
    //  ... that is, their use_count will become zero, thus helping us avoid a crash if we try to access a deleted friend
    // Return false the person does not exist in the people map, else return true
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    bool Facebook::deletePerson( std::string personName) {
        if (existsPerson(personName)) {
            const std::shared_ptr person = people[personName];
            for (const auto& pair: person -> friends) {
                const auto& other = pair.second.lock();
                // if (other) {
                    // other -> friendedByCount -= 1;
                    // other -> friends.erase(person -> id);
                // }
            }
            people.erase(personName);
            return true;
        }
        return false; // replace with your code
    }


    // TODO: ADD FRIEND
    // Goal: Add a friend id (not name) and "friend weak pointer" to an existing person's friend map as a key-value pair
    // Note that friending is one-directional.  So that if person "personName" adds person "friendName" as a friend, 
    // .... then, person "personName" is NOT added to person "friendName"'s friend map.
    // Find a shared_ptr to the specified person and to the specified friend by using the people map of shared_ptr's found in the Facebook class
    // Add the "friendName" Person's id and a weak_ptr to the friend map of the "personName" as a key-value pair
    // Note that by assigning a shared_ptr from "people" to the friend map's value (a weak_ptr type), it will be automatically converted into a weak_ptr
    // Finally, increment the count of times the "friendName"  instance has been declared a friend by someone else using its Person "friendedByCount"
    // Return false if either the person or friend does not exist in the people map
    // Return false if the requested friendship already exists (that is, if the friendName is alraedy present in the friend map of the personName)
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    bool Facebook::addFriend( std::string personName, std::string friendName) {
        if (existsPerson(personName) && existsPerson(friendName)) {
            std::shared_ptr person = people[personName];
            std::shared_ptr person_f = people[friendName];
            if (person -> friends.count(person_f -> id) > 0) {
                return false;
            }
            person -> friends[person_f -> id] = person_f;
            person_f -> friendedByCount += 1;
            return true;
        }
        return false;
    } // end addFriend()


    // TODO: GET PERSON FRIENDS
    // Restrictions: you may not use .find() in your solution (-2 pts penalty)
    std::vector<std::string> Facebook::getPersonFriends( std::string personName ) {
        std::vector<std::string> friend_list;
        if (existsPerson(personName)) {
            std::shared_ptr person = people[personName];
            const auto& friend_map = person -> friends;
            for (const auto& pair: friend_map) {
                std::shared_ptr temp = pair.second.lock();
                if (temp) {
                    friend_list.push_back(temp -> name);
                }
            }
        }
        return friend_list;
    }


    // TODO: TOTAL FRIENDS
    // Goal Return the integer number of total friends in all Person instances referenced by the people map
    // NOTE: be sure to use a reference to avoid unwanted copies while you are inspecting the people map
    // NOTE2: total friends is the sum of all "friends" map sizes for all people (not the sum of the friendedByCount)
    int Facebook::totalFriends( ) {
        int sum = 0;
        for (const auto& person_pair: people) {
            sum += person_pair.second -> friends.size();
        }
        return sum;
    } // end addFriend()


    // TODO: UPDATE NAME
    // Goal: Update a person's name to a new unique name without corrupting existing friendships
    // Return false if the old name does NOT exist in the people map of the Facebook class
    // Return false if the new name DOES exist in the people map of the Facebook class (if it is already in use)
    // Note that you will be updating the key of an existing key-value pair, 
    //  ... so you must preserve the shared_ptr for the Person instance (otherwise all friend references will be lost)
    bool Facebook::updatePerson( std::string personName, std::string updateName) {
        if (existsPerson(personName) && !existsPerson(updateName)) {
            std::shared_ptr person = people[personName];
            person -> name = updateName;
            people[updateName] = person;
            people.erase(personName);
            return true;
        }
        return false;
    } // end addFriend()


    // TODO: CLEAR PEOPLE
    // Goal: Clear the people map of the Facebook class, triggering automatic destruction of all People instances
    bool Facebook::clearPeople( ) {
        people.clear();
        return true;
    } // end clearPeople()


    // TODO: DESTRUCTOR:
    // Goal: delete all People instances in the Facebook in as few lines of code as necessary.
    // Confirm that People instances are being deleted by watching the console for People destructor messages when executing the "(r) reset" command in main()
     Facebook::~Facebook(){
        clearPeople();
    }

