/*

COMP 235

Lab 31 - Exceptions  (Start)

Catch all exceptions in main(), without altering the class provided.

You will need to add a try { } and mutliple catch { } sections to main() to handle exceptions raised by the class and its use in main

Uncomment each exception situation in main() (see TODO notes below) and catch the specific exception it throws.

Your program should not crash when you are done.

Note that catching an exception allows program execution to continue (at the top of the while loop)

You may wish to reference this page: https://en.cppreference.com/w/cpp/error/exception

*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class VectorN { // a vector of arbitrary dimension
  public:
    std::vector<double> vec; // our actual vector values ("dim" of them)

    VectorN( int _dim = 0 ) {
      if ( _dim <= 0)
        throw invalid_argument("VectorN Constructor 1: invalid_argument exception thrown: Dimension values passed to the constructor must be Postive ");

      // else
      vec.resize( _dim, 0.0 ); // set the vector size to _dim, and init all values to zero
    } // end constructor 1

    VectorN( std::vector<double> v = { }  ) {
      if ( v.size() == 0)
        throw invalid_argument("VectorN Constructor 2: invalid_argument exception thrown: Vectors passed to the constructor must non-zero size ");

      // else
      vec = v; // copy into v
    } // end constructor 2


  double operator+ (const VectorN & rhs ){  // add the vector rhs, but only if it is of the same dimension

    if ( this->vec.size() != rhs.vec.size()  ) 
        throw out_of_range("VectorN :: operator+() : out_of_range exception thrown: Vectors of different sizes cannot be added");

    // else
    for( int i=0; i< vec.size(); i++) vec[i] += rhs.vec[i];

  } // end division overload

  double mag( ) { // return the magnitude of the vector
    double sum =0.0;
    for(auto & i : vec) sum += i*i;
    return sqrt( sum );
  }

  double normalize( ) { // normalize this vector by dividing each of its components by the magnitude
    double m = mag();// calculate the magnitude
    if ( m == 0) 
      throw runtime_error("VectorN::normalize() : runtime_error exception thrown: cannot normalize a vector of magnitude zero");
    
    for(auto & i : vec) i /= m; // else divide by the mag
  }

};

int main() {

  while( true ) { // we will loop.. just to demonstrate that "catching" an exception allows us to continue
    // your final submission should not crash
    try {

    cout << "\n Ready to (re)test?  (hit any character and return to continue) ";
    char x; cin >> x; 
      
    VectorN tooSmall( 0 );  // TODO: should raise an exception
    VectorN empty( {  } ); // TODO: should raise an exception
    
    VectorN xy( 2 ); // XY 2D vector all zeros
    VectorN xyz( 3 ); // XYZ 3D vector all zeros
    VectorN xyzw( 4 ); // XYZW 4D vector all zeros

    
    VectorN sum = xy + xyz; // TODO: should raise an exception

    VectorN a ( { 0, 0, 0 } );
    a.normalize(); // TODO: should raise an exception 
  

    cout << "\nBottom of Loop... we have not crashed, so we'll continue from the top of the loop..." << endl;
    } catch (invalid_argument) {
        cout << "Invalid Argument\n";
    } catch (out_of_range) {
        cout << "out of range\n";
    } catch (runtime_error) {
        cout << "runtime error\n";
    }
  }
  // end while

} // end main()
