#include "Pawn.h"

Pawn::Pawn(int _row, int _col, bool _isWhite, std::string _name): Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Pawn";
}

Pawn::~Pawn(){
    std::cout<<"Destructing Pawn Class" << std::endl;
}

bool Pawn::isLegalMoveTo(int _row, int _col) {

    Piece* temp = board -> pieceAt(_row, _col);
    
    int row_diff = _row - row;
    int col_diff = _col - col;

    //Check for moving 2 spaces
    if (row_diff == 2) {
        if (row == 2 && isWhite && !board -> isOccupied(row + 1, col) && !temp && col_diff == 0) {
            return true;
        } else {
            return false;
        }
    } else if (row_diff == -2) {
        if (row == 7 && !isWhite && !board -> isOccupied(row - 1, col) && !temp && col_diff == 0) {
            return true;
        } else {
            return false;
        }
    }

    //Can only move 1 space
    if (row_diff == 1 && isWhite) {
        if (col_diff == 0 && !temp) {
            return true;
        } else if (abs(col_diff) == 1 && temp) {
            return true;
        } else {
            return false;
        }
    //Can only move 1 space
    } else if (row_diff == -1 && !isWhite) {
        if (col_diff == 0 && !temp) {
            return true;
        } else if (abs(col_diff) == 1 && temp) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

