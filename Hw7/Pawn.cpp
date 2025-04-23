#include "Pawn.h"

Pawn::Pawn(int _row, int _col, bool _isWhite, std::string _name): Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Pawn";
}

Pawn::~Pawn(){
    std::cout<<"Destructing Pawn Class" << std::endl;
}

bool Pawn::isLegalMoveTo(int _row, int _col) {
    if (!Piece::isOnBoard(_row, _col)) {
        return false;
    }

    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    bool status = false;
    
    int row_diff = _row - row;
    if (col == _col) {
        //White on bottom
        if (isWhite && (row_diff == 1 || (row_diff == 2 && row == 2))) {
            if (row_diff == 2) {
                status = board -> isOccupied(_row - 1, _col);
            } else {
                status = true;
            }
        } else if (!isWhite && (row_diff == -1 || (row_diff == -2 && row == 6))) {
            if (row_diff == -2) {
                status = board -> isOccupied(_row + 1, _col);
            } else {
                status = true;
            }
        }
    }

    //Checks for captures
    if (status && temp && temp -> isWhite != isWhite) {
        temp -> isCaptured = true;
    }
    
    return status;
}

