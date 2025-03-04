/*

  DONE : this header file has been fully written for you

*/

#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <list>
#include <string>
#include "Card.h"
#include "Hand.h"

class BlackJack{

  private:
    Hand deck;          // source deck of cards 
    Hand dealerHand;    // dealer's "hand" 
    Hand playerHand;    // player's hand
    std::vector<std::string> playerNames; // these are the names for each player in the game: typically "Player" and "Dealer"

    int winningPlayerId; // id # of the player that has won the game, or -1 if the game is not over yet
      // convention is that the dealer is  ID = 1 and the Player is ID = 0;
      // NOTE: the winning player name can always be found by playerNames[ winningPlayerId ]

  public:
    BlackJack(     // constructor
          std::vector<std::string> _playerNames = {"Player", "Dealer"},  // the characters that describe the players, defaults to "Player" and "Dealer"
          std::vector<int> cardIDs = {} // vector of card IDs we want in the  deck; defaults to empty (player and dealer hands will be empty)
       ); // PROTOTYPE!

    void printInstructions(); // print instructions for the game
    void printBoard(std::string message = "*** Black Jack: Print Board \u2660 \u2665 \u2666 \u2663 ***"); // print a message and the state of the game: player hand (all cards up), and dealer hand (all cards up)
    bool takePlayerTurn();  // Player takes their turn, setting winningPlayerId to -1, 0, or 1, and returning true if the game is over
    bool takeDealerTurn(); // Dealer takes a turn, setting winnningPlayerId to -1, 0, or 1, and returning true if the game is over
    int getWinningPlayerId(); // return the value of the private winningPlayerId, as set by isWin().
    int getPlayerPoints(); // return the points for the player's hand by calling Hand::playerHand->getPoints()
    int getDealerPoints(); // return the points for the dealer's hand by calling Hand::dealerHand->getPoints()
    void play(); // play the game, in Pincluding all turn-taking and intput / output
};

#endif