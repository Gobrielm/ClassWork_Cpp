/*
COMP 235

HW 3 : Connect Four (Start)


*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "ConnectFour.h"

using namespace std;

int main() {

  cout << "Let's Play Connect Four..." << endl;

  srand(time(nullptr)); // uncomment to we have a random game every time 
  // OR: replace time(nullptr) with any integer (ex 5) to ensure identical results while testing
  
  // When ready to TEST, RENAME the file "testMe.cpp.rename" to "testMe.cpp" (remove the '.rename' extension) 

  ConnectFour game('.', {'X', 'O'}); // construct the game, specify an empty character and  vector of any number of player tokens
  // game.play();                       // play the game until over
  game.printBoard();
  cout <<  "\nGoodbye!"  << endl;
}