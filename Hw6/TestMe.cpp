#include <iostream>
#include <string>
#include <fstream>
#include "Facebook.h"

    // OPEN FILE
    // print out a description of the entire "Facebook database" along with useful statistics about pointer use
     bool Facebook::testMe( std::string fileName ){

       const char * red = "\033[1;31m";
       const char * green = "\033[1;32m";
       const char * done = "\033[0m";
       const char * cyan = "\033[96m";
     // open the file and build a network of Person classes and initiliaze the Map
        std::fstream inFile; // file we want to read
        std::string personName;
        int friendCount =0;
        std::string friendName;

       srand( 1234); // initialize random number generator for repeatable results
      clearPeople(); // make sure the database is cleared.
       
      if ( fileName.size() == 0) return false; // nothing to do

        // first pass

        inFile.open(fileName);

        while(inFile >> personName){ // read the name of a person
          std::cout << "Creating person " << personName << " from " << fileName << std::endl;
          addPerson( personName );// push a shared_ptr to a Person into the vector of people
          inFile >> friendCount; // how many friends does this person have?
          for(int i=0; i<friendCount; i++){
            inFile >> friendName; 
          }
        }
        inFile.close();

        // at this point, we know that all persons in the file have been created, though their friends have not
        // so we'll read the file again to create associations with the friends

        // second pass

        inFile.open(fileName);

        while(inFile >> personName){ // read the name of a person
          inFile >> friendCount; // how many friends does this person have?
          for(int i=0; i<friendCount; i++){
              inFile >> friendName; 
              std::cout << "Adding friend " << friendName << " to " << personName << std::endl;
              addFriend( personName, friendName) ; 
          }
        } // while

        inFile.close();


      if (existsPerson("lillian") && people["lillian"]->friendedByCount != 5 ) { std::cout <<  "lillian friendedByCount is incorrect: " << people["lillian"]->friendedByCount << done << std::endl; return false; }
      if (existsPerson("nellie") && people["nellie"]->friendedByCount != 4 ) { std::cout <<  "nellie friendedByCount is incorrect " << people["nellie"]->friendedByCount<< done << std::endl;return false; }
      if (existsPerson("chantelle") && people["chantelle"]->friendedByCount != 2 ) { std::cout <<  "chantelle friendedByCount is incorrect" << people["chantelle"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("tia") && people["tia"]->friendedByCount != 4 ) { std::cout <<  "tia friendedByCount is incorrect" << people["tia"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("ali") && people["ali"]->friendedByCount != 3 ) { std::cout <<  "ali friendedByCount is incorrect" << people["ali"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("gene") && people["gene"]->friendedByCount != 4 ) { std::cout <<  "gene friendedByCount is incorrect" << people["gene"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("jacob") && people["jacob"]->friendedByCount != 4 ) { std::cout <<  "Jacob friendedByCount is incorrect" << people["jacob"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("rafael") && people["rafael"]->friendedByCount != 2 ) { std::cout <<  "rafael friendedByCount is incorrect" << people["rafael"]->friendedByCount<< done << std::endl; return false;}
      if (existsPerson("abdullah") && people["abdullah"]->friendedByCount != 4 ) { std::cout <<  "abdullah friendedByCount is incorrect"  << people["abdullah"]->friendedByCount<< std::endl; return false;}
      if (existsPerson("keaton") && people["keaton"]->friendedByCount != 5 ) { std::cout <<  "keaton friendedByCount is incorrect" << people["keaton"]->friendedByCount<< done << std::endl; return false;}

      if (! existsPerson("lillian") ) { std::cout << red << "lillian should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("nellie") ) { std::cout << red << "nellie should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("chantelle") ) { std::cout << red << "chantelle should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("tia") ) { std::cout << red << "tia should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("ali") ) { std::cout << red << "ali should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("gene") ) { std::cout << red << "gene should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("jacob") ) { std::cout << red << "jacob should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("rafael") ) { std::cout << red << "rafael should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("abdullah") ) { std::cout << red << "abdullah should exist, but does not" << done << std::endl; return false; }
      if (! existsPerson("keaton") ) { std::cout << red << "keaton should exist, but does not" << done << std::endl; return false; }
       

      std::cout << "Would you like to attempt AAA  comprehensive testing now (y for yes)? ";
      std::string response;
      std::cin >> response;

      if ( response[0] == 'y') {
        bool ok = true; // flag for each test
        int totalBadTests = 0;
        int totalTests = 0;
        std::cout << "testing.... " << std::endl;
        std::cout << "Test #1: adding up to 10,000 random people with names '0' through '999'" << std::endl; totalTests++;
        
        for(int i=0; i< 10000; i++) { // add up to 10000 random people with names "0" to "999"
          std::string personName = std::to_string( rand()%1000 );
          addPerson( personName ); // will fail for some invalid requests
          if ( !existsPerson( personName ) ){
            ok = false;
            std::cout << red << "testMe(): existsPerson() failed to report true after adding person " << personName << ".  Please check your solution." << done << std::endl;
            { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
          }
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test
        
        std::cout << "Test #2: deleting up to 10,000 random people with names '0' through '999'" << std::endl;totalTests++;
        for(int i=0; i< 1000; i++) { // delete up to 1000 random people with names "0" to "999"
          std::string personName = std::to_string( rand()%1000 );
          deletePerson( personName ); // will fail for some invalid requests
          if ( existsPerson( personName ) ){
            ok = false;
            std::cout << red << "testMe(): existsPerson() failed to report false after deleting person " << personName << ".  Please check your solution." << done << std::endl;
            { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
          }
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test

        std::cout << "Test #3: adding up to 10,000 friend relationships two random between people with names '0' through '999'" << std::endl;totalTests++;
        for(int i=0; i< 10000; i++) { // add up to 10000 random friend relationshiops with names "0" to "999"
          std::string personName = std::to_string( rand()%1000 );
          std::string friendName = std::to_string( rand()%1000 );
          if (personName == friendName) continue;
          int personFriendsBefore = 0;
          int friendFriendsBefore = 0;
          int totalFriendsBefore = 0;
          if ( existsPerson( personName ) && existsPerson( friendName ) ) {  // if these random people both exist
            totalFriendsBefore = totalFriends( ); // record total number of friends in the system before we add a new valid friend
            personFriendsBefore = people[personName]->friends.size();
            friendFriendsBefore = people[friendName]->friends.size();
          }
          bool result = addFriend( personName, friendName ); // will fail for some invalid requests
          if ( result == true ) {
            if (  !existsPerson( personName ) || !existsPerson( friendName ) ){ // should not report true if either person did not exist
              ok = false;
              std::cout << red << "testMe(): addFriend() returned true when either the person or friend specifed did not exist.  Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if ( totalFriendsBefore != totalFriends()-1  ) { // there should be 1 more friend now
              ok = false;
              std::cout << red << "testMe(): valid addFriend() did not result in increase of total friends according to totalFriends() method.  Total Friends before was " << totalFriendsBefore << " while total friends after was " << totalFriends() << " .Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if ( personFriendsBefore != people[personName]->friends.size()-1  ) { // there should be 1 more friend now for this person
              ok = false;
              std::cout << red << "testMe(): valid addFriend() did not result in increase of total friends for " << personName << "(person) according to their friends map size.    friends.size() before was " << personFriendsBefore << " while friends.size() after was " << people[personName]->friends.size() << " .Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if ( friendFriendsBefore != people[friendName]->friends.size() ) { // there should be NO CHANGE to count of friends friends
              ok = false;
              std::cout << red << "testMe(): valid addFriend() incorrectly increased of total friends for " << friendName << "(friend) according to their friends map size.    friends.size() before was " << friendFriendsBefore << " while friends.size() after was " << people[friendName]->friends.size() << " .Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
          } // end result == true
        } // done adding friends  
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test

        std::cout << "Test #4: deleting up to 1000 random people with names '0' through '999'" << std::endl;totalTests++;
        for(int i=0; i< 1000; i++) { // delete up to 1000 random people with names "0" to "999"
          std::string personName = std::to_string( rand()%1000 );
          deletePerson( personName ); // will fail for some invalid requests
          if ( existsPerson( personName ) ){
            ok = false;
            std::cout << red << "testMe(): existsPerson() failed to report false after deleting person " << personName << ".  Please check your solution." << done << std::endl;
            { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
          }
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test
        
        std::cout << "Test #5: updating up to 1000 random people with names '0' through '999'" << std::endl;totalTests++;
        for(int i=0; i< 1000; i++) { // update up to 1000 random people with names "0" to "999"
          std::string personName = std::to_string( rand()%1000 );
          if ( existsPerson( personName )) { // if we picked a real person
            std::string updateName = ("-"+personName);// update the person by prefixing a negative sign to their name
            updatePerson( personName, updateName ); 
            if ( existsPerson( personName ) ){ // this person should no longer exist
              ok = false;
              std::cout << red << "testMe(): existsPerson() failed to report false after updating personName " << personName << " to updateName" << updateName << ".  Perhaps you forgot to erase the original key:value pair for personName? Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if ( !existsPerson( updateName ) ){ // this person should exist
              ok = false;
              std::cout << red << "testMe(): existsPerson() failed to report true for " << updateName << " after updating person " << personName << " to " << updateName << ".  Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if ( people.count(updateName) != 1 ) {
              ok = false;
              std::cout << red << "testMe(): people.count() for " << updateName << " failed to return a value of 1 after updating person " << personName << " to " << updateName << ".  Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            deletePerson( "TEST_PERSON"); // delete in case they already existed
            addPerson( "TEST_PERSON"); // add a new person called "TEST_PERSON" that we can use to "friend" the updated person
            bool result = addFriend( "TEST_PERSON", updateName ); // added updateName as a friend
            std::vector<std::string> friendNames = getPersonFriends( "TEST_PERSON"); // get a vector of strings of friend names (not ids)
            if (friendNames.size() != 1 ) {
              ok = false;
              std::cout << red << "testMe(): Adding a new TEST_PERSON and adding " << updateName << " as their friend does not appear to have resulted in a friends map of size 1 for TEST_PERSON. getPersonFriends( 'TEST_PERSON' ) returned " << friendNames.size() << " This may mean that addFriend TEST_PERSON " << updateName << " failed to find the updated friend name " << updateName << " Please check your solution." << done << std::endl;
              for (auto name : friendNames ) std::cout << name << ','; std::cout << std::endl;
              for (auto name : friendNames ) printPerson( name );
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
            if (friendNames.size() != 1 && friendNames[0] != updateName ) { // the actual Person::name field was never updated to the new update name, only the key.
              ok = false;
              std::cout << red << "testMe(): The updated name " << updateName << " does not appear to have been updated in the actual Person instance, which is still " << friendNames[0] << "  Perhaps you only updated the key for the people map to " << updateName << ". Please check your solution." << done << std::endl;
              { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
            }
          }
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test

        std::cout << "Test #6: checking total number of people left in database..." << std::endl;totalTests++;
        std::cout << "      people left in database: " << people.size() << std::endl;
        if ( people.size() != 147 ) { // includes TEST_PERSON created above
          ok = false;
          std::cout << red << "testMe(): total number of people left in database should be 147.  Please check your solution." << done << std::endl;
          std::cout <<  red << "Would you like to print out all people left? (y/n)";
          {std::string s; std::cin >> s; if (s.size()>0 && s[0]=='y') listPeople();} // print out a list of all people left in database
          std::cout << done << std::endl;
          { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++; ok = true; // reset for the next test

        std::cout << "Test #7: Calling totalFriends() to add up all friend map sizes for people left in database..." << std::endl;totalTests++;
        std::cout << "      sum of all friends map sizes: " << totalFriends() << std::endl;
        if ( totalFriends() != 503 ) {
          ok = false;
          std::cout << red << "testMe(): sum of all friends map sizes should be 503.  Please check your solution." << done << std::endl;
          { char x; std::cout << "Enter any character (and then return) to continue testing: ";}  // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++;  ok = true; // reset for the next test


        std::cout << "Test #8: adding up all 'Person::friendedByCount values for people left in database (may be > than totalFriends() due to deleted people who WERE friended before being deleted)..." << std::endl;totalTests++;
        int totalFriendings = 0;
        for( auto thisPerson: people ){
          totalFriendings += thisPerson.second->friendedByCount;
        }
         std::cout << "      sum of all remaining 'friendedByCount' values: " << totalFriendings << std::endl;
        
        if ( totalFriendings != 632 ) {
          ok = false;
          std::cout << red << "testMe(): sum of all remaining 'friendedByCount' values should be 632.  Please check your solution." << done << std::endl;
          std::cout <<  red << "Would you like to print out all people left? (y/n)";
          {std::string s; std::cin >> s; if (s.size()>0 && s[0]=='y') listPeople();} // print out a list of all people left in database
          { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++; ok = true; // reset for the next test

        std::cout << "Test #9: adding up all deleted friends (expired weak pointers) in friend maps for people left in database..." << std::endl;totalTests++;
        int totalDeletedFriends = 0;
        for( auto & thisPair: people ){
          for(auto q =  thisPair.second->friends.begin(); q!= thisPair.second->friends.end(); q++ ){
              //std::shared_ptr<Person> sp = q->second.lock(); // attempt to get a "lock' on the weak pointer so we can inspect it; 
              if ( q->second.expired() ) {// if (! sp ) {  // if the pointer exists
                totalDeletedFriends ++;
              }
  
            } // done search through all friends
          } // done searching people
          std::cout << "      sum of all deleted friend references: " << totalDeletedFriends << std::endl;
        
        if ( totalDeletedFriends != 281 ) {
          ok = false;
          std::cout << red << "testMe(): sum of all remaining deleted friend map weak_ptr references should be 281.  Please check your solution." << done << std::endl;
          { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++; ok = true; // reset for the next test


        std::cout << "Test #10: adding up all EXISTING friends using getPersonFriends() (should NOT include expired weak pointers for deleted friends) for people left in database..." << std::endl;totalTests++;
        int totalExistingFriendNames = 0;
        for(auto &thisPerson : people) { // get friend lists of everyone who exists
          std::vector<std::string> tmpVec = getPersonFriends( thisPerson.second->name ); // will fail for some invalid requests
          totalExistingFriendNames+=tmpVec.size(); // add up the number of names we got back, not including any names of deleted People
        }  
        
        std::cout << "      total of all existing friends from getPersonFrinds() (excludes weak pointers with use_count()==0 ): " << totalExistingFriendNames << std::endl;
        if ( totalExistingFriendNames != 222 )  {
          ok = false;
          std::cout << red << "testMe():total of all existing friends from getPersonFrinds() should be 222.  Please check your solution." << done << std::endl;
          { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++; ok = true; // reset for the next test

        std::cout << "Test #11:  totalFriends() (DOES include expired weak pointers for deleted friends) for people left in database..." << std::endl;totalTests++;
        std::cout << "      totalFriends()  =  " << totalFriends() << std::endl;
        if ( totalFriends() != 503 ) {
          ok = false;
          std::cout << red << "testMe():total of all existing friends from getPersonFrinds() should be 503.  Please check your solution." << done << std::endl;
          { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
        }
        if (ok) std::cout << green << "   OK!" << done << std::endl;
        else totalBadTests++; ok = true; // reset for the next test
        

        std::cout << "Test #12:  clearPeople() should reduce static population count for Person class to zero via ~Person() destructor..." << std::endl;totalTests++;
        clearPeople(); // make sure the database is cleared.

        if ( Person::population != 0 ) { // UPDATE something must be wrong since clearly the map should have trigger destruction of all Person instances
          std::cout << "    Person::population = " << Person::population << std::endl;
          ok = false;
          std::cout << red << "testMe(): Ooops... somehow all People instances did not get destructed when we cleared the people map... please check your solution!" << done << std::endl;
           { char x; std::cout << "Enter any character (and then return) to continue testing: "; std::cin >> x; } // exit(1); 
          }
        if (ok) std::cout << green << "   OK!" << done << std::endl; 
        else totalBadTests++; ok = true; // reset for the next test


        std::cout << cyan << "Total Tests Performed: " << totalTests << done << std::endl;
        std::cout<< red << " Total Failed Tests: " << totalBadTests << done << std::endl;
        { std::cout << "Done testing... enter any character (and then return) to reset and continue? "; char x; std::cin >> x; }

        if ( totalBadTests == 0)
          return true; 
        else
          return false;
        
       } // end comprehensive testing


      return true;
       
     } // end Facebook::testMe()