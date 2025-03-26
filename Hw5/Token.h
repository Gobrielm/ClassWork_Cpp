#ifndef TOKEN_H
#define TOKEN_H

 // This file is only needed and provided as an example, if you choose to pursue the bonus for this assignment.
 // To use this file, you would copy the contents to the Token.h file and be sure to update your Token.cpp file with 
 // the contents of the Token_bonus.cppX file, if desired

class Token{ // description of a puzzle piece
friend class Puzzle; // declare Puzzle to be a friend of Token class
  private:

      char letter; // the ascii character that represents this puzzle piece
      int row; // row location of the puzzle piece in the puzzle grid - not known when the constructor is called
      int col; // column location of this puzzle piece in the puzzle grid - not known when the constructor is called
      int id; // the unique integer id of this puzzle piece
      int top; // the id of the puzzle piece directly above this piece, or zero if this puzzle piece is along the top edge of the puzzle.
      int right; //  the id of the puzzle piece directly to the right of this piece, or zero if this puzzle piece is along the right edge of the puzzle.
      int bottom; // the id of the puzzle piece directly below this piece, or zero if this puzzle piece is along the bottom edge of the puzzle.
      int left;

  public:
      Token(char l, int id, int top, int right, int bottom, int left); // constructor that creates a token based on a letter, id, and 4 neighboring ids
      ~Token(); // destructor - what gets called any time a Token instance is deleted or goes out of scope
      void printMe(); // print a one-line description of the token include its ascii character, row, & column
};
#endif