#include <iostream>
#include <memory>


using namespace std;

class Vehicle {
  static int count;
  const int id;
  const string type;
  const bool isElectric;
  public:
  Vehicle(string _type = "generic", bool _isElectric = false): type(_type), isElectric(_isElectric), id(count) {
    count += 1;
  }

  ~Vehicle() {
    cout << type << " is being deleted";
    count -=1;
  }

  bool get_isElectric() {
    return isElectric;
  }
  
  string get_type() {
    return type;
  }

  void printMe() {
    cout << "A " <<type << " that is " << (isElectric ? " ": "not ") << "electric with id: " << id << '\n';
  }
};

class Honda: public Vehicle {

  Honda(): Vehicle("Honda", false) {}

  ~Honda() {
    cout << get_type() << " Goodbye";
  }
};

class Tesla: public Vehicle {

  Tesla(): Vehicle("Tesla", true) {}

  ~Tesla() {
    cout << get_type() << " Goodbye";
  }
};

class ParkingSpace {
  static int count;
  Vehicle* occupiedBy;
  const int spaceId;
  bool hasCharger;
  public:
  ParkingSpace(): spaceId(count) {
    hasCharger = false;
    occupiedBy = nullptr;
    count++;
  }

  ~ParkingSpace() {

    count--;
  }
  int get_spaceId() {
    return spaceId;
  }
  bool get_hasCharger() {
    return hasCharger;
  }
  void set_hasCharger(bool _hasCharger) {
    hasCharger = _hasCharger;
  }
  bool isEmpty() {
    return occupiedBy == nullptr;
  }
  bool canParkHere(Vehicle *_vPtr) {
    if (isEmpty()) {
      occupiedBy = _vPtr;
      return true;
    }
    return false;
  }
  int doParkHere(Vehicle* _vPtr) {
    return occupiedBy == _vPtr;
  }
  void printMe() {
  }
};

int ParkingSpace::count = 0;

int Vehicle::count = 0;

int main() {
  
  return 0;
}