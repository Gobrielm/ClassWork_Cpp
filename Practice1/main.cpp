#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;

// Base class for  Bee
class Bee {
    static int count;
    const int id;
    const string type;
    
    public:
    Bee(string _type = "Base"): type(_type), id(count) {
        cout << "Bee created with type " << type << " and id " << id << '\n';
        count += 1;
    }

    ~Bee() {
        cout << "Bee destroyed with type " << type << " and id " << id << '\n';
        count -= 1;
    }

    string getType() {
        return type;
    }

    int getId() {
        return id;
    }

    static int getCount() {
        return count;
    }

    void printBee() {
        cout << "Bee of type " << type << " with id: " << id << '\n';
    }
};

int Bee::count = 0;

// Derived class for Drone

class Drone: public Bee {
    public:
    Drone(): Bee("Drone") {}
};

// Derived class for Worker

class Worker: public Bee {
    public:
    Worker(): Bee("Worker") {}
};

// Definition of the Cell class

class Cell {
    static int count;
    const int id;
    const bool dronesOnly;
    Bee* beePtr;
    public:
    Cell(bool _dronesOnly = false): id(count), dronesOnly(_dronesOnly), beePtr(nullptr) {
        count += 1;
    }
    ~Cell() {
        cout << "Cell class with id " << id << "is being deleted that has statud DronesOnly: " << dronesOnly << '\n';
        delete beePtr;
        count -= 1;
    }
    static int getCount() {
        return count;
    }
    int getId() {
        return id;
    }
    Bee* getBeePtr() {
        return beePtr;
    }
    bool isDroneCell() {
        return dronesOnly;
    }
    bool isEmptyCell() {
        return beePtr == nullptr;
    }
    bool canAssignBeeToCell(Bee* newPtr) {
        if (isEmptyCell()) {
            if (dronesOnly && newPtr->getType() == "Drone") {
                return true;
            } else if (!dronesOnly && newPtr ->getType() == "Worker") {
                return true;
            }
        }
        return false;
    }
    void doAssignBeeToCell(Bee* newPtr) {
        if (canAssignBeeToCell(newPtr)) {
            beePtr = newPtr;
        }
    }
    void printMe() {
        cout << "Cell id: " << id << ", DroneOnly: " << dronesOnly << ", Bee: " << beePtr << '\n';
    }
};

int Cell::count = 0;

// Definition of the 3D Hive class

class Hive {
    const int rows;
    const int columnsPerRow;
    const int slicesPerRow;
    Cell **** arr;
    public:
    Hive(int _rows, int _cols, int _slices): rows(_rows), columnsPerRow(_cols), slicesPerRow(_slices) {
        arr = new Cell***[rows];
        for (int r = 0; r < rows; r++) {
            arr[r] = new Cell**[columnsPerRow];
            for (int c = 0; c < columnsPerRow; c++) {
                arr[r][c] = new Cell*[slicesPerRow];
                for (int s = 0; s < slicesPerRow; s++) {
                    arr[r][c][s] = new Cell(rand() % 2);
                }
            }
        }

    }

    ~Hive() {
        cout << "Hive with rows: " << rows << ", cols: " << columnsPerRow << ", and slices: " << slicesPerRow << " is being deleted.\n";
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columnsPerRow; c++) {
                for (int s = 0; s < slicesPerRow; s++) {
                    delete arr[r][c][s];
                }
                delete[] arr[r][c];
            }
            delete[] arr[r];
        }
        delete[] arr;
    }

    void printHive() {
        cout << "Hive with rows: " << rows << ", cols" << columnsPerRow << ", and slices: " << slicesPerRow << "\n";
    }

    int countEmptyCells() {
        int count = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columnsPerRow; c++) {
                for (int s = 0; s < slicesPerRow; s++) {
                    if (arr[r][c][s] -> isEmptyCell()) {
                        count += 1;
                    }
                }
            }
        }
        return count;
    }

    int countDroneCellsInHive() {
        //Counting drones in hive
       int count = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columnsPerRow; c++) {
                for (int s = 0; s < slicesPerRow; s++) {
                    if (arr[r][c][s] -> isDroneCell()) {
                        count += 1;
                    }
                }
            }
        }
        return count;
    }

    vector<int> doAssignBeeToHive(Bee* beePtr) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columnsPerRow; c++) {
                for (int s = 0; s < slicesPerRow; s++) {
                    //Checks if can assign before assigning
                    if (arr[r][c][s] -> canAssignBeeToCell(beePtr)) {
                        arr[r][c][s] -> doAssignBeeToCell(beePtr);
                        return vector<int>{r, c, s};
                    }
                }
            }
        }
        return vector<int>{};
    }
};

void testMe(); // prototype

int main() { // written for you, may au
  
    testMe(); // defined below
    return 0;
  
} // end main()



//
// TEST ME 
//

