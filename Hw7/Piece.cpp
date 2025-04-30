/*

  This file has been fully written for you


*/

#include <iostream>
#include <string>
#include "Piece.h"

// DONE FOR YOU: this ENTIRE file implementation is complete, but should be studied.

Piece :: Piece(int _row, int _col, bool _isWhite, std::string _name ){ // constructor 
    
    if(_row<1 || _row > 8) {
        std::cout << "piece() constructor: row = " << _row << " is out of bounds. Placing piece at row = 1 by default." << std::endl;
        _row = 1;
    }

    if(_col<1 || _col > 8) {
        std::cout << "piece() constructor: column = " << colNames[_col] << " is out of bounds. Placing piece at column = 1 by default." << std::endl;
        _col = 1;
    }
    
    neverMoved = true; // this piece has never been moved
    row=_row; // 1-based row # location of this piece (1..8)
    col=_col; // 1-based col # location of this piece (1..8 corresponds to a...h)
    ptype = "unknown";  // string name of type of piece like "rook" "king", "queen", etc.  Different than specified piece name below
    isWhite = _isWhite; // true if white piece, otherwise black
    name = _name; // r1b, p1b, p4b, kib, etc.
    board = nullptr; // a "back-pointer" to an instance of the ChessBoard by each piece
}

std::string Piece :: colorName(){ 
  // return a string that describes if this piece is White or Blank, based on the the isWhite bool member
  return ( isWhite ? "White" : "Black" );
}


// destructor - invoked from destructor of derived class

Piece :: ~Piece(){ std::cout<<"Destructing piece base class" << std::endl; }


// member functions

void Piece :: printMe(){ // print out a debug description of each piece
  std::cout << "Color: " << colorName();
  std::cout << "Type: " << ptype << ", ";
  std::cout << "Location = (" << row << "," << colNames[col] << ") ";
  std::cout << "Is Captured = " << (isCaptured ? "True" : "False") << std::endl;
} // end printMe()


// true if the row, col location specified is "legal" or not (to avoid crashing when bad input is provided
// not that this is 1-based and not zero based)
bool Piece :: isOnBoard(int _row, int _col){
    
    if((_row<1 || _row > 8)  || (_col<1 || _col > 8) ){ 
        return false; // NO it is not a legal row col specification
    }
    else
        return true; // YES it is a legal row col specification
} // end isOnBoard()


// this is a virtual method that SHOULD be overwritten in each derived class
// that means we will never really call this method, unless some derived class has not yet implemented this method
// in that case, this method would serve as a fall-back method to simply see if the row, col specification is legal or not
// as such this is really just a debug method that should not be called once the game is fully implemented
  bool Piece :: isLegalMoveTo(int _row, int _col) {
    
    std::cout << "Baseclass isLegalMoveTo() here.."   << std::endl;
    
    if (isOnBoard(_row, _col)) 
        return true;
    else
        return false;
}   // virtual method to be implemented in derived classes


// this is the generic (base class) method that all pieces can use (it is NOT over-ridden by a derived class)
// please note however that this method DOES call a method isLegalMoveTo() that IS over-ridden by a derived class
// this technique allows a base-class method to call a derived method, which is the "key aspect" of this assignment
// see **** below where this method is called

