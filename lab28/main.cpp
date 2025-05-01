/* 


COMP 235

Lab 28 (NOT OPTIONAL) : Threaded Guessing Game  (Start)

main() has been written for you, using 3 "guesser threads",  but you may add more threads if you like

Develop a simple multi-threaded guessing game "worker" function
where any number of “guesser” threads launched in main() compete to guess a secret number that is being “held” by the main() thread.

Have the the guesser threads guess randomly to keep things simple.

Use the same worker function for all guesser threads

If the guesser thread believes it guesses correctly, print “I win” and quit the game.
  Use a lock to ensure that only one thread ever prints “I win”.

Make sure your program terminates normally when one thread guesses the secret number (print a message in main() to confirm you’ve done it correctly.)

You program should not crash and it should not end up in “thread lock” (infinite loop)

You may need to put a 1 second sleep pause in your worker function to slow things down so you can debug

*/

#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>


using namespace std;

void doGuess(int secretNumber, mutex *m, int myID, int *winner ){

  while(true){
    // try to get the lock from m (will automatically wait here if it is not available)
    m -> lock();
    // check to see if *winner is still -1 (no winner yet)
    // if some other thread already won (*winner != -1), then
      // print a message
      // unlock the mutex
      // and return
    if (*winner != -1) {
        cout << "Other thread has guessed the number\n";
        m -> unlock();
        return;
    // else we try ONE guess from 0 to 9 
    // (NOTE: we can increase the range to from 0 to 99, but be sure to change main() as well!) 
    // print the number that we choose as the guess
    } else {
        int guess = rand() % 10;
        cout << "Thread" << myID << " guesses " << guess << "\n";
        if (guess == secretNumber) {
            *winner = myID;
            cout << "Thread" << myID << " has guessed the number\n";
            m -> unlock();
            return;
        } else {
            cout << "Thread" << myID << " has failed to guess the number\n";
            m -> unlock();
        }
    }

    // guessed correctly?
    // if guess matches secretNumber
        // set the winning ID to be myID (this will signal other threads that the game is over)
        // print a message indicating myID has guessed correctly
        // unlock the mutex
        // return

  
    // else wrong guess
    // print a message that the guess was incorrect
    // unlock the mutex so other threads have a chance

    this_thread :: sleep_for(  chrono::seconds(0)); // sleep for 1 second to give other threads a chance
      // NOTE: not fair to sleep before the unlock... why?
      //     because all other threads are locked while we are sleeping.
  } // end while

} // end doGuess()




int main() { // DONE FOR YOU
  
  cout << "Lab: Threaded Guessing Game\n";

  // srand(time(nullptr)); // notice that without this call to srand() our secret number will always be 3
  int secretNumber = rand()%10;   // between 0 and 9
  int winner = -1; // -1 means no one has won yet

  mutex m;

  cout << "main(): I am thinking of the number " << secretNumber << endl;
  cout << "main(): Let's see which thread guesses it first..." << endl;

  // launch our threads
  thread t1(doGuess, secretNumber, &m, 1, &winner);
  thread t2(doGuess, secretNumber, &m, 2, &winner); 
  thread t3(doGuess, secretNumber, &m, 3, &winner);

  t1.join(); // rejoin the threads here
  t2.join();
  t3.join();

  cout << "main(): and the winner is.....";
  cout << "Thread #" << winner << endl;

}