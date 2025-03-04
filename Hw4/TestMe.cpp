/*

  When ready, rename this file to remove its ".rename" extension
  Then rerun  your code to see test results

  The TestMe class in this file will be instantiated, and its constructor will test test your code.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>
#include <algorithm>

#include "BlackJack.h"


class TestMe {
  public:

  TestMe(){  
  
    std::cout << "TestMe Constructor(): Starting tests..." << std::endl;
  
    //const char * inputFileName = "TestMeIn.txt";
    const char * outputFileName = "TestMeOut.txt";
    std::ofstream outputFile;
    outputFile.open(outputFileName); // open it to reinitialize it
    outputFile.close(); // close the file
  
  
      // Simulate the file contents as a string
      std::string simulatedFileContents = "h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s h h h s";
      std::istringstream inFile(simulatedFileContents); //      // fakefile: Create an istringstream object with the string
      
      //std::ifstream inFile(inputFileName);                    // oldway: realfile: redirect i/o
      std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
      std::cin.rdbuf(inFile.rdbuf());            // redirect std::cin to in.txt!
  
    std::ofstream out( outputFileName );
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
  
    float yourScore = 0;
    float bonusScore = 0;
    bool testResults[ 100 ]; // results of our tests - max 100 of them
    bool bonusTestResults[ 100 ]; // result of bonus tests - max 100 of them
  
    for (int i=0; i<100; i++){
      testResults[i] = false; // init all test results to false
      bonusTestResults[i] = false; // init all test results to false
    }
  
    int testNum = -1; // start negative: zero will be our first test
    int bonusTestNum = -1; // 
    std::string testName = "";
  
      { //  0: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test A: Dealer Should win with larger hand (20)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins
        srand(10);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        // for(int i=0; i<52; i++) 
        //   cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        // random_shuffle(cardIDs.begin(), cardIDs.end());
        // BlackJack game({"Player", "Dealer"}, cardIDs);
        BlackJack game({"Player", "Dealer"},  { 4, 5, 6, 20, 21, 30, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 1){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      { //  1: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test B : Player should win with larger hand (19)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins
        srand(999);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        // for(int i=0; i<52; i++) 
        //   cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        // random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"},  { 48, 35, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      { //  2: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test C:  Player Should win with 21";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Player wins
        srand(1345);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        //random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"}, { 48, 48, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
      { //  3: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test D:  Player Should win with 20";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Player wins
        srand(4568);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        //random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"}, {28, 29, 13, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      { //  4: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test E: Dealer Should Win (Player Busts)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins
        srand(34657678);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"}, cardIDs);
        game.play();
        if (game.getWinningPlayerId() == 1){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
      { //  5: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test F: Player Wins (Dealer Busts)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Player wins
        srand(4567);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"}, cardIDs);
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      { //  6: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test G: Player Wins (Dealer Busts)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Player wins
        srand(4567);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        random_shuffle(cardIDs.begin(), cardIDs.end());
        BlackJack game({"Player", "Dealer"}, cardIDs);
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
       {//  7: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test H: Player Win's with 21";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins tie
        srand(4567);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        for(int i=0; i<52; i++) 
          cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        random_shuffle(cardIDs.begin(), cardIDs.end());
       // BlackJack game({"Player", "Dealer"}, cardIDs);
        BlackJack game({"Player", "Dealer"}, {44, 48, 2, 47, 49, 3,  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      {//  8: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test I: Test Player Points - should be 14";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins tie
        srand(444);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        // for(int i=0; i<52; i++) 
        //   cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        // random_shuffle(cardIDs.begin(), cardIDs.end());
        // BlackJack game({"Player", "Dealer"}, cardIDs);
        BlackJack game({"Player", "Dealer"}, {16, 17, 14, 47, 49, 3,  5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17 });
        game.play();
        if (game.getPlayerPoints() == 14){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
      {//  9: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test J: Test Dealer Points - should be 17 (dealer stands on > 16)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins tie
        srand(444);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        // for(int i=0; i<52; i++) 
        //   cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        // random_shuffle(cardIDs.begin(), cardIDs.end());
        // BlackJack game({"Player", "Dealer"}, cardIDs);
        BlackJack game({"Player", "Dealer"}, {16, 17, 14, 20, 21, 19,  5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17 });
        game.play();
        if (game.getDealerPoints() == 17){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
    {//  10:  
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        testNum++; // increment to the next test
        testName = "Test K (WIP): Dealer wins on tie with player at 21 (dealer stands on > 16)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
  
        // Dealer wins tie
        srand(444);
        std::vector<int> cardIDs; // we'll fill this up with card ids zero to 51
        // for(int i=0; i<52; i++) 
        //   cardIDs.push_back(i);  // here we are pushing integers which represent card IDS
        // random_shuffle(cardIDs.begin(), cardIDs.end());
        // BlackJack game({"Player", "Dealer"}, cardIDs);
        BlackJack game({"Player", "Dealer"}, {24, 25, 26, 23, 27, 31,  5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17 });
        game.play();
        if (game.getDealerPoints() == 21){
          std::cout << "Passed test #" << testNum << std::endl;
          testResults[testNum] = true;
        }
        else {
          std::cout << "Failed test #" << testNum << std::endl;
          testResults[testNum] = false;
        }
      }
  
  
      { // Bonus 0: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        bonusTestNum++; // increment to the next test
        testName = ": Testing Hand::hasAnAce() Hand DOES / DOES NOT have an Ace: stand-alone:";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
  
        srand(10);
        Hand hasAce( {48, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 }); // has an ace
        Hand hasNoAce( {48, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 }); // has an ace
  
        if (hasAce.hasAnAce() == true && hasNoAce.hasAnAce() == false ){
          std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = true;
          bonusScore += 10;
        }
        else {
          std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
          if ( hasAce.hasAnAce() != true ) {
            std::cout << "hasAnAce() incorrectly returned FALSE for a Hand that has Aces" << std::endl;
            hasAce.printMe();
          }
          if ( hasNoAce.hasAnAce() != false ) {
            std::cout << "hasAnAce() incorrectly returned TRUE for a Hand that has NO Aces" << std::endl;
            hasNoAce.printMe();
          }
          bonusTestResults[bonusTestNum] = false;
        }
      }
  
      { // Bonus 1: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        bonusTestNum++; // increment to the next test
        testName = ": Player wins with True Black Jack: Ace of Diamonds (11) and a King of Spades (10)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
  
        srand(10);
        BlackJack game({"Player", "Dealer"}, {48, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = true;
          bonusScore += 10;
        }
        else {
          std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = false;
        }
      }
  
      { // Bonus 2: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        bonusTestNum++; // increment to the next test
        testName = ": Player Wins with Two Aces and Nine: Ace of Hearts (11) and Ace of Diamonds (1) and a Nine of Clubs (9)";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
  
        srand(10);
        BlackJack game({"Player", "Dealer"}, {2, 1, 35, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = true;
          bonusScore += 10;
        }
        else {
          std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = false;
        }
      }
  
    { // Bonus 3: 
        inFile.clear();                 // reset input stream
        inFile.seekg(0, std::ios::beg); 
        bonusTestNum++; // increment to the next test
        testName = ": Player Wins with and Eight, a Two, and Ace";
        std::cout << std::endl << "***********************" << std::endl;
        std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
  
        srand(10);
        Hand t( {28, 4, 0, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 } );
        t.printMe();
        BlackJack game({"Player", "Dealer"}, {28, 4, 0, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 });
        game.play();
        if (game.getWinningPlayerId() == 0){
          std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = true;
          bonusScore += 10;
        }
        else {
          std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
          bonusTestResults[bonusTestNum] = false;
        }
      }
    
  
    // reset i/o
  
    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again
  
    // test numbers go from zero to testNum (inclusive)
  
    //this_thread::sleep_for( chrono::seconds(1)); // sleep for 1 seconds
  
  
    std::cout << "   Your individual test results are: " << std::endl;
    for(int i=0; i<=testNum; i++){
      //std::cout << "       Base Test  #" << i << ": " << (testResults[i] ? " Passed " : " Failed ") << std::endl;
      std::cout << "       Base Test  #" << i << ": "
                << (testResults[i] ? " \033[32mPassed " : " \033[31mFailed ")
                << "\033[0m" << std::endl;
      
      if (testResults[i])
        yourScore += 90.0 / (testNum+1);
    }
  
    for(int i=0; i<=bonusTestNum; i++){
      //std::cout << "       Bonus Test #" << i << ": " << (bonusTestResults[i] ? " Passed " : " Failed ") << std::endl;
          std::cout << "       Bonus Test #" << i << ": "
                << (bonusTestResults[i] ? " \033[32mPassed " : " \033[31mFailed ")
                << "\033[0m" << std::endl;
    }
    bonusScore /= (bonusTestNum+1);
  
    std::cout << "   Your Base score is " << yourScore << " out of 90 possible points " << std::endl;
    std::cout << "   Your Bonus score is " << bonusScore << std::endl;
    std::cout << "   Your Total score (preliminary) is " << (yourScore + bonusScore) << std::endl;
    std::cout << "   (You may be eligible for up to +10 more base points based on comments and user feedback, to be assessed after submission)" << std::endl;
  
  
  
    std::cout << std::endl;
  
    std::cout.flush();
  
    
  
  } // end TestMe constructor

};

TestMe testMeInstance; // creating the instance will automatically test your code.