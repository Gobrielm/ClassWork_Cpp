#include "Puzzle.h"

#include <fstream>
#include <vector>

// constructor: using the filename, load the puzzle pieces into the dynamic pieces array
Puzzle::Puzzle(std::string fileName) {
    std::ifstream fileIn(fileName);
    int numberOfLines;
    fileIn >> numberOfLines;
    pieces = new Token*[numberOfLines + 1];

    int futureCharacter;
    int row;
    int col;
    
    int current = 0;
    while (fileIn >> futureCharacter, fileIn >> row, fileIn >> col) {
        pieces[current] = new Token(futureCharacter, row, col);
        rowCount = std::max((row + 1), rowCount);
        colCount = std::max((col + 1), colCount);
        current ++;
    }
}

// print the list of randomized puzzle pieces
void Puzzle::printPieces() {
    int curr = 0;
    while (pieces[curr] != nullptr) {
        pieces[curr]->printMe();
        curr++;
    }
}

// allocate the grid and copy pieces pointers to their correct location int the grid;
void Puzzle::loadGrid() {
    grid = new Token**[rowCount]();
    int num = 0;
    
    while (pieces[num] != nullptr){
        Token* temp = pieces[num];

        if (grid[temp -> row] == nullptr) {
            grid[temp -> row] = new Token*[colCount]();
        }
        grid[temp -> row][temp -> col] = new Token(temp -> letter, temp -> row, temp -> col);
        num++;
    }
    
}

// destructor - when we delete the Puzzle instance, the destructor should clean up all "new" allocations for pieces and grid
Puzzle::~Puzzle() {
    delete[] pieces;

    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            delete grid[r][c];
        }
        delete[] grid[r];
    }
    delete[] grid;
}

// print the entire puzzle, using the grid data member 
void Puzzle::printGrid() {
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            Token* temp = grid[r][c];
            if (temp != nullptr) {
                std::cout<< temp -> letter;
            }
        }
        std::cout << '\n';
    }
}