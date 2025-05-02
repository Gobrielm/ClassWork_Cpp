#include "Rook.h"

Rook::Rook(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Rook";
}
Rook::~Rook() {
    std::cout<<"Destructing Rook Class" << std::endl;
}

bool Rook::isLegalMoveTo(int _row, int _col) {
    //Checking if moving in straight line
    if (row != _row && col != _col) {
        return false;
    }

    //Check for pieces in the way
    return board -> isClear(row, col, _row, _col);
}