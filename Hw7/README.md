# Overview (Spring 23-B)
Write a PvP (player vs player) turn-based chess game, based on a simple printed character-representation of the standard chess board and named pieces .  (You will not be adding any "AI" for this assignment - but that would be an excellent personal project to pursue after this course!)  Search for "TODO" in this document for a short-cut to see implementation steps you must perform).

Please note: This assignment requires an understanding of class inheritance and over-riding of pure virtual base-class methods.  These concepts are generally not covered until late in the course and so attempting this assignment before these topics are covered can prove quite challenging.

Here's how our board will print below. Note that "r1b" means "rook 1 black" and "r1w" means "rook 1 white", etc.  

We will move pieces on each turn by stating the piece name followed by the location we want to move it to like: p1b 6 a which would move the black pawn #1 from its current position to row 6 column a (if legal).

The game will always start with a white piece and the turn will pass to the alternate player after each legal move.  Any illegal or unsuccessful move will be ignored and the turn will not be passed.

```
    a   b   c   d   e   f   g   h  
8: r1b h1b b1b qub kib b2b h2b r2b 

7: p1b p2b p3b p4b p5b p6b p7b p8b 

6: --- --- --- --- --- --- --- --- 

5: --- --- --- --- --- --- --- --- 

4: --- --- --- --- --- --- --- --- 

3: --- --- --- --- --- --- --- --- 

2: p1w p2w p3w p4w p5w p6w p7w p8w 

1: r1w h1w b1w quw kiw b2w h2w r2w 

    a   b   c   d   e   f   g   h 
```



# Reference
- If you are unfamiliar with the game of chess, you may wish to read a bit about it here:
https://chessdelights.com/chess-positions/ 
- This site is also helpful: https://www.chessvariants.com/d.chess/chess.html 

- You can play a simple game here to check your understanding:
https://www.chess.com/play/computer 

