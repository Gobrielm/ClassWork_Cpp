/*

COMP 235

HW 8 : Threads Restaurant (Start)

  PLEASE SEE THE README FILE
  
  NOTE THAT THIS ASSIGNMENT IMPLEMENTS ALL CLASSES IN THE MAIN.CPP File
  
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <mutex>



using namespace std;

const char * redTextStart =          "\033[1;31m"; // change output text color to red (used in cout)
const char * invertRedTextStart =    "\033[7;31m";
const char * blueTextStart =         "\033[;34m";
const char * greenTextStart =        "\033[;32m";
const char * invertWhiteTextStart =  "\033[7;37m";
const char * magentaTextStart =      "\033[;35m";
const char * invertMagentaTextStart =  "\033[7;35m";
const char * yellowTextStart =        "\033[4;33m";
const char * coloredTextEnd =         "\033[0m"; // end red text color (for cout)

//
// BUILD INPUT DATA FILES (not used)
//

void randomCustomers() { // this function builds a random customer data file. you do not need to call it unless you want to create a new data file for your testing purposes.
  ofstream outFile("randomCustomers.txt");
  vector<string> orders = { "burger", "chicken", "fish" };
  vector<string> people = {
  "Avery", "Bridget", "Cameron", "Dakota", "Ethan", "Fiona", "Gavin", "Hayden", "Isaac", "Jasmine", "Kaitlyn", "Leah", "Madison", "Natalie", "Oliver", "Paige", "Quentin", "Rebecca", "Sophie", "Trevor", "Ursula", "Violet", "Wyatt", "Xavier", "Yara", "Zane", "Asher", "Bella", "Caleb", "Delilah", "Ella", "Finn", "Grace", "Harper", "Isabella", "Jace", "Kendall", "Liam", "Mackenzie", "Nathan", "Owen", "Parker", "Quincy", "Riley", "Savannah", "Tristan", "Uriel", "Victoria", "Willow", "Ximena", "Yvette", "Zachary", "Aria", "Brody", "Cassie", "Dante", "Eliza", "Fletcher", "Gabriela", "Hayley", "Isabel", "Jaxon", "Kaden", "Luna", "Mason", "Nina", "Oscar", "Peyton", "Quinn", "Raven", "Samantha", "Theodore", "Una", "Vivian", "Wesley", "Xandra", "Yasmine", "Zara", "Amelia", "Bennett", "Caroline", "Daniel", "Emily", "Felicity", "Griffin", "Hazel" 
  };

  
  for (int p=0; p< people.size(); p++){
    outFile << people[p] << p << " " << orders[rand()%orders.size()] << endl;
  }
  outFile.close();
} // end randomCustomers


//
// CUSTOMER CLASS (done for you)
//

class Customer { 
  public:
    static int count; // STATIC: total number of instances created (initialized below)
    string customerName;
    string foodWanted;
    string foodReceived; // burger, chicken, fish, salad
    Customer ( string _name = "unkown", string _foodWanted  = "uknown") : customerName( _name ), foodWanted( _foodWanted ) { 
      cout << "Customer Constructor: created customer #" << count++ << ", " << customerName  << " who wants one " << foodWanted << endl;
    }

    ~Customer() { cout << "~Customer() decreasing count to " << --count <<  endl; } //  Destructor

    Customer( const Customer & other) { //  copy constructor
      cout << "Customer Copy Constructor: created copy of customer " << customerName  << " who wants one " << foodWanted << endl;
      customerName = other.customerName; 
      foodWanted = other.foodWanted; 
      foodReceived = other.foodReceived;
      count++; 
    }

    Customer& operator=(const Customer& other) { // new assignment operator
        if (this != &other) { // Self-assignment check
            customerName = other.customerName; 
            foodReceived = other.foodReceived;
        }
        return *this; // Return reference to the current object
    }

}; // end Customer class

int Customer::count = 0; // Static initialization: keep track of how many customers we created


//
// ORDER CLASS (done for you) 
//

class Order { 
  public:
    static int count; // STATIC: total number of orders instaces created: initialized below
    string customerName; // customer name
    string foodItem; // burger, chicken, fish, salad

    Order( string _customerName="none", string _foodItem = "none" ) : customerName( _customerName ), foodItem( _foodItem ) { 
        cout << "Order Constructor:    Created order #" << count++  << " for customer " << customerName << " for one " << foodItem << endl;
    }

    ~Order() { cout << "~Order() decreasing count to " << --count <<  endl; } //  Destructor

    Order( const Order & other) {  // copy constructor
      cout << "Order Copy Constructor: created copy of order " << foodItem  << " for  " << customerName << endl;
      customerName = other.customerName; 
      foodItem = other.foodItem; 
      count++; 
    }

    Order& operator=(const Order& other) { //  assignment operator
        if (this != &other) { // Self-assignment check
            customerName = other.customerName; 
            foodItem = other.foodItem;
        }
        return *this; // Return reference to the current object
    }

}; // end Order class

int Order::count = 0; // static initialization of count of all order instances created


//
// RESTAURANT CLASS
//

class Restaurant  { 
  
  public:

    queue<Customer> customersOutside;  // queue of Impatient customers waiting to have their order taken
    map<string, Customer> customersWaiting; // map of Hungry customers waiting for their order to be cooked and served to them
    queue<Order> ordersUncooked; // queue of orders taken and passed to the kitchen, but not yet cooked by the chef(s)
    queue<Order> ordersCooked; // queue of orders cooked by the kitchen chef(s), but not served
    queue<Customer> customersServed; // queue of Happy customers who have been served their cooked orders and can go home and eat

    static map<string, int> sales; // quantity of items sold for burgers, fish, chicken, etc.

  //
  // CONSTRUCTOR
  //
    Restaurant( string inputFileName) {

      ifstream inFile(inputFileName);
      string customerName;
      string foodItem;
      while ( inFile >> customerName >> foodItem ) {
        Customer newCustomer( customerName, foodItem); // create the customer
        customersOutside.push( newCustomer );
      }
      cout << greenTextStart <<  "The restaurant is open" << coloredTextEnd << endl;
      cout << yellowTextStart << "Hey we have a huge line of customers outside!!" << coloredTextEnd << endl;
      cout << "They look impatient... we better start taking orders!" << endl;
      inFile.close();
    } // end constructor

  //
  // CLOSE RESTAURANT
  //
    bool close() { // (try to) close the restaurant   

      cout << yellowTextStart << "\n\nRestaurant::close(): Trying to close your restaurant...." << coloredTextEnd <<  endl;
      int badReviews = 0; // we increment this below

      int customersConstructedCount = Customer::count; //  copy it before we decrement
      int ordersConstructedCount = Order::count; //  copy it before we decrement
      
      int servedCount = 0;
      while ( !customersServed.empty()) { // deconstruct and inspect the queue of served customers

        // did they get what they want?
        if ( customersServed.front().foodWanted != customersServed.front().foodReceived ) {
          cout << redTextStart << "Restaurant::close(): ERROR: customer " << customersServed.front().customerName << " has the wrong food item (they wanted " << customersServed.front().foodWanted  << " but they received " << customersServed.front().foodReceived  << "), You just got a bad review!" << coloredTextEnd <<endl;
          badReviews++; // one bad review is deadly!
        } // end of bad customer review
          

        // document what we sold, even if it was wrong
        sales[customersServed.front().foodReceived]++; // increment the count (0 will be added if it does not already exist)
        // done with  customer

      customersServed.pop(); // remove customer from the queue
      servedCount++; // increment how many customer we found in the served queue
        
      } // end while: done checking all served customers

      
      cout << "Restaurant::close(): There are " << customersOutside.size() << " customers outside (should be 0)" << endl;
      if (customersOutside.size() != 0 )  {
        cout << redTextStart << "Restaurant::close(): Oh no... you left " << customersOutside.size() << " customers waiting outside " << coloredTextEnd << endl;
        badReviews++; // another bad review
      }
      
      cout << "Restaurant::close(): There are " << customersWaiting.size() << " customers waiting for their cooked orders (should be 0 )" << endl;
      if (customersWaiting.size()  != 0 ) {
        cout << redTextStart << "Restaurant::close(): Oh no... you left " << customersWaiting.size() << " customers waiting for their orders " << coloredTextEnd << endl;
        badReviews++; // another bad review
      }
      
      cout << "Restaurant::close(): You served " << servedCount << " customers (and you constructed " << customersConstructedCount << " customers)" << endl; // JDY V2 fix use customersConstructedCount
      if (servedCount  != customersConstructedCount ) { // JDY V2 fix use customersConstructedCount
        cout << redTextStart << "Restaurant::close(): Oh no... you somehow did not serve the same number of customers as were originally constructed " << coloredTextEnd << endl;
        badReviews++; // another bad review
      }
      
      cout << "you served " << sales["burger"] << " burgers" << endl;
      cout << "you served " <<  sales["fish"]  << " fish" << endl;
      cout << "you served " <<  sales["chicken"]  << " chicken" << endl;
      cout << "(that's " << sales["burger"] + sales["fish"] + sales["chicken"] << " total orders served (should be " << ordersConstructedCount << ")" << endl;  // JDY V2 use ordersConstructedCount

      // if (sales["burger"] + sales["fish"] + sales["chicken"]   != ordersConstructedCount) { // use ordersConstructedCount
      //   cout << redTextStart << "Oh no... you somehow did not cook the same total number of orders " << coloredTextEnd << endl;
      //   badReviews++; // another bad review
      // }

    // did we get any bad reviews
    if (badReviews > 0){
      cout << redTextStart << "Restaurant::close(): Oh no... you received " << badReviews << " bad reviews.." << coloredTextEnd << endl;
      cout << redTextStart << "Restaurant::close(): The Restaurant is closed - Perhaps forever :( " << coloredTextEnd << endl;
      return false;
    }
    cout <<  greenTextStart << "The Restaurant is closed - everyone is happy!" << coloredTextEnd << endl;
    return true;
  } // end close() method

}; // end Restaurant class


// STATIC INITIALIZATION: RESTAURANT SALES figures
// these are the sales figures for each food type.  It is a map.
 map<string, int> Restaurant :: sales; // Restaurant::close() method will use this (you do not need to do anything)



// 
// TAKING ORDERS WORKER FUNCTION (Done for you)
// You should study this worker function and use it as a guide for the other two you must write below
// 

  void takingOrders(int threadId, Restaurant *r, mutex *m) {
    // INPUT: threadId is an integer that helps us tell which thread is "talking".  Please use it for all cout calls you make
    // INPUT: r is a pointer to a Restaurant instance.  You will use it to access data members AFTER you get the mutex lock
    // INPUT: m is a pointer to a mutex instance. You will use it to access the lock() and unlock() methods.
    
    while(true){ // loop until someone exits the loop
      m->lock(); // wait here until we get the mutex locked
      
      if ( r->customersOutside.empty()) { // see if there are customers outside waiting....
        m->unlock(); // unlock before we go.. we only do this when this cashier can quit and go home!
        std::cout << blueTextStart << "takingOrders(): Thread #" << threadId << " No more customers outside.. Quitting time for me!" << coloredTextEnd<< std::endl;
        return;
      }


      Customer serveMe = r->customersOutside.front(); // get a copy of the customer instance at the front of the queue
      r->customersOutside.pop(); // clear this customer from the queue
      m->unlock(); // unlock the mutex so other threads can go to work while I sleep (below)

      int delay = rand()%3;
      std::cout << blueTextStart << "takingOrders(): Thread #" << threadId << " Taking a customer " << serveMe.customerName  << " order for " << serveMe.foodWanted << "... this will take " << delay << " seconds...!" << coloredTextEnd<< std::endl;
      this_thread :: sleep_for( chrono::seconds(delay)); // sleep while we take this customer's order (unlocked!)
      
      m->lock(); // wake up and try to lock again so we can put the requested (uncooked)  order on the queue
      r->ordersUncooked.push( Order(serveMe.customerName, serveMe.foodWanted )); // create the order and push it on the queue
      r->customersWaiting.insert( { serveMe.customerName , serveMe } ); // KV pair goes into a map of customers waiting
      m->unlock();
      std::cout << blueTextStart << "takingOrders(): Thread #" << threadId << "... Order taken! Customer..." << r->customersWaiting[ serveMe.customerName ].customerName << " is waiting for their order " << coloredTextEnd<<std::endl;
      // Note above: this approach to printing the customer's name simply verifies that they are correctly stored in the map!
      // It also demonstrates how you can access a customer below when you need to serve them their order!

    } // end while
    
  } // done taking orders


//
// COOKING ORDERS WORKER FUNCTION (STEP 1: you must write this)
//

  void cookingOrders(int threadId, Restaurant *r, mutex *m) {
    while(true) {

        m -> lock();
        if (r -> customersOutside.size() == 0 && r -> customersWaiting.size() == 0) {
            std::cout << blueTextStart << "cookingOrders(): Thread #" << threadId << " Quitting time for me!" << coloredTextEnd<< std::endl;
            m -> unlock();
            return;
        }
        if (r -> ordersUncooked.size() == 0) {
            m -> unlock();
            std::cout << "cookingOrders(): Thread #" << threadId << " has nothing to do!";
            this_thread :: sleep_for( chrono::seconds(1));
            continue;
        }

        Order toCook = r -> ordersUncooked.front();
        r -> ordersUncooked.pop();
        m -> unlock();
        
        int delay = 2; //Default for Fish
        std::string foodItem = toCook.foodItem;
        if (foodItem == "Burger") {
            delay = 3;
        } else if (foodItem == "Chicken") {
            delay = 4;
        }
        std::cout << blueTextStart << "cookingOrders(): Thread #" << threadId << " Cooking a customers " << foodItem  << " order for " << toCook.customerName << "... this will take " << delay << " seconds...!" << coloredTextEnd<< std::endl;
        this_thread :: sleep_for( chrono::seconds(delay));

        m -> lock();
        r -> ordersCooked.push(toCook);
        m -> unlock();
    }
  } // done cooking orders


//
// SERVING ORDERS WORKER FUNCTION (STEP 2: you must write this)
//

  void servingCookedOrders(int threadId, Restaurant *r, mutex *m) {
    while (true) {
        std::cout << blueTextStart << "servingCookedOrders(): Thread #" << threadId << " Quitting time for me!" << coloredTextEnd<< std::endl;
        m -> lock();
        if (r -> customersWaiting.size() == 0 && r -> customersOutside.size() == 0) {
            m -> unlock();
            return;
        }
        if (r -> ordersCooked.size() == 0) {
            m -> unlock();
            std::cout << "servingCookedOrders(): Thread #" << threadId << " has nothing to do!";
            this_thread :: sleep_for( chrono::seconds(1));
            continue;
        }

        Order toServe = r -> ordersCooked.front();
        r -> ordersCooked.pop();

        m -> unlock();

        int delay = 2;
        std::cout << blueTextStart << "servingCookedOrders(): Thread #" << threadId << " Serving a customers " << toServe.foodItem  << " order for " << toServe.customerName << "... this will take " << delay << " seconds...!" << coloredTextEnd<< std::endl;
        this_thread :: sleep_for( chrono::seconds(delay));

        m -> lock();

        if (r -> customersWaiting.count(toServe.customerName) == 0) {
            m -> unlock();
            std::cout << "No customer of name " << toServe.customerName << " found!\n";
            return;
        }

        Customer c = r -> customersWaiting[toServe.customerName];
        c.foodReceived = toServe.foodItem;
        r -> customersWaiting.erase(toServe.customerName);
        r -> customersServed.push(c);

        m -> unlock();
    }
  } // done serving orders
  


int main() {

  Restaurant r( "customersLarge.txt"); // create a default restaurant.
  mutex m; // create a mutex

  thread t1( takingOrders, 1, &r, &m ); // start cashier #1, passing in the address of the restaurant and mutex
  thread c1( cookingOrders, 1, &r, &m ); // start chef #1, passing in the address of the restaurant and mutex
  thread s1( servingCookedOrders, 1, &r, &m );   // start waiter #1, passing in the address of the restaurant and mutex

  t1.join();
  c1.join();
  s1.join();

  r.close(); // close the restaurant
  
}