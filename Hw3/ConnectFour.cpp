#include "ConnectFour.h"
#include "weightedColumn.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
// play() is DONE FOR YOU - uncomment when ready

void ConnectFour::play() { 
	bool isGoodMove = false;
	this->printInstructions(); // print instructions
	this->printBoard();		   // print the board
	while (
		!this->isWin() &&
		!this->isTie()) { // keep playing as long as the game is not won or tied
		if (playingWithAi && currentPlayerId == 1) {
			this -> takeTurnAI();
		} else {
			isGoodMove = this->takeTurn(); // current player takes a turn
		}
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
    for (int i = initTokens.size(); i < totalTiles; i++) {
        int row = i / numCols;
        board[row].push_back(emptyToken);
    }
 }


void ConnectFour::printInstructions() {
	std::cout << "Try to get 4 of your token in a line in any orientation to win.\nEnter a column number such as \"2\" to drop a token into column 2.\n";
	promptUserForAI();
}

void ConnectFour::promptUserForAI() {
	char answer;
	std::cout << "Do you want to play against an AI y/n: ";
	std::cin >> answer;
	std:: cout << '\n';
	playingWithAi = (answer == 'y');
	if (playingWithAi && playerTokens.size() != 2) {
		quick_exit(1);
	}
}

int ConnectFour::getPlayerIDFromToken(char token) {
	for (int i = 0; i < playerTokens.size(); i++) {
		if (playerTokens[i] == token) {
			return i;
		}
	}
	return -1;
}

void ConnectFour::printBoard() {
    for (int r = -1; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
			if (r == -1) {
				std::cout << std::to_string(c + 1);
			} else {
				std::cout << board[r][c];
			}
        }
        std::cout << '\n';
    }
}
// return the character that represents the current player, based on currentPlayerId
char ConnectFour::getCurrentPlayerToken(){return playerTokens[currentPlayerId];}

// advance to the next player in the game
void ConnectFour::nextPlayer() {currentPlayerId = (currentPlayerId + 1) % playerTokens.size();} 

// prompt the current human player and process their turn, returning true if it was successful
bool ConnectFour::takeTurn() {
	std::cout << playerTokens[currentPlayerId] << "'s turn: ";
	int col;
	std::cin >> col;
	col -= 1;
	if (col >= 0 && col < 7) {
		return placeTileInCol(col);
	}
	return false;
}  

//Puts a tile in the lowest row of col and returns t/f based on completion
bool ConnectFour::placeTileInCol(int col) {
	for (int row = numRows - 1; row >= 0; row--) {
		if (board[row][col] == emptyToken) {
			board[row][col] = getCurrentPlayerToken();
			return true;
		}
	}
	return false;
}

//Puts a tile in the lowest row of col and returns t/f based on completion
bool ConnectFour::placeTileInCol(int col, int playerID) {
	for (int row = numRows - 1; row >= 0; row--) {
		if (board[row][col] == emptyToken) {
			board[row][col] = playerTokens[playerID];
			return true;
		}
	}
	return false;
}

//Takes tile away from row
void ConnectFour::removeTileInCol(int col) {
	for (int row = 0; row < numRows; row++) {
		if (board[row][col] != emptyToken) {
			board[row][col] = emptyToken;
			return;
		}
	}
	throw __EXCEPTION__;
}

 // determine if the CURRENT PLAYER has won the game and update winningPlayerId to the winning player's Id
bool ConnectFour::isWin() {
	char token = getCurrentPlayerToken();
	if (checkForWinRows(token) || checkForWinCols(token) || checkForWinDiagonal(token)) {
		winningPlayerId = currentPlayerId;
		return true;
	}
	return false;
}

bool ConnectFour::isWin(int playerID) {
	char token = playerTokens[playerID];
	if (checkForWinRows(token) || checkForWinCols(token) || checkForWinDiagonal(token)) {
		return true;
	}
	return false;
}


