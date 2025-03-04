/*
COMP 235

HW 4 : Blackjack Cards (Start)

  
   When everything is working, rename "TestMe.cpp.rename" to "TestMe.cpp", then rerun you rprogram


*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Hand.h"
#include "Card.h"
#include "BlackJack.h"

using namespace std;

int main() {

//   cout << "Let's Play BlackJack..." << endl;
//   Card queenOfHearts(45);      // This should work already with no changes since Card.h and Card.cpp are done
//   std::cout << queenOfHearts;  // This works because we have implemented

  
//   // STEP 1: test the Hand class below to be sure you have it working before you move on to BlackJack at bottom

//     Hand oneCardHand({ 0 });   // Hand with one card indicated via ID == 0 (ace of spades)
//     oneCardHand.printMe();     // print the hand
  
//     Hand twoCardHand({ 0, 7});  // Hand with two cards indicated via ID == 0, and ID == 7 (two of clubs)
//     twoCardHand.printMe();      // print the hand

//   // STEP 2: uncomment and test a "large" hand - the full deck of cards
  
//     srand(time(NULL));                                   // set the random number seed based on current time  , for the shuffle
//     std::vector<int> cardIDs;                            // we'll fill this up with card ids zero to 51
//     for(int i=0; i<52; i++)  cardIDs.push_back(i);       // here we are pushing integers which represent card IDS (not cards!)
//     random_shuffle(cardIDs.begin(), cardIDs.end());      // use iterators to shuffle the vector of cardIDs

//     Hand myDeck(cardIDs);    // now we are giving the Hand constructor a vector of INTEGERS (not cards!)
//     myDeck.printMe();       // print the Hand we constructed

//   // STEP 3: uncomment and test this below when you are sure your Hand class is fully implemented, to test your game

//     BlackJack game({ "Player A", "Dealer" }, cardIDs);   // specify both arguments; constructor should build full deck from provided ids
//     game.play();                                         // play the game 


  // STEP 4: Remove ".rename" from TestMe.cpp.rename and rerun to see your preliminary grade

  cout << "\nGoodbye" << endl;
  return 0; 
}