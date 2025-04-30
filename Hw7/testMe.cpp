#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include "Piece.h"

// VERSION 3

void getRandomMove( ChessBoard &g, std::string &piece, int &row, int &col ) {

    int pieceNum = 4; // rand()%6; // pick one of the 6 piece types at random
  
  
    if( pieceNum == 0 ) { // Queen

      if ( g.whiteTurn ){ 
      piece = "quw";
      row = g.pieces[3+16]->row;
      col = g.pieces[3+16]->col;
      }
    else {
      piece = "qub";
      row = g.pieces[3]->row;
      col = g.pieces[3]->col;
    }

      
      int rnum = rand()%4; // one of 4 possible moves
      if ( rnum==0)
        row += rand()%14-7; // vert move
      else if ( rnum==1)
        col +=rand()%14-7; // horz move
      else if ( rnum==2){
        int offset = rand()%14-7;
        row += offset;
        col += offset; // diag move
        }
      else {
        int offset = rand()%14-7;
        row -= offset;
        col += offset; // diag move
      }

    } // end queen
      
    else if (pieceNum == 1 ){ // King
      row += rand()%4-2; 
      col += rand()%4-2;
      
      if ( g.whiteTurn ) 
        piece = "kiw";
      else 
        piece = "kib";
    }

    else if (pieceNum ==  2 ){ // Bishop
      
      int rnum = rand()%2; // one of two possible diags
      if ( rnum==0){
        int offset = rand()%14-7;
        row += offset;
        col += offset; // diag move
        }
      else {
        int offset = rand()%14-7;
        row -= offset;
        col += offset; // diag move
      }

      int pieceNum = rand()%2+1; // bishop 1 or 2
      if ( g.whiteTurn ) 
        piece = "b"+std::to_string(pieceNum) + "w";
      else 
        piece = "b"+std::to_string(pieceNum) + "b";
    }

    else if (pieceNum ==  3){ // Rook
      int rnum = rand()%2;
      if ( rnum==0)
        row += rand()%14-7; // vert move
      else if ( rnum==1)
        col +=rand()%14-7; // horz move

      int pieceNum = rand()%2+1; // rook 1 or 2
      if ( g.whiteTurn ) 
        piece = "r"+std::to_string(pieceNum) + "w";
      else 
        piece = "r"+std::to_string(pieceNum) + "b";
    }

    else if (pieceNum == 4 ){ // Knight

      int pieceNum = rand()%2+1; // knight 1 or 2
      if ( g.whiteTurn ) {
        row = g.pieces[1+16]->row;
        col = g.pieces[1+16]->col;
        piece = "h"+std::to_string(pieceNum) + "w";
        
      }
      else {
        row = g.pieces[1]->row;
        col = g.pieces[1]->col;
        piece = "h"+std::to_string(pieceNum) + "b";
      }

      std::cout << "randomMove() starts at " << piece << ", " << row << ", " << col << std::endl;
      
      int rnum = rand()%4; // 4 possible directions

      int rowdiff = rand()%2+1; // 1 or 2
      int coldiff = 3-rowdiff; // 2 or 1 (compliment)
      
      if ( rnum ==0){
        rowdiff *= -1;
      }
      else if ( rnum==1){
        coldiff *= -1;
      }

      else if (rnum==2) {
        rowdiff *= -1;
        coldiff *= -1;
      }


      row += rowdiff;
      col += coldiff;


      std::cout << "       ends at" << piece << ", " << row << ", " << col << std::endl;
    }

    else if (pieceNum ==  5 ){ // Pawn
      row = rand()%6-3; 
      col=rand()%3-1;

      int pieceNum = rand()%8+1; // pawn 1 through 8
      if ( g.whiteTurn ) 
        piece = "b"+std::to_string(pieceNum) + "w";
      else 
        piece = "b"+std::to_string(pieceNum) + "b";
    }
  

    ///std::cout << "random piece is " << piece << std::endl;
  
}

// convert the current state of the board into a string the exactly describes the board for comparison purposes
std::string getBoardCode( const ChessBoard & g){
    std::string tmp;
    for ( Piece * p : g.pieces){
      // build a uniquely identifiable string for this specific piece
      tmp += std::to_string(p->neverMoved) + std::to_string(p->isCaptured) + std::to_string(p->row) + std::to_string(p->col) + (p->ptype) + std::to_string(p->isWhite) + p->name;
    }
    
    std::for_each(tmp.begin(), tmp.end(), [](char & c){ // drop the case to relax our test in case pcode or piece names are capitalized
      c = ::tolower(c);
    });
  
    return tmp;
} // end getBoardCode()


