/*

COMP 235 

LAB 22 :  Buried Treaasure  (Start)

Convert the functioning program below to use unique pointers from the <memory> library.

You will need to convert all cpp files in this repl

First, run the program below to be sure you understand its operation.

Choose a random seed and observe the sum of "found gold" that is printed out for each unique seed chosen.

Note that the findTreasure() function  searches through the entire "treasure map" of pointers to find locations in the 2D array that are not nullptr.

The function then returns a total of the non-null pointer's integer references as the "total gold found."


Test your "unique pointer" version of this program by visually adding up the treasure you see in the treasure map printed.  
The sum returned from findTreasure() should match.

*** HINT **** you will need to use the unique_ptr get() method to "get" and print the raw address within the printTreasureMap() function.

      see reference:  https://en.cppreference.com/w/cpp/memory/unique_ptr/get


  */

  #include <iostream>
  #include <string>
  #include <iomanip>
  #include <memory>
  using namespace std;
  
  void hideTreasure(unique_ptr<int> treasureMap[ 20 ][10], int rowCount, int colCount );  // prototype -you will need to change "int *"" to use unique_ptr
  void printTreasureMap(unique_ptr<int> treasureMap[ 20 ][ 10 ], int rowCount, int colCount ); // prototype - you will need to change "int *"" to use unique_ptr
  int findTreasure(unique_ptr<int> treasureMap[ 20 ][ 10 ], int rowCount, int colCount ); // prototype - you will need to change "int *"" to use unique_ptr
  
  
  int main() {
  
    cout << "Please enter a seed for the random number generator (ex: 12 would result in 348 units of treasure found ): ";
    int seed; cin >> seed;
    srand(seed);  // the same seed should generate the same treasure map each time we rerun
    
    const int numberOfRows = 20; // constant dimensions for our treasure map below
    const int numberOfColumns = 10;
  
    unique_ptr<int> myTreasureMap[numberOfRows][numberOfColumns]; // a 2D array of pointers
    hideTreasure( myTreasureMap, numberOfRows, numberOfColumns ); // "hides" integers via pointers at random locations (else sets pointers to nullptr)
  
    printTreasureMap( myTreasureMap, numberOfRows, numberOfColumns );// print a description of the treasure map using printTreasureMap()
  
    int totalTreasureFound = 0; // no treasure found yet
    //  Call your findTreasure() function here and store its return value in  "totalTreasureFound"
    totalTreasureFound = findTreasure( myTreasureMap, numberOfRows, numberOfColumns );
    
    cout << endl << "The total treasure found for the seed value " << seed << " is " << totalTreasureFound << endl;
  
  } // end main()
  
  
  