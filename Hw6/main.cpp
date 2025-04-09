/*

 DONE : This main.cpp file has been fully implemented for you.

*/

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Facebook.h"


using namespace std;

// DONE: this function has been full implemented for you
string printInstructions() {

  cout << "Welcome to Facebook... I mean 'Meta'...." << endl;

  cout << "\nYou may: \n";
  cout << "   (e) check to see if a named Person exists.\n";
  cout << "   (a) add a new Person. \n";
  cout << "   (p) print description of a Person. \n";
  cout << "   (l) list all people in the Facebook database.\n";
  cout << "   (u) update an (existing) person's old name to a new name.\n";
  cout << "   (d) delete an existing Person.\n";
  cout << "   (f) add an (existing) named Friend to existing named Person's "
          "friends map.\n";
  cout << "   (v) print a list of friends for a specific existing person.\n";
  cout << "   (#) print the total number of friends declared in the Facebook "
          "dabase.\n";
  cout << "   (c) clear all people from the Facebook database.\n";
  cout << "   (t) test all Facebook methods in various ways.\n";
  cout << "   (h) help, print these instructions.\n";

  return "\nPlease enter a command (e, a, p, l, u, d, f, v, #, c, t, h): "; // used in the main() loop
}

int main() {

  string commandPrompt = printInstructions(); // see function above main()

  // create the Facebook class.... referenced by a unique_ptr
  unique_ptr<Facebook> fPtr = make_unique<Facebook>(); // a unique pointer to a dynamically allocated
                               // instance of the Facebook class

  while (true) { // take input from the user that alters the Facebook database

    string userResponse;  // user input (we are only interested in the 1st letter)
    string personName; // name of a person we want to add to the database
    string updateName; // new name for an existing person we want to update (to
                       // replace their old name)
    string friendName; // name of a friend we want to add to an existing person
    string parentName; // name of a parent we want to add to and existing person
    vector<string> friendVector;
    cout << commandPrompt; // print the instructions string we got back from the
                           // printInstructions() function call
    cin >> userResponse;

    switch (userResponse[0]) { // check the first characer of the user response

    case 'e': // DOES PERSON EXIST?
      cout << "Please enter the name of the person you would like to search for: ";
      cin >> personName;
      if (fPtr->existsPerson(personName)) {
        cout << "Success: " << personName << " does exist " << endl;
      } 
      else {
        cout << "    **** I am sorry, " << personName << " could not be found."
             << endl
             << endl;
      }
      break;

    case 'a': // ADD PERSON
      cout << "Please enter the name of the person you would like to ADD: ";
      cin >> personName;
      if (fPtr->addPerson(personName)) {
        cout << "Success: " << personName << " has been added " << endl;
      } 
      else {
        cout << "    **** I am sorry, " << personName
             << " could not be added.. perhaps they are already in the "
                "Facebook database?"
             << endl
             << endl;
      }
      break;

    case 'p': // PRINT PERSON DESCRIPTION
      cout << "Please enter the name of the EXISTING Person to print:: ";
      cin >> personName;
      if (!fPtr->printPerson(personName)) {
        cout << "    **** I am sorry " << parentName
             << " does not exist in the Facebook database" << endl;
      }
      break;

    case 'l':             // LIST PEOPLE
      fPtr->listPeople(); // list all people in the Facebook dabase (that is, in
                          // its people map)
      break;

    case 'u': // UPDATE a Person's name
      cout << "Please enter the CURRENT name of the EXISTING Person:: ";
      cin >> personName;
      cout << "Please enter a NEW (unused) name for the EXISTING person "
           << personName << ": ";
      cin >> updateName;
      if (fPtr->updatePerson(personName, updateName)) {
        cout << "Success: " << personName << " has been changed to "
             << updateName << endl;
      } 
      else {
        cout << "    **** I am sorry,  " << personName
             << " does not exist in the Facebook database. Update Aborted."
             << endl
             << endl;
      }
      break;

    case 'd': // DELETE PERSON
      cout << "Please enter the name of the person you would like to DELETE: ";
      cin >> personName;
      if (fPtr->deletePerson(personName)) {
        cout << "Success: " << personName << " has been deleted " << endl;
      } else {
        cout << "    **** I am sorry, " << personName
             << " could not be deleted.. perhaps they are not currently in the "
                "Facebook database?"
             << endl
             << endl;
      }
      break;

    case 'f': // ADD FRIEND
      cout << "Please enter the name of the existing person who is adding a "
              "new friend "
           << friendName << ": ";
      cin >> personName;
      cout << "Please enter the name of the existing person that represents "
              "the new friend: ";
      cin >> friendName;
      if (fPtr->addFriend(personName, friendName)) {
        cout << "Success: " << friendName
             << " has been added to the friendList of " << personName << endl;
      } 
      else {
        cout << "    **** I am sorry, either " << friendName << " or "
             << personName
             << " does not exist in the Facebook database. Add Friend aborted."
             << endl
             << endl;
      }
      break;

    case 'v': // List VIRAL FRIENDS OF A PERSON
      cout << "Please enter the name of the existing person who's friends we "
              "want to see "
           << personName << ": ";
      cin >> personName;
      friendVector = fPtr->getPersonFriends(personName);
      if (friendVector.size() > 0) {
        cout << "Friends of " << personName << " are ";
        for (auto &thisName : friendVector)
          cout << thisName << ", ";
        cout << endl;
      } 
      else
        cout << "    *** I am sorry, " << personName << " has no friends"
             << endl;
      break;

    case '#': // COUNT FRIENDS
      cout << "The current total number of friends is " << fPtr->totalFriends()  << ": ";
      break;

    case 'c':              // CLEAR PEOPLE
      fPtr->clearPeople(); // clear people from the Facebook people map,
                           // automatically triggering  People destructors
      cout << "The Facebook database has been cleared" << endl << endl;
      break;

    case 't': // test
      if (fPtr->testMe(
              "testPeople.txt")) // this will correctly destruct the old
                                 // Facebook instance, before creating a new one
        cout << "Congratulations - you passted all tests.  Well-done!" << endl
             << endl;
      else
        cout << "Hmmm... seems there were one or more problems... please see output (above) and the testPeople.txt file!"  << endl;
      break;

    case 'h': // HELP
      printInstructions();
      break;

    default:
      cout << "Please try again, or type h for help" << endl;
      continue;
      
    } // end switch
    
  } // end while
  
  cout << "Done!\n" << flush; // be sure to flush
  
}// end main()