//Checks rows for wins
bool ConnectFour::checkForWinRows(char token) {
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

//Checks cols for wins
bool ConnectFour::checkForWinCols(char token) {
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

//Checks diagonals for wins
bool ConnectFour::checkForWinDiagonal(char token) {
	for (int c = 0; c < numCols; c++) {
		if (checkForWinDiagonalLD(token, c) || checkForWinDiagonalRD(token, c)) {
			return true;
		}
	}
	return false;
}
//Checks the left-down diagonals
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
//Checks the Right-Down diagonals
bool ConnectFour::checkForWinDiagonalRD(char token, int c) {
	int currentCount = 0;
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
//Checks for the chosen token and updates count and returns true if there is 4 in a direction
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
int ConnectFour::getWinningPlayerId() {return winningPlayerId;}

// determine if the game cannot be won by either player regardless of the number of moves
bool ConnectFour::isTie() {
	return isRowTie() && isColTie() && isDiagonalTie();
}

//Checks rows for ties
bool ConnectFour::isRowTie() {
	int tracker = 0;
	char curr = ' ';
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			if (!tieTracker(curr, r, c, tracker)) {
				return false;
			}
		}
		tracker = 0;
		curr = ' ';
	}
	return true;
}

//Checks cols for ties
bool ConnectFour::isColTie() {
	int tracker = 0;
	char curr = ' ';
	for (int c = 0; c < numCols; c++) {
		for (int r = 0; r < numRows; r++) {
			if (!tieTracker(curr, r, c, tracker)) {
				return false;
			}
		}
		tracker = 0;
		curr = ' ';
	}
	return true;
}

//Checks diagonals for ties
bool ConnectFour::isDiagonalTie() {
	bool currentStatus = true;
	for (int c = 0; c < numCols; c++) {
		currentStatus = currentStatus && isDiagonalTieRD(c) && isDiagonalTieLD(c);
	}
	return currentStatus;
}

//Checks the left-down diagonals
bool ConnectFour::isDiagonalTieLD(int c) {
	int tracker = 0;
	char curr = ' ';
	for (int r = 0; r < numRows; r++) {
		if (!tieTracker(curr, r, c, tracker)) {
			return false;
		}

		c -= 1;
		if (c < 0) {
			break;
		}
	}
	return true;
}

//Checks the right-down diagonals
bool ConnectFour::isDiagonalTieRD(int c) {
	int tracker = 0;
	char curr = ' ';
	for (int r = 0; r < numRows; r++) {
		if (!tieTracker(curr, r, c, tracker)) {
			return false;
		}

		c += 1;
		if (c >= numCols) {
			break;
		}
	}
	return true;
}

//Keeps track of if a player could win
bool ConnectFour::tieTracker(char &curr, int r, int c, int &tracker) {
	//Anyone could place in emptyToken
	if (board[r][c] == emptyToken) {
		tracker += 1;
	//If the token matches current token or is empty then set tracked token
	} else if (curr == board[r][c] || curr == ' ') {
		tracker += 1;
		curr = board[r][c];
	//Found a different token so reset
	} else {
		curr = board[r][c];
		tracker = 1;
	}
	//If 4 in a direction then return no tie
	if (tracker >= 4) {
		return false;
	}
	return true;
}

void ConnectFour::takeTurnAI() {
	// std::array<int, 7> weights = getColumnWeights();
	int col = miniMax(1, 0).getColumn();
	// int max = -999;
	// for (int i = 0; i < numCols; i++) {
	// 	std::cout << std::to_string(i + 1) << " has weight: " << std::to_string(weights[i]) << "\n";
	// 	if (weights[i] > max) {
	// 		max = weights[i];
	// 		col = i;
	// 	}
	// }
	if (col == -1) {
		std::cout<<"AAAAA";
	}
	placeTileInCol(col);
}

std::array<int, 7> ConnectFour::getColumnWeights() {
	std::array<int, 7> toReturn;
	for (int c = 0; c < numCols; c++) {
		toReturn[c] = getColumnWeight(c);
	}
	return toReturn;
}

int ConnectFour::getColumnWeight(int c) {
	for (int r = numRows - 1; r >= 0; r--) {
		if (board[r][c] == emptyToken) {
			return getSpaceWeight(r, c);
		}
	}
	return -99;
}

int ConnectFour::getSpaceWeight(int r, int c) {
	char token = getCurrentPlayerToken();
	int weight = 0;
	int aiTokens = 0;
	int enemyTokens = 0;
	int emptyTokens = 0;
	char tracked = ' ';
	
	//Checking row right
	for (int ct = c + 1; ct < fmin(numCols, c + 4); ct++) {
		if (trackTokens(r, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
	}
	tracked = ' ';
	//Checking row left
	for (int ct = c - 1; ct >= fmax(0, c - 4); ct--) {
		if (trackTokens(r, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
	}
	
	weight += calculateWeight(emptyTokens, enemyTokens, aiTokens);
	//Checking column down
	resetCounts(tracked, aiTokens, enemyTokens, emptyTokens);
	for (int rt = r + 1; rt < fmin(numRows, r + 4); rt++) {
		if (trackTokens(rt, c, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
	}
	tracked = ' ';
	//Checking column up
	for (int rt = r - 1; rt >= fmax(0, r - 4); rt--) {
		if (trackTokens(rt, c, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
	}
	weight += calculateWeight(emptyTokens, enemyTokens, aiTokens);
	//Checking diagonals left-up
	resetCounts(tracked, aiTokens, enemyTokens, emptyTokens);
	int ct = c - 1;
	for (int rt = r - 1; rt >= fmax(0, r - 4); rt--) {
		if (trackTokens(rt, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
		ct -= 1;
		if (ct < fmax(0, c - 4)) {
			break;
		}
	}
	tracked = ' ';
	//Checking diagonals right-down
	ct = c + 1;
	for (int rt = r + 1; rt < fmin(numRows, r + 4); rt++) {
		if (trackTokens(rt, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 

		ct += 1;
		if (ct >= fmin(numRows, c + 4)) {
			break;
		}
	}
	weight += calculateWeight(emptyTokens, enemyTokens, aiTokens);
	//Checking diagonals right-up
	resetCounts(tracked, aiTokens, enemyTokens, emptyTokens);
	ct = c + 1;
	for (int rt = r - 1; rt >= fmax(0, r - 4); rt--) {
		if (trackTokens(rt, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 

		ct += 1;
		if (ct >= fmin(numRows, c + 4)) {
			break;
		}
	}
	tracked = ' ';
	//Checking diagonals left-down
	ct = c - 1;
	for (int rt = r + 1; rt < fmin(numRows, r + 4); rt++) {
		if (trackTokens(rt, ct, tracked, emptyTokens, aiTokens, enemyTokens)) {
			break;
		} 
		ct -= 1;
		if (ct < fmax(0, r - 4)) {
			break;
		}
	}
	weight += calculateWeight(emptyTokens, enemyTokens, aiTokens);
	return weight;
}

weightedColumn ConnectFour::miniMax(int isMaximising, int depth) {
	
	if (depth > 6) {
		return weightedColumn(evalutateBoard(), -1);
	}
	weightedColumn currentBest(-1000, -1);
	if (isMaximising == 0) {
		currentBest.changeWeight(2000);
	} 
	for (int col = 0; col < numCols; col++) {
		bool valid = placeTileInCol(col, isMaximising); // 0 for player 1 for comp
		if (!valid) {
			continue;
		}
		if (isWin(isMaximising)) {
			removeTileInCol(col);
			return weightedColumn((isMaximising == 1 ? 1000 : -1000) / (depth + 1), col);
		}
		if (isTie()) {
			removeTileInCol(col);
			return weightedColumn(-10, col);
		}
		weightedColumn futureMove = weightedColumn(miniMax(1 - isMaximising, depth + 1).getWeight(), col);
		if (isMaximising == 1) {
			if (futureMove.getWeight() > currentBest.getWeight()) {
				currentBest = futureMove;
			}
		} else {
			if (futureMove.getWeight() < currentBest.getWeight()) {
				currentBest = futureMove;
			}
		}
		
		removeTileInCol(col);
	}
	return currentBest;
}

int ConnectFour::evalutateBoard() {
	int tracker = 0;
	char current = emptyToken;
	int boardStatus = 0;
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			if (board[row][col] == emptyToken) {
				if (current != emptyToken) {
					boardStatus += (getPlayerIDFromToken(current) == 1 ? 1: -1) * tracker * 20;
				}
				tracker = 0;
				current = emptyToken;
			} else if (board[row][col] == current) {
				tracker += 1;
			}  else if (current == emptyToken) {
				current = board[row][col];
				tracker += 1;
			}
		}
		if (current != emptyToken) {
			boardStatus += (getPlayerIDFromToken(current) == 1 ? 1: -1) * tracker * 20;
		}
		current = emptyToken;
		tracker = 0;
	}
	if (current != emptyToken) {
		boardStatus += (getPlayerIDFromToken(current) == 1 ? 1: -1) * tracker * 20;
	}
	current = emptyToken;
	tracker = 0;
	for (int col = 0; col < numCols; col++) {
		for (int row = 0; row < numRows; row++) {
			if (board[row][col] == emptyToken) {
				if (current != emptyToken) {
					boardStatus += (getPlayerIDFromToken(current) == 1 ? 1: -1) * tracker * 20;
				}
				tracker = 0;
				current = emptyToken;
			} else if (board[row][col] == current) {
				tracker += 1;
			}  else if (current == emptyToken) {
				current = board[row][col];
				tracker += 1;
			}
		}
		if (current != emptyToken) {
			boardStatus += (getPlayerIDFromToken(current) == 1 ? 1: -1) * tracker * 20;
		}
		current = emptyToken;
		tracker = 0;
	}
	return boardStatus;
}

bool ConnectFour::trackTokens(int r, int c, char &tracked, int &emptyTokens, int &aiTokens, int &enemyTokens) {
	char token = getCurrentPlayerToken();
	if (board[r][c] == emptyToken) {
		emptyTokens += 1;
		if (tracked = ' ') {
			tracked = emptyToken;
		}
	} else if (board[r][c] == tracked || tracked == ' ') {
		tracked = board[r][c];
		if (tracked == token) {
			aiTokens += 1;
		} else {
			enemyTokens += 1;
		}
	} else {
		return true;
	}
	return false;
}

void ConnectFour::resetCounts(char &tracked, int &aiTokens, int &enemyTokens, int &emptyTokens) {
	tracked = ' ';
	aiTokens = 0;
	enemyTokens = 0;
	emptyTokens = 0;
}

int ConnectFour::calculateWeight(int emptyTokens, int enemyTokens, int aiTokens) {
	if (enemyTokens >= 3) {
		return 99;
	} else if (aiTokens >= 3) {
		return 99;
	} else if (emptyTokens < 4 && (enemyTokens + aiTokens + emptyTokens) > 2) {
		return enemyTokens + aiTokens;
	} 
	return 0;
}