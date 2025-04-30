/*

  This file has been fully written for you

  UNLESS you choose to pursue the bonus methods, stubbed out at the bottom of the file:

    bool ChessBoard :: isCheckmate()
    bool ChessBoard :: isStalemate()

*/


#include <iostream>
#include <cmath>
#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"

ChessBoard :: ChessBoard(){ // default constructor
  std::cout << "ChessBoard() default constructor here"  << std::endl;

  int count=0; // count of pieces we have created so far, used below

  // Black Pieces
  pieces[count++] = new Rook(  8, a, black, "r1b"); // upper left corner  black
  pieces[count++] = new Knight(8, b, black, "h1b"); // 
  pieces[count++] = new Bishop(8, c, black, "b1b"); //
  pieces[count++] = new Queen( 8, d, black, "qub"); // 
  pieces[count++] = new King(  8, e, black, "kib"); // KING == position 4
  pieces[count++] = new Bishop(8, f, black, "b2b"); // 
  pieces[count++] = new Knight(8, g, black, "h2b"); // 
  pieces[count++] = new Rook(  8, h, black, "r2b"); //  upper right corner black
  
  pieces[count++] = new Pawn(7, a, black, "p1b"); // upper leftmost pawn black
  pieces[count++] = new Pawn(7, b, black, "p2b"); // 
  pieces[count++] = new Pawn(7, c, black, "p3b"); // 
  pieces[count++] = new Pawn(7, d, black, "p4b"); // 
  pieces[count++] = new Pawn(7, e, black, "p5b"); //     
  pieces[count++] = new Pawn(7, f, black, "p6b"); //
  pieces[count++] = new Pawn(7, g, black, "p7b"); //
  pieces[count++] = new Pawn(7, h, black, "p8b"); //     

  // white pieces
  pieces[count++] = new Rook(  1, a, white, "r1w"); // lower left corner  white
  pieces[count++] = new Knight(1, b, white, "h1w"); // 
  pieces[count++] = new Bishop(1, c, white, "b1w"); //
  pieces[count++] = new Queen( 1, d, white, "quw"); // 
  pieces[count++] = new King(  1, e, white, "kiw"); //  KING == position 4 + 16 = 20
  pieces[count++] = new Bishop(1, f, white, "b2w"); // 
  pieces[count++] = new Knight(1, g, white, "h2w"); // 
  pieces[count++] = new Rook(  1, h, white, "r2w"); // lowerright corner white
  
  pieces[count++] = new Pawn(2, a, white, "p1w"); // lower leftmost pawn white
  pieces[count++] = new Pawn(2, b, white, "p2w"); // 
  pieces[count++] = new Pawn(2, c, white, "p3w"); // 
  pieces[count++] = new Pawn(2, d, white, "p4w"); // 
  pieces[count++] = new Pawn(2, e, white, "p5w"); //     
  pieces[count++] = new Pawn(2, f, white, "p6w"); //
  pieces[count++] = new Pawn(2, g, white, "p7w"); //
  pieces[count++] = new Pawn(2, h, white, "p8w"); //

  // store the pointer to the board within each piece so each can reference the
  // board in the Piece :: moveTo() function

  for (int p = 0; p < 32; p++)
    pieces[p]->board = this; // "this" is "this instance of the Chessboard".. we want to be
              // able to find the board from each piece

} // end chessboard constructor


// return true if the location row, col is occupied by a piece on the board
bool ChessBoard ::isOccupied(int _row, int _col, bool silent) {

  for (int p = 0; p < 32; p++) {
    if (pieces[p]->isCaptured) // don't check pieces which have already been captured
      continue;

    if ((pieces[p]->row == _row) && (pieces[p]->col == _col)) { // there is a piece here already
      if (!silent) 
        std::cout << "isOccupied()  rc = (" << _row << ", " << colNames[_col]  << ") is occupied by " << pieces[p]->name <<std::endl;
      return true;
    }
  }
  return false; // nothing on that row, col space
}

