#include <iostream> // so we can use cout and endl below
#include <iomanip> // so we can use setw() below
#include <memory>


// Print the treasure map
void printTreasureMap(std::unique_ptr<int> treasureMap[ 20 ][ 10 ], int rowCount, int colCount ){ 

  if ( rowCount != 20 ) {
    std::cout << "Sorry I cannot only print the treasure map if it has 20 rows" << std::endl;
    return;
  }

  if ( colCount != 10 ) {
    std::cout << "Sorry I cannot only print the treasure map if it has 10 columns" << std::endl;
    return;
  }
  
  for(int r=0; r<rowCount; r++) { // for each row
    
    for(int c=0; c<colCount; c++) { // for each column within each row
      
      if (treasureMap[r][c] != nullptr ) // if the maze pointer is not nullptr
        std::cout << std::setw(10) << std::left << treasureMap[r][c].get() << "->" << std::left << std::setw(4) << *treasureMap[r][c]; // print "what is at" the location pointed to be the address stored in location r, c of maze
        // HINT!! we need to use the unique_ptr get() method above: treasureMap[r][c].get() to print its address
      else
        std::cout << std::setw(10) << std::left << "nullptr   " <<  std::setw(6) << " ";
      
    } // end inner for
    
    std::cout << std::endl; // end this row, before we start a new one 
    
  } // end outer for
} // end function