void testMe() {

const string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const string RESET = "\033[0m";

cout << "Be sure to change comments in testMe() to activate tests!" << endl;

#define TESTME    // uncomment this line to test everything all at once
#ifdef TESTME       // Or.. move this #ifdef down gradually to expose each new test 1, 2, 3, etc, as you code
  
  int testCount = 0;
  int totalPoints = 0;
  string testName;
  int inc = 1;

  // TEST 1
  testName = "BEE: create and delete Bee (base)";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n------------------------------------------------\n";
    Bee * basePtr = new Bee();
    basePtr->printBee();
    assert( Bee::getCount() == 1 && "Bee Population should be 1" );
    delete basePtr;
    assert( Bee::getCount() == 0 && "Bee Population should be 0" );
    totalPoints += inc;
    cout << "Total tests passed so far: " << totalPoints << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }

  // TEST 2
  testName = "DRONE: create and delete Drone Bee";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n-------------------------------------------------\n";
    Drone * dronePtr = new Drone();
    dronePtr->printBee();
    assert( Bee::getCount() == 1 && "Bee Population should be 1" );
    delete dronePtr;
    assert( Bee::getCount() == 0 && "Bee Population should be 0" );
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }


  // TEST 3
  // create and delete worker bee
  testName = "WORKER: create and delete Worker Bee";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n-------------------------------------------------\n";
    Worker * workerPtr = new Worker();
    workerPtr->printBee();
    assert( Bee::getCount() == 1 && "Bee Population should be 1" );
    delete workerPtr;
    assert( Bee::getCount() == 0 && "Bee Population should be 0" );
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }
    

  // TEST 4
  testName = "CELL: Create and delete many empty Cells";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n---------------------------------------------------------\n";
    vector<Cell*> cellPtrs; // emtpy vector of cell pointers
    int droneCount = 5; int workerCount = 5;
    for (int i=0; i<droneCount; i++) cellPtrs.push_back( new Cell( true ) ) ; // drones 
    for (int i=0; i<workerCount; i++) cellPtrs.push_back( new Cell( false ) ) ; // workers 
    cout << "# of Cells created so far " << Cell::getCount() << endl;
    cout << "NOTE: Cell population after Cell creation is " << Cell::getCount() <<  ", and should be " << 10 << endl;
    assert( Cell::getCount() == (droneCount+workerCount) && " Cell population after Cell creation not correct");
    for (auto thisCell : cellPtrs ) delete thisCell; // destruct all cells.. pop count should fall to zero
    cout << "NOTE: Cell population after Cell vector clear is " << Cell::getCount() <<  ", and should be " << 0 << endl;
    assert( Cell::getCount() == 0 && " Cell population after clearing vector of cell poitners is not 0");
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }



    // TEST 5
  testName = "CELL: Create a drone cell and test isDroneCell() method";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n---------------------------------------------------------\n";
    Cell *cellPtr; // a single Cell pointer
    cellPtr =  new Cell( true )  ; // drone cell (true means drone)

    cout << "cellPtr->isDroneCell() says it is " << (cellPtr->isDroneCell() ? "" : " not" ) << " a drone cell" << endl;
    assert(  cellPtr->isDroneCell() == true  && "SHould have been a drone cell based on constructor argument being true" );
    delete cellPtr;
    
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }

  // TEST 6
  testName = "CELL: Create a worker cell and test isDroneCell() method";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n---------------------------------------------------------\n";
    Cell *cellPtr; // a single Cell pointer
    cellPtr =  new Cell( false )  ; // worker cell (false means worker)

    cout << "cellPtr->isDroneCell() says it is " << (cellPtr->isDroneCell() ? "" : " not" ) << " a drone cell" << endl;
    assert(  cellPtr->isDroneCell() == false  && "Should have been a worker cell based on constructor argument being false" );
    delete cellPtr;
    
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }


  
  // TEST 7
  testName = "CELL: Create a Cell, assign a drone using doAssignBeeToCell(),  and delete the Cell (check Bee and Cell population)";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n---------------------------------------------------------\n";
    Cell *cellPtr; // a single Cell pointer
    cellPtr =  new Cell( true )  ; // drone cell
    Drone * dronePtr = new Drone ; // drone bee
    // Assign drone to the honeycomb
    cellPtr->doAssignBeeToCell(dronePtr);
    cout << "# of Cells created so far " << Cell::getCount() << endl;
    cout << "# of Bees created so far " << Bee::getCount() << endl;
    cout << "Now.. we delete the Cell which should delete the Bee..." << endl;
    delete cellPtr;
    cout << "NOTE: Bee population after Cell delete is " << Bee::getCount() <<  ", and should be " << 0 << endl;
    assert( Bee::getCount() == 0 && " Bee population after Cell delete should be 0");
    assert( Cell::getCount() == 0 && " Cell population after Cell delete should be 0");
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }
  

  // TEST 8
  Hive * hivePtr;
  testName = "HIVE, CELL: Create and delete an empty Hive, check Cell population";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n--------------------------------------------------\n";
    int rows = 2; int cols = 2; int slices = 2;
    hivePtr = new Hive(rows, cols, slices  );
    hivePtr->printHive();
    cout << "# of Cells created so far " << Cell::getCount() << endl;
    cout << "NOTE: Cell population after Hive creation should " << rows*cols*slices << endl;
    assert( Cell::getCount() == rows*cols*slices && " Cell population after Hive creation not correct");
    delete hivePtr; 
    assert( Cell::getCount() == 0 && " Cell population after Hive delete should be 0");
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }

  // TEST 9
  // Hive * hivePtr; (declared above)
  testName = "HIVE Destructing Hive: create and delete an empty Hive, check Bee population";
  try {
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n------------------------------------------\n";
    hivePtr = new Hive(2, 2, 2 );
    hivePtr->printHive();
    cout << "# of Bees created so far " << Bee::getCount() << endl;
    assert( Bee::getCount() == 0 && " Bee population after creation should 0");
    delete hivePtr; 
    assert( Bee::getCount() == 0 && " Bee population after delete should 0");
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }



  // TEST 10
  // Hive * hivePtr; (declared above)
  int rows=2; int cols=3; int slices=4;
  try {
    testName = "HIVE: Create new empty Hive and test Hive::countEmptyCells()";
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n------------------------------------------\n";

    hivePtr = new Hive(rows, cols, slices  ); // create Hive
    hivePtr->printHive();

    int emptyCellsInHiveCount = hivePtr->countEmptyCells();
    assert( emptyCellsInHiveCount == rows*cols*slices && " countEmptyCells() is not correct");
    
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  catch(...) {
    cout << RED << "... countEmptyCells() should have been " <<  rows*cols*slices << RESET << endl;
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }


  // TEST 11
  try {
    testName = "HIVE: Use AssigneBeeToHive() assigning bees to empty Hive and test Hive::countEmptyCells(),";
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n------------------------------------------\n";

    Drone * dronePtr = new Drone();
    dronePtr->printBee();
    Worker * workerPtr = new Worker();
    workerPtr->printBee();
    cout << "\n# of Bees created now is " << Bee::getCount() << endl;
    assert( Bee::getCount() == 2 && " Bee population should 2");

    
    // Assign bees to the honeycomb
    vector<int> droneLocation = hivePtr->doAssignBeeToHive(dronePtr);
    vector<int> workerLocation = hivePtr->doAssignBeeToHive(workerPtr);

    hivePtr->printHive();

    cout << "Drone assigned to location: "; for (auto item: droneLocation ) cout << item << ", "; cout << endl;
    cout << "Worker assigned to location: "; for (auto item: workerLocation ) cout << item << ", "; cout << endl;

    int emptyCellsInHiveCount = hivePtr->countEmptyCells();
    assert( emptyCellsInHiveCount == rows*cols*slices-2 && " countEmptyCells() is not correct");
      
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
    
  catch(...) {
    cout << RED << "... countEmptyCells() should have been " <<  rows*cols*slices-2 << RED << endl;
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }

  
  // TEST 12
  try {
    testName = "HIVE: Delete Hive and test Bees::count() ";
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n------------------------------------------\n";

    // Print details of the HoneyComb
    hivePtr->printHive(); // should delete bees

    delete hivePtr; 
    assert( Bee::getCount() == 0 && " Bee population after Hive delete should 0");
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;
  }
  
  catch (...) {
    cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }

  // TEST 13
  try {
    testName = "Create new Hive, fill it using doAssignBeeToHive(new Drone ), and test Drone Cell distribution ";
    cout << "\nStarting Test # " << ++testCount << ", " << testName <<  "\n-----------------------------------------------------------------\n";

    rows = 4; cols = 4; slices = 4; // 64 bees, 50% should be drone compatible
    
    hivePtr = new Hive(rows, cols, slices  ); // create Hive

    int dronesAssignedCount = 0; // no drones assigned to the Hive so far
    for (int i=0; i<rows*cols*slices; i++){
      vector<int> droneLocation = hivePtr->doAssignBeeToHive(new Drone ); // true - it is a drone

      if (droneLocation.size() != 0) {
          cout << "Assigned new drone to location " << droneLocation[0] << ", " << droneLocation[1] << ", " << droneLocation[2] << endl;
          dronesAssignedCount++;
      }
    }

    cout << "All drones have been assigned - there should be " << dronesAssignedCount << " drones in droneOnly cells in the hive << " << endl;

    cout << "Testing hivePtr->countDroneCellsInHive() = " << hivePtr->countDroneCellsInHive() << endl;
    // cout << "Drones = " << hivePtr -> countDroneCellsInHive() << '\n';
    assert( hivePtr->countDroneCellsInHive() == dronesAssignedCount && " drones created should match drones assigned" );
    
    cout << "OK\n" << endl;
    totalPoints += inc;
    cout << GREEN << "Total tests passed so far: " << totalPoints << RESET << endl;

  }
  catch(...) {
      cout << RED << "... Failed Test "  << testCount << RESET << endl;
  }




  cout << "\n\nTotal tests passed = " << totalPoints << endl;

#endif
} // end testMe
