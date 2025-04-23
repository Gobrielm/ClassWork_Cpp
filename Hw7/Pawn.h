/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <iostream>
#include <string>
#include "Piece.h"

class Pawn : public Piece{ // Pawn derives (inherits from) from Piece
    
  public:
    Pawn(int _row, int _col, bool _isWhite, std::string _name); // construct a Pawn at this location, of the specified color, with the specified screen name (p1b, p2b, ... p8b,  p1w, p2w, ... p8w )
    ~Pawn(); // destructor
    bool isLegalMoveTo(int _row, int _col); // true if this Pawn can move to the specified location from its current location
    
};