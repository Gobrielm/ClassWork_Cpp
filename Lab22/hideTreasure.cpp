#include <iostream>
#include <memory>

void hideTreasure(std::unique_ptr<int> treasureMap[ 20 ][ 10 ], int rowCount, int colCount ){
  
  if ( rowCount != 20 ) {
    std::cout << "Sorry I cannot only initialize the treasure map if it has 20 rows" << std::endl;
    return;
  }

  if ( colCount != 10 ) {
    std::cout << "Sorry I cannot only initialize the treasure map if it has 10 columns" << std::endl;
    return;
  }
  std::cout << "hideTreasure(): hiding the treasure...";

  //
  // nullify the the 2D array
  //

  for(int r=0; r<rowCount; r++){ // for each row
    for(int c=0; c<colCount; c++){ // for each column in each row
      if (rand()%(60) == 0) // 1/60 chance of finding treasure here!
        treasureMap[r][c] = std::make_unique<int>(rand()%(rowCount*colCount) );  // store a random amount of treasure here
      else
        treasureMap[r][c] = nullptr; // set the pointer to null (no treasure)
    } // end inner for
  } // end outer for

  std::cout << "DONE!" << std::endl << std::endl;

} // end hideTreasure