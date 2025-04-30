/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <string>
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop,  public Rook { // NOTE !! Queen derives from (inherits from) Bishop and Rook!
    
  public:
    Queen(int _row, int _col, bool _isWhite, std::string _name); // construct a Queen this location, of the specified color, with the specified screen name (qub, quw)
    ~Queen();     // destructor
    bool isLegalMoveTo(int _row, int _col) override; // true if this Queen can move to the specified location from its current location
    
};