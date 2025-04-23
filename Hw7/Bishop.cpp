#include "Bishop.h"

Bishop::Bishop(int _row, int _col, bool _isWhite, string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Bishop";
}
Bishop::~Bishop() {
    std::cout<<"Destructing Bishop Class" << std::endl;
}
bool Bishop::isLegalMoveTo(int _row, int _col) {
    if (!Piece::isOnBoard(_row, _col)) {
        return false;
    }
    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    int row_diff = _row - row;
    int col_diff = _col - col;
    bool status = row_diff == col_diff && row_diff != 0;

    //Checks for captures
    if (status && temp && temp -> isWhite != isWhite) {
        temp -> isCaptured = true;
    }

    return status;
}