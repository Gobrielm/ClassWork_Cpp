#include "Rook.h"

Rook::Rook(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Rook";
}
Rook::~Rook() {
    std::cout<<"Destructing Rook Class" << std::endl;
}

bool Rook::isLegalMoveTo(int _row, int _col) {
    if (!Piece::isOnBoard(_row, _col)) {
        return false;
    }

    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    bool status = (col == _col || row == _row) && !(col == _col && row == _row);

    //Checks for captures
    if (status && temp && temp -> isWhite != isWhite) {
        temp -> isCaptured = true;
    }
    
    return status;
}