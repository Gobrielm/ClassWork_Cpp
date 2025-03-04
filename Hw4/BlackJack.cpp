#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "BlackJack.h"


//
// PLAY (DONE for you)
//
// DONE: the method below has been written for you to help you understand how your methods will be used
// uncomment when you are ready to test the game
// the method below has been written for you to help you understand how your methods will be used

  void BlackJack :: play() {
    std::cout << "Let's Play BlackJack!" << std::endl;

    bool gameOver = false; // Bust means >21
    this->printInstructions(); // print instructions
    this->printBoard("\n** printBoard() Before the game:\n------------------------------------"); // print the board
    gameOver = this->takePlayerTurn(); // current player takes a turn
    this->printBoard("\n** printBoard() After Player's Turn:\n------------------------------------"); // print the board
    if (!gameOver) this->takeDealerTurn(); // AI takes a turn

    this->printBoard("\n** printBoard() After Dealer's Turn:\n------------------------------------"); // print the board 
    
    // note below that the winning player is who we want, not the current player
    if (getWinningPlayerId() != -1){
      std::cout << "Congratulations: " << playerNames[getWinningPlayerId()] << " has won the game!" << std::endl;
    }
    else{ 
      std::cout << "Looks like the game was a tie" << std::endl;

    std::cout << "Goodbye!" << std::endl;
    }
  } // end play()



BlackJack::BlackJack(std::vector<std::string> _playerNames, std::vector<int> cardIDs) {
  playerNames = _playerNames;
  for (int x: cardIDs) {
    deck.addACard(Card(x));
  }
}

// print instructions for the game
void BlackJack::printInstructions() {
  std::cout << "TODO";
}

 // print a message and the state of the game: player hand (all cards up), and dealer hand (all cards up)
void BlackJack::printBoard(std::string message) {
  std::cout << message << '\n';
  std::cout << "Dealer's hand: ";
  playerHand.printMe();
  std::cout << "Player's hand: ";
  dealerHand.printMe();
}

// Player takes their turn, setting winningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack::takePlayerTurn() {
  char action;
  std::cin >> action;
  if (action == 'h') {
    Card drawnCard = deck.dealACard();
    playerHand.addACard(drawnCard);
    
    int playerPts = getPlayerPoints();
    if (playerPts > 21) {
      winningPlayerId = 1;
      return true;
    } else if (playerPts == 21) {
      return true;
    }
    updateWinningState();
  }
  return false;
}

bool BlackJack::updateWinningState() {
  int dealerPts = getDealerPoints();
  int playerPts = getPlayerPoints();
  if (playerPts > dealerPts) {
    winningPlayerId = 0;
  } else if (playerPts < dealerPts) {
    winningPlayerId = 1;
  } else {
    winningPlayerId = -1;
  }

  return false;
}

// Dealer takes a turn, setting winnningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack::takeDealerTurn() {
  int dealerPts = getDealerPoints();
  if (dealerPts < 17) {
    Card drawnCard = deck.dealACard();
    playerHand.addACard(drawnCard);
    
    int dealerPts = getDealerPoints();
    if (dealerPts > 21) {
      winningPlayerId = 0;
      return true;
    } else if (dealerPts == 21) {
      return true;
    }
    updateWinningState();
  }
  return false;
}

// return the value of the private winningPlayerId, as set by isWin().
int BlackJack::getWinningPlayerId() {
  return winningPlayerId;
}

// return the points for the player's hand by calling Hand::playerHand->getPoints()
int BlackJack::getPlayerPoints() {
  return playerHand.getPoints();
}

// return the points for the dealer's hand by calling Hand::dealerHand->getPoints()
int BlackJack::getDealerPoints() {
  return dealerHand.getPoints();
}
