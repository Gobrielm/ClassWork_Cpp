/*
COMP 235

HW 5 : Jigsaw Puzzle (Start)


*/

#include <iostream>
#include "Puzzle.h"
#include "Token.h"
// STEP 1: include necessary .h files

using namespace std;

 int main() {

  cout << "Building a Jigsaw Puzzle...." << endl;
  // STEP 2: declare a myPuzzle_ptr variable that holds a POINTER to a Puzzle Instance (NOT a Puzzle instance). Set it to nullptr
  Puzzle* myPuzzle_ptr = nullptr;

  // STEP 3: create a new (dynamically allocated) Puzzle instance and store its pointer in myPuzzle_ptr, Pass its constructor the puzzle_input_basic.txt file name
  myPuzzle_ptr = new Puzzle("puzzle_input_basic.txt");
  // STEP 4: print a raw description all the pieces in the puzzle by calling the printPieces() method from the puzzle pointer (this is not the same as printing the puzzle image)
   myPuzzle_ptr -> printPieces();
  // STEP 5: initialize the grid and then load it with all the Token pointers by calling the loadGrid() method from the myPuzzle_ptr pointer
   myPuzzle_ptr -> loadGrid();
  // STEP 6: print the final puzzle image by calling the printGrid() method from the myPuzzle_ptr pointer
   myPuzzle_ptr -> printGrid();
  // STEP 7: delete the what the myPuzzle_ptr pointer points to: a Puzzle instance, effectively calling the Puzzle destructor
    delete myPuzzle_ptr;
  cout << "\nGoodbye" << endl;
  return 0;
}
