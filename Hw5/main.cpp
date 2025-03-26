/*
COMP 235

HW 5 : Jigsaw Puzzle (Start)


*/

#include <iostream>
#include "Puzzle.h"
#include "Token.h"


using namespace std;

 int main() {

  cout << "Building a Jigsaw Puzzle...." << endl;
  Puzzle* myPuzzle_ptr = nullptr;

  myPuzzle_ptr = new Puzzle("puzzle_input_bonus.txt");

  myPuzzle_ptr -> printPieces();

  myPuzzle_ptr -> loadGrid();

  myPuzzle_ptr -> printGrid();

  delete myPuzzle_ptr;

  cout << "\nGoodbye" << endl;
  return 0;
}
