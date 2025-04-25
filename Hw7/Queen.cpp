#include "Queen.h"

Queen::Queen(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Queen";
}
Queen::~Queen() {
    std::cout<<"Destructing Queen Class" << std::endl;
}

bool Queen::isLegalMoveTo(int _row, int _col) {
    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    bool rook_capabilities = (col == _col || row == _row);
    
    int row_diff = _row - row;
    int col_diff = _col - col;

    bool bishop_capabilities = (abs(row_diff) == abs(col_diff));

    bool status = rook_capabilities || bishop_capabilities;

    //Checking for pieces in the way as bishop
    if (bishop_capabilities) {
        int row_dir = row_diff > 0 ? 1: -1;
        int col_dir = col_diff > 0 ? 1: -1;
        for (int i = 1; i < abs(col_diff); i++) {
            if (board -> isOccupied(row + (i * row_dir), col + (i * col_dir))) {
                return false;
            }
        }
    }
    //Checking for piecies in the way as rook
    if (rook_capabilities) {
        int row_dir = 0, col_dir = 0;

        if (row_diff != 0) {
            row_dir = row_diff > 0 ? 1: -1;
        } else {
            col_dir = col_diff > 0 ? 1: -1;
        }
    
        for (int i = 1; i < abs(std::max(row_diff, col_diff)); i++) {
            if (board -> isOccupied(row + (i * row_dir), col + (i * col_dir))) {
                return false;
            }
        }
    }

    return status;
}