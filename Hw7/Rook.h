/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <string>
#include "Piece.h"

class Rook : public virtual Piece{  // Rook derives from (inherits from) Piece
  public:
    Rook(int _row, int _col, bool _isWhite, std::string _name); // construct a Rook this location, of the specified color, with the specified screen name (r1b, r2b, r1w, r2w)
    ~Rook();  // destructor
    virtual bool isLegalMoveTo(int _row, int _col); // true if this Rook can move to the specified location from its current location
};