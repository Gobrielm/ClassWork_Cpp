/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <iostream>
#include <string>
#include "Piece.h"

class King : public Piece{ // King derives from (inherits from) Piece
    
  public:
        
    King(int _row, int _col, bool _isWhite, std::string _name); // construct a King at this location, of the specified color, with the specified screen name (kib, kiw)
     ~King();     // destructor
    bool isLegalMoveTo(int _row, int _col);// true if this King can move to the specified location from its current location
};