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
  srand(time(NULL));
  std::vector<int> cardIDs;
  for(int i=0; i<52; i++)  cardIDs.push_back(i);
  random_shuffle(cardIDs.begin(), cardIDs.end());

  BlackJack game({ "Player A", "Dealer" }, cardIDs);   
  game.play();

  cout << "\nGoodbye" << endl;
  return 0; 
}