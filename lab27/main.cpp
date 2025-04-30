/*

COMP 235

Lab 27 : Virtual Methods  (Start)

Implement a simple class hierarchy that utilizes the abstract Shape base class to report the color and volume of two derived 3D shapes: Cube and Cylinder

Your solution should support the code provided in main() without changing the Abstract base Shape class, and without changing main().

And it should print the volumne of each shape as indicated in the comments in main().

Note that the Shape class does not provide a default constructor, so you must call the Shape constructor from your derived class constructors to set the base color of each shape.

Also, because the getColor() method is "protected" in the based class, your derived classes will require the "using" keyword to expose the protected method so it can be called in main() directly. Remember NOT to use the parenthesis () when you "re-designate" your getColor() method as public in the child class.

*/

#include <iostream>
using namespace std;



class Shape { // Abstract class (do not change)
  private:
    std::string color; // color of this shape... all shapes have a color
  protected:
    Shape( std::string _color ){ // constructor
      color = _color;
    }
    virtual double getVolume() = 0;  // pure virtual method (prevents us from instantiating this Shape!)
    std::string getColor() { return color;}
}; // end Shape


// TODO STEP 1: Create a Cube class that derives from Shape, and adds a double data member "size" and an overridden getVolume() method
//   where the volume of a Cube can be calculated as the size * size * size
class Cube: public Shape {
    private:
        double size;
    
    public:
    Cube( std::string p_color , double p_size): Shape(p_color) { // constructor
        size = p_size;
    }
    using Shape::getColor;

    double getVolume() {
        return size * size * size;
    }
};



// TODO STEP 2: Create a Cylinder class that derives from Shape, and adds double data members "height" and "radius", and an overridden getVolume() method
//   where the volume of a Cylinder can be calculated as the height * radius * radius * 3.1415926 .
class Cylinder: public Shape {
    private:
        double radius;
        double height;
    public:
    Cylinder( std::string p_color , double p_height, double p_radius): Shape(p_color) { // constructor
        radius = p_radius;
        height = p_height;
    }
    using Shape::getColor;
    double getVolume() {
        return radius * radius * height * 3.14159265;
    }
};


int main() {

//   Shape badShape( "grey" ); // DONE: this should not work because Shape is an abstract class (feel free to test it)

  // TODO STEP 3: uncomment when ready
  Cube myCube("red", 10 ); // 10 inch red cube with a volume of 1000 square inches
  cout << "The " << myCube.getColor() << " cube has a volume of " << myCube.getVolume() << " square inches " << endl;

  // TODO STEP 4: uncomment when ready
  Cylinder myCylinder("blue", 10, 1 ); // 10 inch (height) x 1 inch (radius) blue cylinder with a volume of 31.4159 square inches
  cout << "The " << myCylinder.getColor() << " Cylinder has a volume of " << myCylinder.getVolume() << " square inches " << endl;

}