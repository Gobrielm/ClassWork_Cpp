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
		std::vector<char> a;
		board.push_back(a);
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


void ConnectFour::printInstructions() {}; // print instructions for the game
void ConnectFour::printBoard() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            std::cout << board[r][c];
        }
        std::cout << '\n';
    }
}
char ConnectFour::getCurrentPlayerToken(){return playerTokens[currentPlayerId];}; // return the character that represents the current player, based on currentPlayerId
void ConnectFour::nextPlayer(){currentPlayerId = (currentPlayerId + 1) % 2}; // advance to the next player in the game

bool ConnectFour::takeTurn(){return false;};  // prompt the current human player and process their turn, returning true if it was successful
bool ConnectFour::isWin(){return false;}; // determine if the CURRENT PLAYER has won the game and update winningPlayerId to the winning player's Id
int ConnectFour::getWinningPlayerId(){return 1;}; // return the value of the private winningPlayerId, as set by isWin().
bool ConnectFour::isTie(){return false;}; // determine if the game cannot be won by either player regardless of the number of moves