#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

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

    bool bishop_capabilities = abs(row - _row) != abs(col - _col);

    //Check if acting as rook or bishop
    if (!rook_capabilities && !bishop_capabilities) {
        return false;
    }

    //Check if space is clear
    return board -> isClear(row, col, _row, _col);
}