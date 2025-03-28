#include "Puzzle.h"

#include <fstream>

// constructor: using the filename, load the puzzle pieces into the dynamic pieces array
Puzzle::Puzzle(std::string fileName) {
    std::ifstream fileIn(fileName);

    //Info to be collected from each line
    int futureCharacter;
    int id;
    int top;
    int right;
    int bot;
    int left;
    
    colCount = 0;
    rowCount = 0;
    
    while (fileIn >> futureCharacter >> id >> top >> right >> bot >> left) {
        //Instances new Token and stores it in map
        id_to_token[id] = new Token(futureCharacter, id, top, right, bot, left);
        
        //Finds the top left token
        if (left == 0 && top == 0) {
            upper_left = id_to_token[id];
        }
        if (left == 0) {
            rowCount++;
        }
        if (top == 0) {
            colCount++;
        }
    }
    pieceCount = id_to_token.size();
    //Create pieces from map
    pieces = new Token*[pieceCount];
    int current = 0;
    for (const auto& pair: id_to_token) {
        pieces[current] = pair.second;
        current ++;
    }
}

// print the list of randomized puzzle pieces
void Puzzle::printPieces() {
    int curr = 0;
    while (curr < pieceCount) {
        pieces[curr]->printMe();
        curr++;
    }
}

// allocate the grid and copy pieces pointers to their correct location int the grid;
void Puzzle::loadGrid() {
    //Unsafe but every slot is filled
    grid = new Token**[rowCount];
    Token* row_ptr = upper_left;
    Token* current = upper_left;
    int row = 0;
    int col = 0;
    while(true) {
        while(true) {
            //If new row then instance new row
            if (col == 0) {
                grid[row] = new Token*[colCount];
            }
            grid[row][col] = current;
            
            //If reached the end of the row then break
            if (current -> right == 0) {
                break;
            }
            //Increment pointer and column
            current = id_to_token[(current -> right)];
            col++;
        }
        //Checks to see if at the bottom
        if (row_ptr -> bottom == 0) {
            break;
        }
        //Increments and sets curr to the next row
        row++;
        col = 0;
        row_ptr = id_to_token[row_ptr -> bottom];
        current = row_ptr;
    }
}

// destructor - when we delete the Puzzle instance, the destructor should clean up all "new" allocations for pieces and grid
Puzzle::~Puzzle() {
    
    for (auto& pair: id_to_token) {
        //Deletes the actual Token Here
        delete pair.second;
    }
    id_to_token.clear();
    //Deletes dynamically allocated space
    delete[] pieces;
    for (int r = 0; r < rowCount; r++) {
        delete[] grid[r];
    }
    delete[] grid;
}

// print the entire puzzle, using the grid data member 
void Puzzle::printGrid() {
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            Token* temp = grid[r][c];
            std::cout<< temp -> letter;
        }
        std::cout << '\n';
    }
}