// return true if the horizontal, diagonal or vertical line indicated is clear of all pieces
bool ChessBoard :: isClear(int fromRow, int fromCol, int toRow, int toCol, bool silent){ // determine if the line from "from" to "to" is clear
    

  if (!silent) std::cout << "isClear() here checking from  (" << fromRow << "," << colNames[fromCol] << ") to (" << toRow << ", " << colNames[toCol] << ")" <<std::endl;

  
  if (abs(fromRow-toRow)<=1 && abs(fromCol-toCol)<=1)
    return true;  // by definition anything <=1 unit away in either direction is "clear"
  
  else if (fromRow==toRow){ // check horizontal
    int colInc = (fromCol<=toCol ? 1 : -1);
    for(int c=fromCol; c!=toCol; c+=colInc) { // start at fromCol, in the direction of toCol
                              
      if (c==fromCol || c==toCol)
        continue; // skip start or ending column
      
      if (isOccupied(fromRow,c, silent)) {// if this location is occupied, start and end positions
          return false; // the way is blocked by a piece here, so we return false
      }
    }
      
    return true; // the way must be clear
      
  }
  
  else if (fromCol==toCol) { // check vertical
    int rowInc = (fromRow<=toRow ? 1 : -1);
    
    for(int r=fromRow; r!=toRow; r+=rowInc) { // start at fromRow, in the direction of toRow
                            
      if (r==fromRow || r==toRow)
        continue; // skip start or ending column
      
      if (isOccupied(r,fromCol, silent)) {// if this location is occupied, start and end positions
        return false; // the way is blocked by a piece here, so we return false
      }
    }
    return true; // way must be clear
  }
  
  else if (abs(fromRow-toRow) == abs(fromCol-toCol) ) { // diagonal
      int rowInc = (fromRow<=toRow ? 1 : -1);
      int colInc = (fromCol<=toCol ? 1 : -1);
      // std::cout << "isClear(): rowInc = "  << rowInc <<std::endl;
      // std::cout << "isClear(): colInc = "  << colInc <<std::endl;
      
      for(int r=fromRow, c=fromCol; r!=toRow; r+=rowInc, c+=colInc) { // start at fromRow, fromCol, in the direction of toRow, toCol
          
          if (r==fromRow && c==fromCol)
              continue; // skip starting location
          
          if (r==toRow && c==toCol)
              continue; // skip ending location
          
          if (isOccupied(r,c, silent)) {// if this location is occupied, start and end positions
              return false; // the way is blocked by a piece here, so we return false
          }
      }
      return true; // the way must be clear
  }
  
  else {
      std::cout << "isClear(): Warning.  Cannot check arbitrary angles between (" << fromRow << "," << colNames[fromCol] << ") to (" << toRow << ", " << colNames[toCol] << "). Returning true (clear)." <<std::endl;
      return true;
  }
} // end: ChessBoard :: isClear()


// attempt to move the specified piece (by name) to the specified row, column loation
// note that row and column are 1-based integer inputs that specified the 1-based row and column we are want to move to
bool ChessBoard :: takeTurn(std::string pieceName, int row, int col, bool silent ){
    if (!silent) std::cout << "ChessBoard::takeTurn(): Move " << pieceName << " to rc = (" << row << ", " << colNames[col] << ")" <<std::endl;
    
    for(int p=0; p<32; p++){ // look for the piece we are trying to move amongst all pieces[] pointers
      
      if (pieces[p]->name == pieceName) { // found the piece
        if (pieces[p]->isCaptured) { // skip captured pieces
          if (!silent) std::cout <<  blueTextStart << "ChessBoartakeTurn(): Sorry, it you cannot move a capture piece. Move aborted. Still "  << (!pieces[p]->isWhite == 0 ? "Black's turn." : "White's turn.") << coloredTextEnd <<std::endl;
          return false;
        }
      
        if (pieces[p]->isWhite != this->whiteTurn) { // make sure we are moving a piece from the proper color
          if (!silent) std::cout <<  blueTextStart << "ChessBoartakeTurn(): Sorry, it is not your turn," << (pieces[p]->isWhite == 0 ? "Black" : "White") << ". Move aborted. Still "  << (!pieces[p]->isWhite == 0 ? "Black's turn." : "White's turn.") << coloredTextEnd <<std::endl;
          return false;
        }
        if (pieces[p]->moveTo(row, col, silent )) // did the move succeed?
          whiteTurn = (whiteTurn== white ? black : white ); // change turns if move was successful
        else {
          if (!silent) std::cout << blueTextStart << "\nChessBoard::takeTurn(): Sorry, that move did not succeed. Move aborted.  The turn still belongs to " << (whiteTurn== white ? "White" : "Black" ) << coloredTextEnd << std::endl;
          return false;
        }
        if ( isKingInCheck( whiteTurn, false ) )  // Has the successful move has put the king of the new-current turn's color is in check?  (not silent)
          std::cout << "\nChessBoard::takeTurn(): !!!! The turn succeeded... " << redTextStart << "now the " << (whiteTurn== white ? "White" : "Black" ) <<  " King is in check!!!" << coloredTextEnd << std::endl; // print info message for the new-current player

        lastPieceMovedSuccessfully = pieces[p]; // save this piece so we can print it in a different color in printMe()
        return true; // done moving the piece, we can return now
      }
    } // done looping through all pieces

  if (!silent) std::cout << blueTextStart << "\nChessBoard::takeTurn(): Sorry, the piece named " << pieceName << " is not valid. Move aborted.  The turn still belongs to " << (whiteTurn== white ? "White" : "Black" ) << coloredTextEnd << std::endl;
  
  return false; // failed turn - something's amiss, as we should never have gotten this far
  
} // end: ChessBoard :: takeTurn()

