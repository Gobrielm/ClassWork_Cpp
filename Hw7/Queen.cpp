#include "Queen.h"

Queen::Queen(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Queen";
}
Queen::~Queen() {
    std::cout<<"Destructing Queen Class" << std::endl;
}

bool Queen::isLegalMoveTo(int _row, int _col) {
    if (!Piece::isOnBoard(_row, _col)) {
        return false;
    }

    Piece* temp = board -> pieceAt(_row, _col);
    //Checks if tile is taken by same color
    if (temp && temp -> isWhite == isWhite) {
        return false;
    }

    bool rook_capabilities = ((col == _col || row == _row) && !(col == _col && row == _row));
    
    int row_diff = _row - row;
    int col_diff = _col - col;

    bool bishop_capabilities = (row_diff == col_diff && row_diff != 0);

    bool status = rook_capabilities || bishop_capabilities;

    //Checks for captures
    if (status && temp && temp -> isWhite != isWhite) {
        temp -> isCaptured = true;
    }

    return status;
}