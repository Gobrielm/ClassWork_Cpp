#include "ConnectFour.h"
#include <iostream>

// play() is DONE FOR YOU - uncomment when ready

// void ConnectFour ::play() { 
// 	bool isGoodMove = false;
// 	this->printInstructions(); // print instructions
// 	this->printBoard();		   // print the board
// 	while (
// 		!this->isWin() &&
// 		!this->isTie()) { // keep playing as long as the game is not won or tied
// 		isGoodMove = this->takeTurn(); // current player takes a turn
// 		if (isGoodMove) {
// 			this->printBoard(); // print the board if that was a good move
// 			if (this->isWin())
// 				break; // if that was a winning move, quit the game
// 			if (this->isTie())
// 				break;			// else if the game is tied, quit the game
// 			this->nextPlayer(); // else, advance to the next player in the game.
// 		}						// else that was an illegal move
// 	}							// end while: game over
// 	if (this->getWinningPlayerId() == -1)
// 		std::cout << "Sorry - It looks like the game was a tie." << std::endl;
// 	else
// 		std::cout << "Congratulation: Player #" << this->getCurrentPlayerToken()
// 				  << " has won the game!" << std::endl;
// 	std::cout << "Goodbye!" << std::endl;
// } // end play


// TODO: the rest of your implementations go below here