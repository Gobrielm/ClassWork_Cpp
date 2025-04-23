/*

 DONE : This header file has been fully written for you.

*/

#pragma once
#include <iostream>
#include <string>

class Piece; // this is called a forward reference: it tells the compiler that "Piece" will eventually be defined

class ChessBoard{
    public:
        const char colNames[9] = {'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}; // 
        Piece * lastPieceMovedSuccessfully = nullptr; // last piece that was successfully moved as a result of ChessBoard::takeTurn()
        enum columnLetters {a=1, b=2, c=3, d=4, e=5, f=6, g=7, h=8};
        const bool black = false; // abbreviation for "isWhite != true"
        const bool white = true;  // abbreviation for "isWhite == true"
        Piece *pieces[32]; // array of pointers to pieces on the board. this is the BASE class, even though we will assign derived pointers (NOTE OUR FORWARD REFERENCE ABOVE!)
        bool whiteTurn = true; // true if it is white's turn, else black (white goes first, by default)
        
        ChessBoard(); // default constructor: create the board and pieces
        bool isOccupied(int _row, int _col, bool silent = false); // determine if the location row, col is occupied by a piece on the board
        bool isClear(int fromRow, int fromCol, int toRow, int toCol, bool silent = false); // determine if the line from "from" to "to" is clear of all pieces      
        bool takeTurn(std::string pieceName, int row, int col, bool silent = false); // move the piece uniquely identified by name to the 1-based integer location row, col
        Piece *pieceAt(int _row, int _col); // return a pointer to the piece at the requested location on the chess board
        void printMe(); // print a character representation of the entire chessboard 
        bool isKingInCheck(bool isWhite, bool silent = false ); // return true if the specified KING (white or black) is currently in check
        std::string isCheckmate(); // BONUS +10 return "White", "Black" or "none" to indicate if either player is in checkmate and therefore has lost the game 
        bool isStalemate(); // BONUS +10 return true if the current state of the game is in stalemate (a tie)

        const char * redTextStart =          "\033[1;31m"; // change output text color to red (used in cout)
        const char * invertRedTextStart =    "\033[7;31m";
        const char * blueTextStart =         "\033[;34m";
        const char * greenTextStart =        "\033[;32m";
        const char * invertWhiteTextStart =  "\033[7;37m";
        const char * magentaTextStart =      "\033[;35m";
        const char * invertMagentaTextStart =  "\033[7;35m";
        const char * yellowTextStart =        "\033[4;33m";
        const char * invertCyanTextStart =    "\033[7;36m";
        const char * coloredTextEnd =         "\033[0m"; // end text color (for cout)

}; // end class chessBoard