# The ChessBoard Class
Before each new turn, the game will print a representation of the board that closely matches the scheme shown above. Black Team will always start at the top of the printed board, and white team will always start at the bottom. 
- Note that each column takes up at least 4 characters so that we can easily identify the names of each of the pieces on the board (which are represented by 3 characters... so we'll see a gap between columns). 
- A blank line will be printed between rows to make the game board "more square" on the screen. 
- Rows will be labeled (1(bottom) through 8(top)) at the left of each row, and columns (a(left) through h(right)) at the top of each column, as shown below, to help players identify the desired location of their next move.

Our chess board will NOT be represented by 2D array of tokens, as we have done in other assignments. Instead, we will simply store a pointer (of type Piece, which is the Base Class) to to each of the derrived class instances of each piece in an array of Piece pointers.  This array of 32 Piece pointers will tell us all we need to know so that we can manage the game and print out a representation of the board at any time.  As such, the constructor for the ChessBoard class will also construct each different piece on the board by calling YOUR derived class constructor and storing a pointer to the instance of each piece in the ChessBoard pieces array.
- Except for the bonus, ChessBoard.cpp has been fully implemented for you
- The provided ChessBoard.cpp methods provide many insights into the architecture of this assignment.
- You should review both the ChessBoard.h and ChessBoard.cpp files to ensure you are oriented to this approach before beginning implementation of your derrived classes
- See more on the BONUS below, which requires that you implement two methods in the ChessBoard.cpp file:
  - bool ChessBoard :: isCheckmate(); // return a string that indicates the winnning color, or None, if not checkMate for the current color
  - bool ChessBoard :: isStalemate(); // return true if the game current player is not in check, but any possible move for the current player would be illegal
  



# The Pieces
Pieces are named as follows and the program will recognize them by name when input via main()

### White Team
- **Rook Names  : r1w, r2w** - left and right Rooks for white team
- **Knight Names: h1w, h2w** - left and right Knights for white team
- **Bishop Names: b1w, b2w** - left and right Bishops for white team
- **Queen   : quw** - Queen for the white team
- **King    : kiw** - King for the white team
- **Pawn  Names : p1w, .. p8w** - Pawns for the white team

### Black Team
- **Rook Names: r1b, r2b** - left and right Rooks for black team
- **Knight Names: h1b, h2b** - left and right Knights for black team
- **Bishop Names: b1b, b2b** - left and right Bishops for black team
- **Queen: qub** - Queen for the black team
- **King: kib** - King for the black team
- **Pawns: p1b, .. p8b** - Pawns for the black team


# Taking Turns
Players representing the white and black teams will take turns specifying which piece they want to move, along with the row, column location they want to move the piece to.  Each turn is comprised of a piece name, a row number, and a column letter. The move below attempts to move the pawn p1w from its current location to row 3, column a.

`White, Enter a move (piece_name row col_letter)?  p1w 3 a`
- Your game will need to recognize bad input and reprompt the same team player (don't change turns), if these conditions occur:
  - Prevent any unrecognized piece from being played at any time
  - Prevent the wrong team from playing out of order at any time
  - Prevent any illegal moves from occurring at any time

Internally, moves will be processed as 1-based integers.  As such, when writing code, all row values for moves will be from 1 through 8.  And all column values for moves will be from 1 through 8.  THe code written in main() will make these conversions for you before calling the ChessBoard :: takeTurn( ) method with an integer value for row and column. Note again that these values are NOT zero-based as in previous assignments.  They start at 1 (since we are note using an array)
# Illegal moves for all Pieces
The following are examples of moves that should be considered illegal by your program. These rules are consistent with standard chess rules, but are restated here to help you plan your implementation. Illegal moves should result in the same team being prompted again for the next move(wihtout changing turns):
- A piece may not be moved to a location which is "off the board" based on the row/column specified
- A piece which has been captured already may not be moved
- A piece may not be moved to a location that it cannot reach, based on its type (more on legal type-moves below)
- A piece may not move "through" any pieces which block its path
 -- unless it is the knight (because the knight, by definition can jump over other pieces)
 -- unless the "blocking" piece is from the other team and and is being captured AT the desired destination of the move
- A piece may not be moved to a location that is occupied by one of its own team pieces
- A piece may not be moved out of its current location, if doing so puts its own King in "check"
- A piece may not move to its current location ("null" moves are not allowed) 

# Legal moves
You may find the following page helpful in understanding the moves described below: https://www.chessvariants.com/d.chess/chess.html 
- **Pawn**: Moves only forward toward the opposing player's back line (cannot move backward). Can move 2 squares forward ONLY on its first move from its original position (It cannot jump over any pieces when taking its 2-space move!). Otherwise, on the first move or thereafter, always moves 1 sqaure forward at a time, unless capturing. Can only move diagonally-forward 1 square to its diagonal-left or diagonal-right when capturing a piece.  Causes the opposing King to be in check only at diagonal squares (in the pawn's forward direction).
- **Rook**: Moves only horizontally or vertically, forward or backward, sliding through **unblocked** squares on the board.  Can move as far as desired, or up to a square where it captures an opposing piece that blocks its path.  Causes an opposing King to be in check only when there is an unblocked horizontal or vertical path between the Rook and opposing King. Cannot jump over pieces.
- **Knight** - Moves to one of 4 possible destinations by jumping from its current position, over any blocking pieces, if necessary.  The "jump" forms an "L" shape in any of 4 directions.  The move can be thought of in two parts: first it moves 2 squares "forward" in any of 4 directions (left, right, up down), and second it moves 1 square to either the "left" or "right" of its "forward move" direction.  The resulting move is an oblique (2+1) diagonal on the board.  The Knight can only capture a piece in the location where it lands.  It Causes an opposing king to be in check only when the King resides in one of the 4 destinations that the Knight can jump to. Note again that "forward" for the Knight can be left, right, up, or down.
- **Bishop**: Moves only diagonally, forward or backward. Can move forward or backward, sliding through unblocked squares on the board.  Can move as far as desired, or up to a square where it captures an opposing piece that blocks its path.  Causes an opposing king to be in check only when there is an unblocked diagonal path between the Bishop and opposing King.  Cannot jump over pieces.
- **Queen**: Moves like a combination of the Rook and Bishop (not the Knight!). Horizontally AND Vertically, through unblocked squares.  Causes an opposing king to be in check only when there is an unblocked horizontal, vertical, or diagonal path between the Queen and opposing King. Cannot jump over pieces.
- **King**: Moves one square at a time, but may never move into a position of being in check. A King can never put an opposing King in check.

# Winning the game
- The game is won by a team when the opposing King is currently in check (under threat of capture) in its current position, AND there is no single move the opposing King can make that takes it out of check, AND there is no single move any other piece can make that would block the check or capture the piece that is causing the King to be in check.

# Tie game (Stalemate)
- The game is tied when the opposing King is NOT CURRENTLY in check (not under threat of capture) in its current position, AND there is no single safe move the opposing team can make using any of its pieces that would not cause the King to be in check (an illegal move).  This situation results in a stalemate and the game ends in a tie.  Implementing this feature is considered a optional bonus element of this assignment (see below).

# Simplifications
The following simplifications will be allowed to help keep things from becoming too complicated. (You are of course welcome to add these on your own if you like):
- ** Promotion** of Pawns which reach the farthest row of the board, opposite from their own starting location, will NOT be required.  Normally, a pawn reaching the farthest row can promote to a queen, rook, knight, or bishop, regardless of whether that piece has been capture during the game.
- **The En Passant** capture by Pawns need NOT be implemented (https://www.chessvariants.com/d.chess/enpassant.html) 
- **Castling** between the King and Rook need NOT be supported. (https://www.chessvariants.com/d.chess/castlefaq.html)

# C++ Class Hierarchy and the Piece class
Note that our game will demonstrate both inheritance and the use of virtual method over-riding in derived C++ classes, using pointers.  As such, our Piece.h and Piece.cpp files will represent the "base class" from which all other Chess pieces are derrived.  MOST OF THE CODE YOU NEED for the game resides in the Piece class (and ChessBoard.cpp), saving you significant work on your derrived classes.  Please study the Piece Class in particular to aid in your understanding of the work already done for you. Note that the Piece class will call a method named isLegalMoveTo().  This specific method will be over-ridden each each of your derived classes.  Writing this over-ridden method and a simple constructor for each derrived piece comprises the work you must do for this assignment.

# Provided for you ("DONE")
The following files have been provided for you and should be reviewed to help you understand operation of the game and the intended use of class methods
- main.cpp - game loop and testing
- ChessBoard.h, ChessBoard.cpp - representation of the ChessBoard class, which will construct the board, and pieces, and will point each piece at the board. (Note that your bonus features will be placed in ChessBoard.cpp, if provided)
- Pawn.h - Construstor, Methods, and Destructor for the Pawn.cpp class implementation
- King.h - Construstor, Methods, and Destructor for the King.cpp class implementation
- Queen.h - Construstor, Methods, and Destructor for the Queen.cpp class implementation
- Knight.h - Construstor, Methods, and Destructor for the Knight.cpp class implementation
- Bishop.h - Construstor, Methods, and Destructor for the Bishop.cpp class implementation
- Rook.h - Construstor, Methods, and Destructor for the Rook class .cpp implementation
  

# Implementation Steps ("TODO")
- A base-class **piece.h** and **piece.cpp** have been written for you.  This base class will provide you with the foundational data members and methods for all classes you derive to implement the six different types of chess pieces on the board (Pawn, Knight, Bishop, Rook, King, Queen).
- You will need to develop (derive) the following six classes via a .cpp and a .h file for each type of piece:
  - Pawn.cpp    (based on Pawn.h)
  - Queen.cpp   (based on Queen.h)
  - King.cpp    (based on King.h)
  - Bishop.cpp  (based on Bishop.h)
  - Rook.cpp    (based on Rook.h)
  - Knight.cpp  (based on Knight.h)

- Each of your derived classes will require the following:
  - Your derived classes should not need any new data members.  The data members in the base class should be sufficient (but you can add more members if you prefer)
  - Your derived classes must implement a single constructor that simply sets the **ptype** data member (which comes from the Piece base class) to a printable name that describes the piece: "King", "Queen", "Bishop", etc.  And your derived constructor must also properly invoke the base class Piece constructor to initialize its required arguments.  ```Note that there are two Piece constructors: a default Piece constructor and a Piece constructor with multiple arguments.  If you fail to invoke the Piece constructor explicitly from the constructor initializer list of your derived class, the default Piece constructor will be called automatically - this may not give you the results you intended, unless you manually implement the base class members one-by-one in your derived class implementation.```
  - Your derived classes must implement a destructor that simply prints a message when the derived piece is destroyed, describing which piece was destroyed (you can use the ptype data member for this).
  - Your derived classes must implement an over-ridden method called isLegalMoveTo() that will determine if a request row, column "move to" location (passed in as arguments to the method) is legal for that specific derived class.  Your isLegalMoveTo() will override the base class virtual method of the same name. (See Piece.h and Piece.cpp).  ```Note that the base class method is not a "pure virtual" method.  That is, it has not be deleted with a "= 0" designation in the Piece.h file.  This means that the Piece base class is not "abstract" and so it can be instantiated, and moreover, it means that if you fail to implement your derived isLegalMoveTo() method, then the "generic" base class isLegalMoveTo() method will be called instead.  This will not give you the intended result for a specific piece, but at least your program will compile and run.```


# Testing and Submission
Before submission, please test your game comprensively using the associated testMe() function call.  This call is configured in main() already so you simply need to run it before submitting your solution.

# Bonus
Implement either or both of the ChessBoard Class methods below for extra points.  See the references provided within this file for rules of the game relating to Checkmate and Stalemate situations.
- +10 Points - Implement the ChessBoard::isCheckmate() method
- +10 Points - Implement the ChessBoard::isStalemate() method
  
# Sample Output

```
      a   b   c   d   e   f   g   h  
8: r1b h1b b1b qub kib b2b h2b r2b 

7: p1b p2b p3b p4b p5b p6b p7b p8b 

6: --- --- --- --- --- --- --- --- 

5: --- --- --- --- --- --- --- --- 

4: --- --- --- --- --- --- --- --- 

3: --- --- --- --- --- --- --- --- 

2: p1w p2w p3w p4w p5w p6w p7w p8w 

1: r1w h1w b1w quw kiw b2w h2w r2w 

    a   b   c   d   e   f   g   h  
    
White, Enter a move (name row col_letter)p1w 3 a

piece.moveTo() : White Pawn moves from (2, a) to (3, a).

    a   b   c   d   e   f   g   h  
8: r1b h1b b1b qub kib b2b h2b r2b 

7: p1b p2b p3b p4b p5b p6b p7b p8b 

6: --- --- --- --- --- --- --- --- 

5: --- --- --- --- --- --- --- --- 

4: --- --- --- --- --- --- --- --- 

3: p1w --- --- --- --- --- --- --- 

2: --- p2w p3w p4w p5w p6w p7w p8w 

1: r1w h1w b1w quw kiw b2w h2w r2w 

    a   b   c   d   e   f   g   h  

Black, Enter a move (name row col_letter) p1b 6 a


piece.moveTo() : Black Pawn moves from (7, a) to (6, a).

    a   b   c   d   e   f   g   h  
8: r1b h1b b1b qub kib b2b h2b r2b 

7: --- p2b p3b p4b p5b p6b p7b p8b 

6: p1b --- --- --- --- --- --- --- 

5: --- --- --- --- --- --- --- --- 

4: --- --- --- --- --- --- --- --- 

3: p1w --- --- --- --- --- --- --- 

2: --- p2w p3w p4w p5w p6w p7w p8w 

1: r1w h1w b1w quw kiw b2w h2w r2w 
---
```


# About testMeIn.txt
The testMeIn.txt file is the input data file for automated testing of your code.  Though you do not need to worry about it structure, you may find it interesting as example of a slightly-complicated input file format.  Understanding its structure may also help you understand issues with your code, and in the rare occasion, how to extend or modify the testMeIn.txt file to help resolve tough issues in your solution. (You should otherwise not change the testMeIn.txt file from its original format, when submit your final solution.)
Here's a short description of the file format
- integer number of tests, on a line by itself, describing essentially how many chess games or tests will be run
Thereafter, the following will be repeated exactly "number of test" times
- string name of this test
- total number of moves in this test (where each player's move counts as 1 move)
Where each "move" is described as shown below, and is repeated "number of move" times
  - string name of piece
  - integer number of "to" row
  - character letter of "to" column
And finallly each game ends in a full description of the state of the board via a compact string similar to the one shown below:
- 1081rook0r1b1082knight0h1b1083bishop0b1b0048queen0qub1085king0kib1086bishop0b2b1087knight0h2b1088rook0r2b1071pawn0p1b1072pawn0p2b1073pawn0p3b1074pawn0p4b0055pawn0p5b1076pawn0p6b1077pawn0p7b1078pawn0p8b1011rook1r1w1012knight1h1w1013bishop1b1w1014queen1quw1015king1kiw1016bishop1b2w1017knight1h2w1018rook1r2w1021pawn1p1w1022pawn1p2w1023pawn1p3w1024pawn1p4w1025pawn1p5w0036pawn1p6w0047pawn1p7w1028pawn1p8w

Note that the testMe.cpp method getBoardCode() will "codify" the current state of the gameboard, so it can be compared against this final string.  If they match, the test is considered successful. Otherwise it is considered a failure, since the piece types and positions would not be a match.
THe contents of the board string are enumerated below using the following code
```
      tmp += std::to_string(p->neverMoved) + std::to_string(p->isCaptured) + std::to_string(p->row) + std::to_string(p->col) + (p->ptype) + std::to_string(p->isWhite) + p->name;
```

The check string is comprised (in order) of the string versions of each piece's data members (even if the piece has been captured):
- neverMoved
- isCaptured
- row location
- column location
- ptype
- isWhite
- name

So this String:
```
1081rook0r1b
```
means:1  0  8  1  rook 0  r1b
- 1 - true, never moved
- 0 - false, is not captured
- 8 - row 8, counting from 1 (bottom of screen)
- 1 - column 1, known as 'a', counting from 'a' (left of screen)
- rook - ptype is rook (this is the lower-case version of the constructor value set in the derived class.
- 0 - false, piece is not white, which means black team.
- r1b - Condensed name "rook 1 black team"

-----

#### Copyright © 2023 by Jeff Yates yatesjdy@gmail.com
All rights reserved. No part of this publication may be reproduced, distributed, or transmitted in any form or by any means, including photocopying, recording, or other electronic or mechanical methods, without the prior written permission of the publisher, except in the case of brief quotations embodied in critical reviews and certain other noncommercial uses permitted by copyright law.


