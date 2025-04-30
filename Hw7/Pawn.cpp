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
    
    int row_diff = _row - row;
    int col_diff = _col - col;

    bool status = false;

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
            status = true;
        } else if (abs(col_diff) == 1 && temp) {
            status = true;
        }
    //Can only move 1 space
    } else if (row_diff == -1 && !isWhite) {
        if (col_diff == 0 && !temp) {
            status = true;
        } else if (abs(col_diff) == 1 && temp) {
            status = true;
        }
    }

    return status;
}

