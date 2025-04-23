/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include "ChessBoard.h"

// Our chessboard, from white's perspective:
//  rows goes from 1 through 8, columns from a through h
//
//     a   b   c   d   e   f   g   h  
// 8: r1b h1b b1b qub kib b2b h2b r2b 
// 7: p1b p2b p3b p4b p5b p6b p7b p8b 
// 6: --- --- --- --- --- --- --- --- 
// 5: --- --- --- --- --- --- --- --- 
// 4: --- --- --- --- --- --- --- --- 
// 3: --- --- --- --- --- --- --- --- 
// 2: p1w p2w p3w p4w p5w p6w p7w p8w 
// 1: r1w h1w b1w quw kiw b2w h2w r2w 

// This file describes a generic chess piece

class Piece{ // parent (base) class from which all chess pieces are derrived from (inherits from)
    private:
      const char colNames[9] = {'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}; // character names of our columns (x is never printed)
      
    public:

      bool neverMoved; // true if this piece has never been moved
      bool isCaptured; // true if this piece was captured
      int row; // row that this piece occupies : row 1, 2, 3, 4, 5, 6, 7, 8
      int col; // column that this piece occupies: col a, b, c, d, e, f, g, h (also enums 1-8)
      std::string ptype; // king, queen, bishop, knight, rook, pawn
      bool isWhite; //  true means white, else black
      std::string name; // what we call this piece - a unique human-readable identifier
      ChessBoard *board; // pointer to the game board
    
     // constructors
        
      Piece();
      Piece(int _row, int _col, bool _isWhite, std::string _name);
        // _row is the integer row location of the piece on the board (starting from 1)
        // _col is the integer column location of the piece on the board (starting from 1)
        //  _isWhite is true if this is a white piece, else false means black piece
        // _name is the screen name like r1b for "rook 1 black" (of 2 rooks), or p4 for "pawn 4 black" (of 8 pawns)

    // destructor
    
    virtual ~Piece();
        
    // member functions
        
      void printMe(); // print a description of this piece
      bool moveTo(int _row, int _col, bool silent = false, bool whatIf = false); 
      bool isOnBoard(int _row, int _col); // true if this piece is on the board
      std::string colorName(); // return a string that is the color name "white" or "black", for printing
      virtual bool isLegalMoveTo(int _row, int _col);   // virtual function to be implemented in derived classes.  Piece cannot answer this question about rook, for example, so the Rook.cpp class must implement this function, even though it may be called by a Piece.cpp method
};