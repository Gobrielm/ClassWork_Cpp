#include "Knight.h"

Knight::Knight(int _row, int _col, bool _isWhite, std::string _name) : Piece::Piece(_row, _col, _isWhite, _name) {
    Piece::ptype = "Knight";
}
Knight::~Knight() {
    std::cout<<"Destructing Knight Class" << std::endl;
}
bool Knight::isLegalMoveTo(int _row, int _col) {
    int row_diff = abs(row - _row);
    int col_diff = abs(col - _col);
    bool status = (row_diff == 1 && col_diff == 2) || (row_diff == 2 && col_diff == 1);

    return status;
}