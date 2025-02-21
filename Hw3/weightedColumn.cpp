#include "weightedColumn.h"
#include <iostream>

weightedColumn::weightedColumn(int _weight, int _col) {
    weight = _weight;
    col = _col;
}

int weightedColumn::getWeight() {return weight;}
int weightedColumn::getColumn() {return col;}
void weightedColumn::changeWeight(int amount){weight += amount;}
weightedColumn weightedColumn::operator+(weightedColumn other) {return weightedColumn(weight + other.weight, col);}