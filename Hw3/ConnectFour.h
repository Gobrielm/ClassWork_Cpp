/*

  DONE : this header file has been fully written for you

*/
#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <vector>
#include "weightedColumn.h"

class ConnectFour{ // DONE FOR YOU - PLEASE DO NOT CHANGE THIS FILE

  private:
    const int numRows = 6;         // for convenience... our board is always 6 rows x 7 columns in connect four
    const int numCols = 7;        
    int winningPlayerId = -1; // will be set to a valid player ordinal id (0, 1, 2, ...) if/when someone wins the game
    std::vector< std::vector <char> > board;     // current tokens on the board; constructor must init numRow, numCols
    char emptyToken;     // a representation of the empty token
    std::vector<char> playerTokens; // these are the tokens for each player in the game (player 0 has the 1st token, etc.)
    int currentPlayerId;  // this is the id of the current player, always between 0 and playerTokens.size()-1 (inclusive) 
                         // it should be set to the "starting player" id by the constructor to start the game

    // NOTE: the current player token can always be found by playerTokens[ currentPlayerId ]
    // Note also that the currentPlayerId must always be from 0 to playerTokens.size()-1 (inclusive) to avoid illegal access in playerTokens[] 
    // ...So a safer way to determine the current player might be: playerTokens[ currentPlayerId%playerTokens.size() ]
    
    bool playingWithAi;
    
    int getPlayerIDFromToken(char token);
    void promptUserForAI();
    bool isWin(int playerID);
    bool placeTileInCol(int col);
    bool placeTileInCol(int col, int playerID);
    void removeTileInCol(int col);
    bool checkForWinRows(char token);
    bool checkForWinCols(char token);
    bool checkForWinDiagonal(char token);
    bool checkForWinDiagonalLD(char token, int c);
    bool checkForWinDiagonalRD(char token, int c);
    bool checkForToken(int r, int c, char token, int &currentCount);
    bool isRowTie();
    bool isColTie();
    bool isDiagonalTie();
    bool isDiagonalTieRD(int c);
    bool isDiagonalTieLD(int c);
    bool tieTracker(char &curr, int r, int c, int &tracker);
    void takeTurnAI();
    std::array<int, 7> getColumnWeights();
    int getColumnWeight(int c);
    int getSpaceWeight(int r, int c);
    bool trackTokens(int r, int c, char &tracked, int &emptyTokens, int &aiTokens, int &enemyTokens);
    void resetCounts(char &tracked, int &aiTokens, int &enemyTokens, int &emptyTokens);
    int calculateWeight(int emptyTokens, int enemyTokens, int aiTokens);
    weightedColumn miniMax(int isMaximising, int depth);
    int evalutateBoard();

  public:
    ConnectFour(                   // constructor ARGUMENTS are listed below
          char _emptyToken = '-',  // the token used for an empty space (defaults to dash)
          std::vector<char>_playerTokens = {'X', 'O'},  // the characters that describe the players, defaults to X and O
          std::vector<char> initTokens = {}, // the tokens that initialize the board for a game already in progress
          int _startingPlayerId = 0 // the id of the player that goes first to start the game
       );

    void printInstructions(); // print instructions for the game
    void printBoard(); // print the board in its current state
    char getCurrentPlayerToken(); // return the character that represents the current player, based on currentPlayerId
    void nextPlayer(); // advance to the next player in the game
    bool takeTurn();  // prompt the current human player and process their turn, returning true if it was successful
    bool isWin(); // determine if the CURRENT PLAYER has won the game and update winningPlayerId to the winning player's Id
    int getWinningPlayerId(); // return the value of the private winningPlayerId, as set by isWin().
    bool isTie(); // determine if the game cannot be won by either player regardless of the number of moves
    void play(); // play the game, in Pincluding all turn-taking and intput / output

    // bool takeAITurn(); // BONUS: computer AI takes a turn, alternating with takeTurn() above

};

#endif