bool testMe() {

  const char * GREEN = "\n\n\033[;32m";
  const char * RED = "\n\033[1;31m";
  const char * RESET  = "\033[0m";
  std::cout << "testMe(): Starting tests..." << std::endl;

  std::cout << "testMe(): which file would you like to use to test? (ex: testMeIn.txt or just y for default)?";

  std::string testFileName = "testMeIn.txt";
  std::cin >> testFileName;

  if ( testFileName == "y") testFileName = "testMeIn.txt";

  // redirect i/o
  std::ifstream inFile( testFileName );
  // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
  // std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to in.txt!

  std::ofstream outFile( "testMeOut.txt" );
  // std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  // std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

  std::string piece, colChar; // piece name and column name (a-h)
  int row, col; // integer equivalent of moves for row and col
  int totalGames = 0; // number of games we will play
 
  inFile >> totalGames; // read in the number of games we will play

  int goodTests = 0;
  int badTests = 0;

  for(int gameCount=0; gameCount<totalGames; gameCount++ ) {
    std::cout << GREEN << "------------------------------------------- " << RESET << std::endl;
    std::cout << GREEN << "Testing game #" << gameCount << " of " << totalGames << " games: " << RESET << std::endl;
    std::string gameName; // Human readable name of this game
    inFile >> gameName;
    //   cout << "\033[;32mGreen Text\033[0m\n";
    std::cout << "\033[;32m*** " << gameName << "***" << RESET << std::endl;
    
    int totalMoves; // integer number of moves in the current game
    inFile >> totalMoves; // total moves to expect from the file, if count < 0 we are plahing "randomly generated game" specifed by only a srand() input value

    ChessBoard g; // create an instance of the chess board, complete with pieces, ready to play.

    bool doRandomMoves = (totalMoves < 0); // are we playing a randomized game?

    int gameSeed = 0;
    if (doRandomMoves ) {
      inFile >> gameSeed; // read in the specified game seed
      srand(gameSeed);
      totalMoves = abs(totalMoves); // remove negative
      std::cout << "  Starting a random game with " << totalMoves << " random moves..." << std::endl;
    }

    bool wasThisTestOk = true; // init true, set to false  below if we find an error below

    std::string winnerName;
    std::string stalemateString;
    
    for( int currentMove=0; currentMove<totalMoves; currentMove++) { // for each move in this game
      bool successfulMove = false;
      
      if (!doRandomMoves) { // reading game moves from the file
        //inFile >> piece >> row >> colChar; // read in the move (replaced with below)

        std::string line; // a line of input from the file

        while (line.size() == 0)  // eats empty (blank) lines
        if (!std::getline(inFile, line)) { // if we cannot read a line, something is very wrong
          std::cout << RED << "!! Error in input file - could not read entire line of text. Skipping." << RESET << std::endl;
          { char x; std::cout << "Enter any character to skip this input line"; std::cin >> x;}
          continue;
        } // end error
        
        // {  // DEBUG
        //  std::cout << "read line: \"" << line << "\"\n";  
        //  char x; 
        //  std::cout << "Enter any character to skip this input line"; std::cin >> x;
        // }
        
        std::istringstream iss(line); // hold the line here to parse it

        if (!(iss >> piece >> row >> colChar)) {
            std::cout << RED << "!! Error in input file - could not parse line of text. Skipping." << RESET << std::endl;
            { char x; std::cout << "Enter any character to skip this input line"; std::cin >> x;}
            continue;
        }

        std::string comments;
        std::getline(iss, comments); // "consume" any remaining comments from the input file
        
        col = ((int)colChar[0]-96); // convert to row character to int as 1 for a, 2 for b, 3 for c, etc.
        successfulMove = g.takeTurn(piece, row, col); // allow the current player to take their turn with the provided move
        g.printMe(); // print out the result of the turn (if taken) after the move

        // if (!successfulMove) {
        //   //\033[1;31mThis is bold red text\033[0m\n"
        //   std::cout << "\033[1;31m!!!  ERROR : Legal Move failed.  Please check your solution. Aborting game # " << gameCount << " on move #" << currentMove << "." << RESET << std::endl;
        //   wasThisTestOk = false;
        //   break;
        // }
      }
      else { // picking a random piece and a random move
        getRandomMove( g, piece, row, col );
        successfulMove = g.takeTurn(piece, row, col, true ); // moves for takeTurn() are 1-based, be silent
        if ( successfulMove) g.printMe(); // only print the board if we moved successfully
      }
      
      // CHALLENGE:  implement these methods in ChessBoard.cpp for a +5 both methods
      winnerName = g.isCheckmate(); // see who wins: "White", "Black" or "KeepPlaying"
      if (winnerName != "KeepPlaying" ) { // The game is over 
        std::cout << (winnerName) << " has won the game via checkmate! This game is over." << std::endl;
      }


      else if (g.isStalemate()) {
          stalemateString="Stalemate";
          std::cout << " The game is a stalemate (tie)! This game is over." << std::endl;
      }
      else {
          std::cout << " This game is still active and it is " << (g.whiteTurn ? "White's" : "Black's" ) << " turn" << std::endl;
      }

      //{ char c; std::cout << "next move(enter any character) ? ";std::cin >> c;}
      
    } // done with all moves

    if ( doRandomMoves ) g.printMe(); // final print for random moves test cases

    std::string bcode_game = getBoardCode( g );

    if (winnerName != "KeepPlaying")
      bcode_game = bcode_game + winnerName + "WinsByCheckmate";// append the winnerName (White, Black)
    else if (stalemateString.size()!= 0)
      bcode_game = bcode_game + "Stalemate";
    else
      bcode_game = bcode_game + "KeepPlaying";
    
    std::string bcode_fromFile;
    inFile  >> bcode_fromFile; // read in the final board code from the file and compare to current state of this game
    // std::cout << "DEBUG: " << bcode_fromFile << std::endl;
    // {char x; std::cout << "OK?"; std::cin >> x;}
    
    if ( bcode_game != bcode_fromFile ) {
      std::cout << RED << "!!!  ERROR : The final state of the game board does not appear to be correct.  Please check your solution. Game # " << gameCount << " Test has failed after all moves." << RESET << std::endl;
      wasThisTestOk = false;

      std::cout << "Correct Board Code for this game is ";
      for(int y=0; y<bcode_fromFile.size(); y++) {
        if (y < bcode_game.size()  && y < bcode_fromFile.size() && bcode_game[y] == bcode_fromFile[y] ) 
          std::cout << "\033[;32m" << bcode_fromFile[y]; // green
        else
          std::cout << "\033[1;31m" << bcode_fromFile[y];  // red
      }
      std::cout << "" << RESET << std::endl;
      std::cout << "Final Board Code for this game is   ";
      for(int y=0; y<bcode_fromFile.size(); y++) {
        if (y < bcode_game.size()  && y < bcode_fromFile.size() && bcode_game[y] == bcode_fromFile[y] ) 
          std::cout << "\033[;32m" << bcode_game[y]; // green
        else
          std::cout << "\033[1;31m" << bcode_game[y];  // red
      }
      std::cout << "" << RESET << std::endl;
    }


    if (wasThisTestOk) {
      std::cout << "\n\033[;32mGAME OVER:  game #" << gameCount << " " << gameName << " testing succeeded. " << RESET << std::endl << std::endl;
      goodTests++;
    }
    else{
      std::cout << RED << "GAME OVER:  game #" << gameCount << " " << gameName <<  " testing failed. " << RESET << std::endl << std::endl;
      badTests++;
    }

    


    { // continue?
        char c; 
        std::cout << "Next game? (y or q) "; 
        std::cin >> c;  
        if ( c=='q') { 
          std::cout << "Aborting Testing... " << std::endl; 
          return false;
        }
    }
    
  } // done with all game tests

  std::cout << "\n\nYour testing results are: \n";
      //   cout << "\033[;32mGreen Text\033[0m\n";
  std::cout << "\033[;32m Tests Completed Successfully: " << RESET << goodTests << std::endl;
  std::cout << "\033[1;31m Tests Failed: " << RESET << badTests << std::endl;
  std::cout << std::endl;
  
  inFile.close();
  outFile.close();

  return true;
  
} // end testMe()