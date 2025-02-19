#include "ConnectFour.h"
#include <iostream>
#include <cmath>
#include <vector>
// play() is DONE FOR YOU - uncomment when ready

void ConnectFour::play() { 
	bool isGoodMove = false;
	this->printInstructions(); // print instructions
	this->printBoard();		   // print the board
	while (
		!this->isWin() &&
		!this->isTie()) { // keep playing as long as the game is not won or tied
		isGoodMove = this->takeTurn(); // current player takes a turn
		if (isGoodMove) {
			this->printBoard(); // print the board if that was a good move
			if (this->isWin())
				break; // if that was a winning move, quit the game
			if (this->isTie())
				break;			// else if the game is tied, quit the game
			this->nextPlayer(); // else, advance to the next player in the game.
		}						// else that was an illegal move
	}							// end while: game over
	if (this->getWinningPlayerId() == -1)
		std::cout << "Sorry - It looks like the game was a tie." << std::endl;
	else
		std::cout << "Congratulation: Player #" << this->getCurrentPlayerToken()
				  << " has won the game!" << std::endl;
	std::cout << "Goodbye!" << std::endl;
} // end play


ConnectFour::ConnectFour( 
    char _emptyToken,  // the token used for an empty space (defaults to dash)
    std::vector<char>_playerTokens,  // the characters that describe the players, defaults to X and O
    std::vector<char> initTokens, // the tokens that initialize the board for a game already in progress
    int _startingPlayerId // the id of the player that goes first to start the game
 ): emptyToken(_emptyToken), playerTokens(_playerTokens), currentPlayerId(_startingPlayerId) {
    int totalTiles = (numCols + 1) * (numRows + 1);
	for (int r = 0; r < numRows; r++) {
		board.push_back({});
	}
	for (int i = 0; i < fmin(initTokens.size(), totalTiles); i++) {
        int row = i / numCols;
        int col = i % numRows;
        board[row].push_back(initTokens[i]);
    }
    for (int i = 0; i < totalTiles; i++) {
        int row = i / numCols;
        board[row].push_back(emptyToken);
    }
 }


void ConnectFour::printInstructions() {return;} // print instructions for the game
void ConnectFour::printBoard() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            std::cout << board[r][c];
        }
        std::cout << '\n';
    }
}
// return the character that represents the current player, based on currentPlayerId
char ConnectFour::getCurrentPlayerToken(){return playerTokens[currentPlayerId];}

// advance to the next player in the game
void ConnectFour::nextPlayer() {currentPlayerId = (currentPlayerId + 1) % 2;} 

// prompt the current human player and process their turn, returning true if it was successful
bool ConnectFour::takeTurn() {
	std::cout << "Please Enter a column number to put a piece into.";
	int col;
	std::cin >> col;
	col -= 1;
	if (col >= 0 && col < 7) {
		return placeTileInCol(col);
	}
	return false;
}  

bool ConnectFour::placeTileInCol(int col) {
	for (int row = numRows - 1; row >= 0; row--) {
		if (board[row][col] == emptyToken) {
			board[row][col] = playerTokens[currentPlayerId];
			return true;
		}
	}
	return false;
}

 // determine if the CURRENT PLAYER has won the game and update winningPlayerId to the winning player's Id
bool ConnectFour::isWin() {
	char token = playerTokens[currentPlayerId];
	if (checkForWinCols(token) || checkForWinRows(token) || checkForWinDiagonal(token)) {
		winningPlayerId = currentPlayerId;
		return true;
	}
	return false;
}

bool ConnectFour::checkForWinCols(char token) {
	int currentCount = 0;
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			if (checkForToken(r, c, token, currentCount)) {
				return true;
			}
		}
		currentCount = 0;
	}
	return false;
}

bool ConnectFour::checkForWinRows(char token) {
	int currentCount = 0;
	for (int c = 0; c < numCols; c++) {
		for (int r = 0; r < numRows; r++) {
			if (checkForToken(r, c, token, currentCount)) {
				return true;
			}
		}
		currentCount = 0;
	}
	return false;
}

bool ConnectFour::checkForWinDiagonal(char token) {
	for (int c = 0; c < numCols; c++) {
		if (checkForWinDiagonalLD(token, c) || checkForWinDiagonalRD(token, c)) {
			return true;
		}
	}
	return false;
}

bool ConnectFour::checkForWinDiagonalLD(char token, int c) {
	int currentCount = 0;
	for (int r = 0; r < numRows; r++) {
		if (checkForToken(r, c, token, currentCount)) {
			return true;
		}
		c -= 1;
		if (c < 0) {
			break;
		}
	}
	return false;
}

bool ConnectFour::checkForWinDiagonalRD(char token, int c) {
	int currentCount = 0;
	char token = playerTokens[currentPlayerId];
	for (int r = 0; r < numRows; r++) {
		if (checkForToken(r, c, token, currentCount)) {
			return true;
		}	
		c += 1;
		if (c >= numCols) {
			break;
		}
	}
	return false;
}

bool ConnectFour::checkForToken(int r, int c, char token, int &currentCount) {
	if (board[r][c] == token) {
		currentCount += 1;
		if (currentCount == 4) {
			return true;
		}
	} else {
		currentCount = 0;
	}
	return false;
}
// return the value of the private winningPlayerId, as set by isWin().
int ConnectFour::getWinningPlayerId(){return winningPlayerId;}
bool ConnectFour::isTie(){return false;} // determine if the game cannot be won by either player regardless of the number of moves