bool Piece::moveTo(int _row, int _col, bool silent , bool whatIf ){ // return true if the piece was moved to the requested 1-based row, col location
  // whatIf, when true, allows us to return if a move is possible, without affecting the board  
  
  if(row==_row && col==_col){ // if the move is not to the same location
      if (!silent) std::cout << "piece.moveTo() : " << colorName() << " " << ptype <<  " move from (" << row << ", " << colNames[col] <<  ") to (" << _row << ", " << colNames[_col] << ") is a NON-move (the piece did not move). Abort Move." << std::endl;;
      return false;
  }
  
  if(!isOnBoard(_row, _col)) { // if the move is actually on the board
     if (!silent)  std::cout << "piece.moveTo() : " << colorName() << " " << ptype <<  " move from (" << row << ", " << colNames[col] <<  ") to (" << _row << ", " << colNames[_col] << ") is off the board. Abort Move." << std::endl;;
      return false;
  }

  // Check if the final location is occuped by a same-colored piece
  // if yes, then we are blocked by our own piece - return false
  // if no, then we MIGHT have a capture
  
  Piece *endPiece = board->pieceAt(_row, _col);  // see if there is a piece at the "to" location

  if (endPiece != nullptr ) { // found a piece, now check its color
      if (!silent) std::cout << "piece.moveTo() : Checking end piece = "  << endPiece->name << std::endl;
      
      if (endPiece->isWhite == isWhite) {
          if (!silent) std::cout << "piece.moveTo() : This move is blocked at the 'to' location by a same-colored piece!. Abort move." << std::endl;
          return false;
      }
  } // done checking "to" location for same-colored piece
  
  if (!isLegalMoveTo(_row, _col)){ // **** this will call the method from the inherited class, not the Piece class
      if (!silent) std::cout << "piece.moveTo() : " << colorName() << " " << ptype <<  " move from (" << row << ", " << colNames[col] <<  ") to (" << _row << ", " << colNames[_col] << ") is not valid for the " << ptype <<". Abort Move." << std::endl;;
      return false;
  }


   // make the move... noting that if it puts the king in check, we will revert the move
  
  int origRow = row; // remember the original piece location in case the move leaves the current king in check
  int origCol = col;

  bool origCapture = false;
  Piece *capturedPiece = nullptr; // a pointer to a piece we may land on, below

  if (this->board->isOccupied(_row, _col)) { // now check to see if we made a capture of a previously uncaptured piece
    capturedPiece = this->board->pieceAt(_row, _col); // get the piece at this location
    origCapture = capturedPiece->isCaptured; // record this so we can undo it below, if the king is still in check
    capturedPiece->isCaptured = true; // indicate that the piece we landed on is captured
  }

  row=_row; // update the row location of this piece
  col=_col; // update the col location of this piece

  // Is my King in Check from this move?
  if (board->isKingInCheck( this->isWhite, true) ) { // (true -> DO SILENT) If this move puts or leaves this piece's same-color king in check , then we cannot make it.
    if (!silent) std::cout << board->redTextStart << "piece.moveTo() : " << colorName() << " " << ptype <<  " move from (" << origRow << ", " << colNames[origCol] <<  ") to (" << _row << ", " << colNames[_col] << ") is not valid because it would put (or leave) its own King in check. Abort Move." << board->coloredTextEnd << std::endl;
    row = origRow; // put this piece back to its original location
    col = origCol;
    if ( capturedPiece != nullptr ) 
      capturedPiece->isCaptured = origCapture; // return the captured piece to the chess board for continued play
    return false;
  }

  if ( whatIf ) { // we are only being asked if this move is possible, so return true, but leave the board unchanged
    if (!silent) std::cout << board->redTextStart << "piece.moveTo() : (WHAT IF?)" << colorName() << " " << ptype <<  " COULD move from (" << origRow << ", " << colNames[origCol] <<  ") to (" << _row << ", " << colNames[_col] << ") BUT NO ACTION TAKEN. Abort Move." << board->coloredTextEnd << std::endl;
    row = origRow; // put this piece back to its original location
    col = origCol;
    if ( capturedPiece != nullptr ) 
      capturedPiece->isCaptured = origCapture; // return the captured piece to the chess board for continued play
    return true; // yes this move would have worked, but we are just testing and reporting back.
  } // end whatif

  // report the successfull move
    
  std::cout << "piece.moveTo() : " << colorName() << " " << ptype <<  " moves from (" << origRow << ", " << colNames[origCol] <<  ") to (" << _row << ", " << colNames[_col] << ")." << std::endl;

  if (capturedPiece != nullptr &&  capturedPiece->isCaptured) 
    std::cout  << board->yellowTextStart << "piece.moveTo() : " << colorName() << " " << ptype <<  " captures " << capturedPiece->colorName()  << " " << capturedPiece->ptype << board->coloredTextEnd << std::endl;
  
  neverMoved = false; // record that this piece has been moved from its original location
  return true; // return true to indicate a successful move
  
} // end: Piece::moveTo()