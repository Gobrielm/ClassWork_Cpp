#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "BlackJack.h"

  void BlackJack :: play() {
    std::cout << "Let's Play BlackJack!" << std::endl;

    bool gameOver = false; // Bust means >21
    this->printInstructions(); // print instructions
    this->printBoard(""); // print the board
    gameOver = this->takePlayerTurn(); // current player takes a turn
    this->printBoard(""); // print the board
    if (!gameOver) this->takeDealerTurn(); // AI takes a turn

    this->printBoard(""); // print the board 
    
    // note below that the winning player is who we want, not the current player
    if (getWinningPlayerId() != -1){
      std::cout << "Congratulations: " << playerNames[getWinningPlayerId()] << " has won the game!" << std::endl;
    }
    else{ 
      std::cout << "Looks like the game was a tie" << std::endl;

    std::cout << "Goodbye!" << std::endl;
    }
  } // end play()


//Constructs playerNames and deck
BlackJack::BlackJack(std::vector<std::string> _playerNames, std::vector<int> cardIDs) : playerNames(_playerNames), deck(cardIDs) {}

// print instructions for the game
void BlackJack::printInstructions() {
  std::cout << "Your goal is to score above the deal but not exceed 21. You may either Hit(h) or Stand(s). \nHitting will give you a new card with value between 1-10. Face cards are always equal to 10 and Ace's are 1";
}

 // print a message and the state of the game: player hand (all cards up), and dealer hand (all cards up)
void BlackJack::printBoard(std::string message) {
  std::cout << message << '\n';
  std::cout << "Player's hand: ";
  playerHand.printMe();
  std::cout << std::to_string(getPlayerPoints()) << " Points\n";
  std::cout << "Dealer's hand: ";
  dealerHand.printMe();
  std::cout << std::to_string(getDealerPoints()) << " Points\n";
}

// Player takes their turn, setting winningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack::takePlayerTurn() {
  std::cout << "Player's Turn: Hit(h) or Stand(s)? ";
  char action;
  std::cin >> action;
  
  //Chosen to hit
  while (action == 'h') {
    Card drawnCard = deck.dealACard();
    playerHand.addACard(drawnCard);
    
    int playerPts = getPlayerPoints();

    if (playerPts == 21) {
      //Player wins as they have an Ace and a Face card for 21
      if (playerHand.hasAnAce() && playerHand.size() == 2) {
        winningPlayerId = 0;
        return true;
      }
      winningPlayerId = -1;
      return false;
    //Player busts
    } else if (playerPts > 21) {
      winningPlayerId = 1;
      return true;
    //Game is still undetermined
    } else {
      winningPlayerId = -1;
    }
    printBoard("Player hits...\n");
    std::cout << "Player's Turn: Hit(h) or Stand(s)? ";
    std::cin >> action;
  }
  //Chosen to stay
  printBoard("Player stands...\n");
  return false;
}

// Dealer takes a turn, setting winnningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack::takeDealerTurn() {
  std::cout << "Dealer's Turn...\n";
  int dealerPts = getDealerPoints();

  while (dealerPts < 17) {
    Card drawnCard = deck.dealACard();
    dealerHand.addACard(drawnCard);
    
    dealerPts = getDealerPoints();
    //Dealer wins
    if (dealerPts == 21) {
      winningPlayerId = 1;
      return true;
    //Dealer busts
    } else if (dealerPts > 21) {
      winningPlayerId = 0;
      return true;
    }
    printBoard("Dealer hits...\n");
  }
  printBoard("Dealer stays...\n");
  //Decides who is higher in score
  if (dealerPts < getPlayerPoints()) {
    winningPlayerId = 0;
  } else {
    winningPlayerId = 1;
  }
  return true;
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
