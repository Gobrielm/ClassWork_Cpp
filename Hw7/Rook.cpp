#include "Rook.h"

Rook::Rook(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Rook";
}
Rook::~Rook() {
    std::cout<<"Destructing Rook Class" << std::endl;
}

bool Rook::isLegalMoveTo(int _row, int _col) {

    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }
    int row_diff = _row - row;
    int col_diff = _col - col;

    bool status = (row_diff == 0 || col_diff == 0);

    //Check for pieces in the way
    if (status) {
        int row_dir = 0;
        int col_dir = 0;
        if (row_diff != 0) {
            row_dir = row_diff > 0 ? 1: -1;
        } else {
            col_dir = col_diff > 0 ? 1: -1;
        }
    
        for (int i = 0; i < abs(std::max(row_diff, col_diff)); i++) {
            if (board -> isOccupied(row + (i * row_dir), col + (i * col_dir))) {
                return false;
            }
        }
    }
    
    return status;
}