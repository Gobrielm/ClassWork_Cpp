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
    int col_diff = _col - col;

    bool could_capture = false;

    //Checks for captures
    if (temp && temp -> isWhite != isWhite && abs(col_diff) == 1) {
        could_capture = true;
    } else if (col_diff != 0) {
        //Can't move diagonal if not capturing
        return false;
    }
    

    if (isWhite && (row_diff == 1 || (row_diff == 2 && row == 2))) {
        if (row_diff == 2) {
            status = !board -> isOccupied(row + 1, col);
        } else {
            status = true;
        }
    } else if (!isWhite && (row_diff == -1 || (row_diff == -2 && row == 7))) {
        if (row_diff == -2) {
            status = !board -> isOccupied(row - 1, col);
        } else {
            status = true;
        }
    }
    
    if (could_capture) {
        temp -> isCaptured = true;
    }
    return status;
}

