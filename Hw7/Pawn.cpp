#include "Pawn.h"

Pawn::Pawn(int _row, int _col, bool _isWhite, std::string _name): Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Pawn";
}

Pawn::~Pawn(){
    std::cout<<"Destructing Pawn Class" << std::endl;
}

bool Pawn::isLegalMoveTo(int _row, int _col) {

    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    bool status = false;
    
    int row_diff = _row - row;
    int col_diff = _col - col;

    //Check if capturing
    if (temp && temp -> isWhite != isWhite) {
        //If capturing, must move left/right 1 space
        if (abs(col_diff) != 1) {
            return false;
        //If capturing can't move two spaces
        } else if (abs(row_diff) > 2) {
            return false;
        }
    }
    //Handles white pawns on bottom of board
    if (isWhite && (row_diff == 1 || (row_diff == 2 && row == 2))) {
        status = row_diff == 2 ? !(board -> isOccupied(row + 1, col)): true;
    //Handles black pawns on top of board
    } else if (!isWhite && (row_diff == -1 || (row_diff == -2 && row == 7))) {
        status = row_diff == -2 ? !(board -> isOccupied(row - 1, col)): true;
    }

    return status;
}

