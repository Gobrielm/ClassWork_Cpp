/*

  DONE : this header file has been fully written for you

*/

#ifndef TOKEN_H
#define TOKEN_H

class Token{ // description of a puzzle piece
friend class Puzzle; // declare Puzzle to be a friend of Token class
  private:

      char letter; // the ascii character that represents this puzzle piece
      int row; // row location of the puzzle piece in the puzzle grid
      int col; // column location of this puzzle piece in the puzzle grid

  public:
      Token(char l, int r, int c); // constructor that creates a token based on a letter, row, and column
      ~Token(); // destructor - what gets called any time a Token instance is deleted or goes out of scope
      void printMe(); // print a one-line description of the token include its ascii character, row, & column
};
#endif