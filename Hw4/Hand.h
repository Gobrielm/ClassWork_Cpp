/*

  DONE : this header file has been fully written for you

*/

#ifndef HAND_H
#define HAND_H
#include <list>
#include <vector>
#include "Card.h"

class Hand {
  std::list<Card> cards;  // list container - no brackets avaialble!  []; so you must use iterators!
  
  public:     
    Hand(std::vector<int> initialCards = {}); // constructor: converts requested vector of card IDs into Card instances; defaults to empty Hand
    void printMe (); // print out the hand from “top to bottom”
    int size (); // return int of how many cards in the Hand
    Card dealACard();      // “deal” a card from the top: remove it and return a copy of it
    void addACard(Card newCard);  // add a new card to the top of a Hand
    int getPoints();   // return an integer value that represents the sum of all card values in this Hand
    bool hasAnAce(); // BONUS: return true if the Hand currently contains any Ace card
};

#endif