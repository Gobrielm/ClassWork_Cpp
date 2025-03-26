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
  // This lambda function serves to replace the deprecated random_shuffle() function from the algorithm library
  auto random_shuffle = [](auto first, auto last) {
    if (first == last) return;
    for (auto it = last - 1; it > first; --it) {
        int j = std::rand() % (it - first + 1);  // generate a random index
        std::iter_swap(it, first + j);          // swap elements
    }
  }; // end function definition 
  
  srand(time(NULL));
  std::vector<int> cardIDs;
  for(int i=0; i<52; i++)  cardIDs.push_back(i);
  random_shuffle(cardIDs.begin(), cardIDs.end());

  BlackJack game({ "Player A", "Dealer" }, cardIDs);   
  game.play();

  cout << "\nGoodbye" << endl;
  return 0; 
}