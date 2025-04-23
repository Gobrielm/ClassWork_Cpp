#include <memory>

int findTreasure(std::unique_ptr<int> treasureMap[ 20 ][ 10 ], int rowCount, int colCount ) {

    int sum = 0;
    for(int r=0; r<rowCount; r++) {
      for(int c=0; c<colCount; c++) {
        if (treasureMap[r][c] != nullptr )
          sum += *treasureMap[r][c];
      } // end inner for
    } // end outer for

  return sum;
} // end findTreasure()
