#include "Bishop.h"

Bishop::Bishop(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Bishop";
}
Bishop::~Bishop() {
    std::cout<<"Destructing Bishop Class" << std::endl;
}
bool Bishop::isLegalMoveTo(int _row, int _col) {
    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    //If not moving in diagonal line then return false
    if (abs(row - _row) != abs(col - _col)) {
        return false;
    }

    //Checking for piecies in the way
    return board -> isClear(row, col, _row, _col);
}