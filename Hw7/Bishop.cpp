#include "Bishop.h"

Bishop::Bishop(int _row, int _col, bool _isWhite, string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
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

    int row_diff = _row - row;
    int col_diff = _col - col;
    //If not moving in diagonal line then return false
    if (abs(row_diff) != abs(col_diff)) {
        return false;
    }

    //Checking for piecies in the way
    int row_dir = row_diff > 0 ? 1: -1;
    int col_dir = col_diff > 0 ? 1: -1;
    for (int i = 1; i < abs(col_diff); i++) {
        if (board -> isOccupied(row + (i * row_dir), col + (i * col_dir))) {
            return false;
        }
    }

    return true;
}