// get a pointer to the Piece instance (if any) at the specified row, column location
Piece * ChessBoard :: pieceAt(int _row, int _col){ // return a pointer to the piece at the requested location
    for(int p=0; p<32; p++){ // search all pieces
        if (pieces[p]->isCaptured) // skip captured pieces
            continue;
        
        if (pieces[p]->row == _row && pieces[p]->col == _col) {
            return pieces[p]; // return a pointer to the piece at this location
        }
    }
    
    return nullptr; // else return a null pointer
} // end ChessBoard :: pieceAt()

// print the chessboard
void ChessBoard :: printMe(){
    
    std::cout <<std::endl;

    
    // print column headings
    
    std::cout << "   ";
    for(int c=a; c<=h; c++) {std::cout << " " << colNames[c] << "  ";}
    std::cout <<std::endl; // end the label of column names
    
    
    for(int r=8; r>=1; r--) {
        std::cout << r << ": "; // print row heading
        
        for(int c=a; c<=h; c++) {
            bool found = false;
            for(int p=0; p<32; p++){ // check every piece
                if (pieces[p]->isCaptured) // skip captured pieces
                    continue;
                if (pieces[p]->row==r && pieces[p]->col==c) { // found the piece at this location
                  // if ( pieces[p]->ptype == "King" && isKingInCheck( pieces[p]->isWhite, true )   ) // true => silent test for check
                  //   std::cout << invertRedTextStart << pieces[p]->name << coloredTextEnd; // print in red
                    
                  // else 
                    if ( pieces[p] == lastPieceMovedSuccessfully )
                    std::cout << (pieces[p]->isWhite? invertWhiteTextStart : invertMagentaTextStart ) << pieces[p]->name << coloredTextEnd << " "; // mark last move in green
                  else if ( !pieces[p]->isWhite )
                    std::cout << magentaTextStart << pieces[p]->name << coloredTextEnd << " "; // mark last move in green
                  else
                    std::cout << pieces[p]->name << " ";
                  found = true;
                  break; // break out of search for pieces
                }
            }
            if (!found)
                std::cout << "--- "; // no piece here
        } // done with this row
        std::cout <<std::endl; // terminate the row
        std::cout <<std::endl; // add a space
    } // done with the rows
    
    std::cout << "   ";// more column labels at bottom
    for(int c=a; c<=h; c++) {std::cout << " " << colNames[c] << "  ";} 
    std::cout << std::endl << std::endl << std::endl; // end the label of column names

} // end ChessBoard :: printMe()


// return true if the King of the color specified is currently in check
bool ChessBoard :: isKingInCheck(bool isWhite, bool silent  ) {

  if (!silent) std::cout << "ChessBoard::isKingInCheck(): Testing to see if the " << (isWhite ? "White" : "Black" ) << " King is in check by testing every enemy piece on the board... \nthis will likely generate output from derived piece classes that are not silent." << std::endl;
  // handle case where we must capture in a "what if" move before we call this function, to determine if the threat has been eliminated

  Piece * thisKing = nullptr; // pointer to the King of the specified color

  if ( !isWhite) 
    thisKing = pieces[ 4 ]; // get a pointer to the king of the current color (for the current turn)
  else 
    thisKing = pieces[ 4 + 16 ];  // get the other king

  int offset = 0; // used below to test pieces of the opposite color
  if (!isWhite)  offset +=16; // use this offset to shift into the white pieces, because the piece we are moving is black (else state at zero)

  for (int i=offset; i<16+offset; i++) { // check all the white pieces if this move is for a black piece, else check the black pieces
    Piece * enemyPiece = pieces[ i ]; // get a pointer to the piece that could attack this king
    
    if ( enemyPiece->isCaptured ) continue; // skip pieces which have been captured
    
    if ( enemyPiece->isLegalMoveTo( thisKing->row, thisKing->col ) ) { // if legal for this enemy piece to move to this king, then the move is not legal
      // if (!silent) std::cout << "\nChessBoard::isKingInCheck(): Sorry, that move would put the King of the same color in check. Move aborted.  The turn still belongs to " << (whiteTurn== white ? "White" : "Black" ) << std::endl;
      if ( !silent) std::cout << redTextStart << "\nChessBoard::isKingInCheck(): !!!! The " << (isWhite ? "White" : "Black" ) <<  " King is in check from " << enemyPiece->name << "!!!" << coloredTextEnd << std::endl; // print info message for the new-current player

      return true;
    }
  } // end checking all enemy pieces
  
  return false;
} // end ChessBoard :: isKingInCheck()


// TODO BONUS: +5 Indicate if either player has won via checkmate
std::string ChessBoard :: isCheckmate(){ // return a string that indicates the winnning color, or None, if not checkMate for the current color
    
    return "None"; // Return only "White", "Black", or "None"
  
} // end ChessBoard :: isCheckMate()

// TODO BONUS: +5 Indicate if the game status is stalemate
bool ChessBoard :: isStalemate(){ // return true if the game current player is not in check, but any possible move for the current player would be illegal
    
    return false; // Return only true or false
  
} // end ChessBoard :: isCheckMate()
   
