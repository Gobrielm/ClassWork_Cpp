/*

DONE - this file has been written for you

*/

#include <iostream>
#include "Token.h"
 
 Token::Token(char l, int r, int c){
        letter = l; // the ascii character that represents the puzzle piece
        row = r; // the row location of the puzzle piece
        col = c; // the column location of the puzzle piece
  }

  Token::~Token(){ 
     // NOTE: you can uncomment this line below to help you debug and SEE when Token instances are being deleted
    //    That should occur when your ~Puzzle destrcutor gets called when you delete a Puzzle instance
//     std::cout << "Token Destructor: deleting Token from location row,column = (" << row << ", " << col << ")" << std::endl;
  }

  void Token::printMe(){
       std::cout << "  Puzzle piece \'" << letter << "\' is located at at row, col = (" << row << ", " << col << ")" << std::endl;
  }