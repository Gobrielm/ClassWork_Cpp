/*

  DONE : this header file has been fully written for you

*/

#ifndef CARD_H
#define CARD_H
#include <iostream>

  class Card{
    public:
      int value; // point value of the card (NOT THE ID!)
      std::string name; // like Ace, One, Two, Three, ... Queen, King
      std::string suit; // like Spades, Hearts, Diamonds, Clubs

      Card(int ID = -1);  // valid ID values go from 0 to 51; -1 means an invalid card aka JOKER

      friend std::ostream& operator<<(std::ostream& os, Card const &n) {
        return os <<  n.name << " of " << n.suit << "(" << n.value << ")" ;
      }

  };

  #endif