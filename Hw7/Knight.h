/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <iostream>
#include <string>
#include "Piece.h"

class Knight : public Piece{ // Knight derives (inherits from) from Piece
    
  public: 
    Knight(int _row, int _col, bool _isWhite, std::string _name); // construct a Knight at this location, of the specified color, with the specified screen name (h1b, h2b, h1w, h2w)
    ~Knight(); // destructor
    bool isLegalMoveTo(int _row, int _col); // true if this Knight can move to the specified location from its current location
};