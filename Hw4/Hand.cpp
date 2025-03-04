#include <iostream>
#include "Hand.h"
#include "Card.h"

// constructor: converts requested vector of card IDs into Card instances; defaults to empty Hand
Hand::Hand(std::vector<int> initialCards) {
    for (int x: initialCards) {
        cards.push_back(Card(x));
    }
}

// print out the hand from “top to bottom”
void Hand::printMe () {
    std:: cout << "{ ";
    int counter = 0;
    for (Card card: cards) {
        std::cout << card;
        if (counter != cards.size() - 1) {
            std::cout << ", ";
        }
        counter++;
    }
    std:: cout << "} ";
    
}
 // return int of how many cards in the Hand
int Hand::size() {
    return cards.size();
}

// “deal” a card from the top: remove it and return a copy of it
Card Hand::dealACard() {
    Card toReturn = cards.front();
    cards.pop_front();
    return toReturn;
}

// add a new card to the top of a Hand
void Hand::addACard(Card newCard) {
    cards.push_front(newCard);
}

// return an integer value that represents the sum of all card values in this Hand
int Hand::getPoints() {
    int sum = 0;
    for (Card card: cards) {
        sum += card.value;
    }
    return sum;
} 

// BONUS: return true if the Hand currently contains any Ace card
bool Hand::hasAnAce() {
    for (Card card: cards) {
        if (card.name == "Ace") {
            return true;
        }
    }
    return false;
}