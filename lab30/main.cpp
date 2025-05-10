/*

COMP 235

Lab 30 :  Computing Stats with Lambda Functions   (Start)

TODO:  
Note the allValues list container in main
Iterate through the container using for_each
Compute and print out the following statistics using ONLY for_each and ”in-line” lambda functions (as arguments to the for_each call)
   sum
   average (the mean)
   statistical "population" variance: sum of the (differences from the mean)^2 

   OPTIONAL
    median (you can pre-sort the values if you like)

*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath> // for sqrt


using namespace std;


int main() {


 cout << "Lambda Stats\n";

 list<double> allValues = { 2,5,2,3,4,6,8,9,7,1,13}; // 
 allValues.sort(); 

//
// PRINT using a lambda and for_each
//

    for_each(allValues.begin(), allValues.end(), 
        [](int val) -> void {std:: cout << val;}
      // TODO: the 3rd argument of for_each() below is our lambda function
      // [ ]( ) { // print out all values in the allValues list
        
      // } // this is the end of our lambda

    ); // this is the end of the for_each() statement!
    cout << endl;

//
// SUM: compute the sum
//

    double sum=0;
    for_each(allValues.begin(), allValues.end(), 
      // TODO: the 3rd argument of for_each() below is our lambda function
      [&sum](int other_val) -> void { // sum up all values in the allValues list and store them in sum (Hint: use a reference)
          sum += other_val;
      } // this is the end of our lambda

    ); // this is the end of the for_each() statement!
    cout << "The sum = " << sum << endl;
    
    // compute total number of items in the vector (it should equal .size())
    int total=0;
    for_each(allValues.begin(), allValues.end(),
      // TODO: the 3rd argument of for_each() below is our lambda function
      [&total](int other_val) -> void { // count the number of items in the allValues container and store in "total" (Hint: use a reference)
        total += 1;
      } // this is the end of our lambda

    ); // this is the end of the for_each() statement!
    cout << "The count = " << total << endl;

    double mean = sum/total; // since know the sum and the total from above, we can calculate the average trivially below
    cout << "The mean (average) = " << mean << endl;
    // note: use the mean below in your calculation of the variance

//
// VARIANCE = sum of (differences from the mean)^2  (that is, squared)
//

    double sumSoFar = 0; // sum up squares of diffs from the mean

    for_each(allValues.begin(), allValues.end(), 
      // TODO: the 3rd argument of for_each() below is our lambda function
      [&sumSoFar, mean](int other_val) {  // calculate the sum of squares of differences from the mean, store in sumSoFar as we go
        sumSoFar += pow(mean - other_val, 2);
      } // this is the end of our lambda

    ); // this is the end of the for_each() statement!

    double variance = (double)sumSoFar/(allValues.size()-1); // this is the statistical variance

    cout << "The variance = " << variance << endl;
    cout << "The standard deviation = " << sqrt(variance) << endl;


  //
  // OPTIONAL (tricky)
  //

  // compute median

    allValues.sort(); // sort ascending, using the sort() method found in the list container

    int minValue = 10000000;
    int maxValue = 0;
    double prev=0;
    double median=0;
    int newCount=0;
    double halfWay = (total+1)/2.0; // 1-based

    cout << "halfWay = " << halfWay << endl;

    for_each(allValues.begin(), allValues.end(), 
      // TODO: the 3rd argument of for_each() below is our lambda function
      [&prev, &median, &newCount, halfWay, &minValue, &maxValue](double i)  { // compute the mins, max, median values of the all values in the list container
        if (i < minValue) {
            minValue = i;
        } else if (i > maxValue) {
            maxValue = i;
        }
        
        if (newCount == halfWay) {
            median = i;
        } else if (((int) halfWay) == newCount && (int) halfWay != halfWay) {
            prev = i;
        } else if (((int) halfWay) == (newCount - 1) && (int) halfWay != halfWay) {
            median = (prev + i) / 2;
        }
        newCount += 1;
        
      } // this is the end of our lambda

    ); // this is the end of the for_each() statement!

    cout << "The Median = " << median << endl;
    cout << "The Max = " << maxValue << endl;
    cout << "The Min = " << minValue << endl;


  
}
