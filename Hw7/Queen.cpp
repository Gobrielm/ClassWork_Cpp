#include "Queen.h"

Queen::Queen(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name), Rook::Rook(_row, _col, _isWhite, _name), Bishop::Bishop(_row, _col, _isWhite, _name) {
    Piece::ptype = "Queen";
}
Queen::~Queen() {
    std::cout<<"Destructing Queen Class" << std::endl;
}

bool Queen::isLegalMoveTo(int _row, int _col) {
    //Queen acts as Rook or Bishop
    return Rook::isLegalMoveTo(_row, _col) || Bishop::isLegalMoveTo(_row, _col);
}