/*

  DONE : this header file has been fully written for you

*/

#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Token.h"

class Puzzle{

  public:

    Puzzle(std::string fileName);  // constructor: using the filename, load the puzzle pieces into the dynamic pieces array
    void printPieces(); // print the list of randomized puzzle pieces
    void loadGrid(); // allocate the grid and copy pieces pointers to their correct location int the grid;
    ~Puzzle(); // destructor - when we delete the Puzzle instance, the destructor should clean up all "new" allocations for pieces and grid
    void printGrid(); // print the entire puzzle, using the grid data member 

  private:
    int pieceCount; // number of pieces in the entire puzzle
    int rowCount; // number of rows in the puzzle (NOT the number of the last row!)
    int colCount; // number of columns in the puzzle (NOT the number of the last column)
    Token **pieces; // dynamic array of pointers to Tokens.  Token instances will be dynamically allocated.
    Token*** grid; // dynamic 2D array of pointers to arrays of pointers to Tokens stored in pieces array.
    std::unordered_map<int, Token*> id_to_token;
    Token* upper_left = nullptr;
};

#endif