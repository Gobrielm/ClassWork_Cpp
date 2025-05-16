#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <set>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

#include <vector>

class Foo  {

    protected: int x;
  
  };
  
  
  class FooJr  : public Foo{
         public:
            FooJr() {cout << x; }
  };

std::mutex m;

void sum_v(int from, int to, const std::vector<int> v, int* count) {
    int temp_count = 0;
    
    for (int i = from; i < to; i++) {
        temp_count += (v)[i];
    }
    m.lock();
    *count = *count + temp_count;
    m.unlock();
}

void create_threads(int numThreads, const std::vector<int>& v, int* count) {
    std::vector<std::thread*> threads;
    for (int i = 0; i < numThreads; i++) {
        m.lock();
        std::thread* th = new std::thread(sum_v, v.size() / (numThreads) * (i), v.size() / (numThreads) * (i + 1), v, count);
        m.unlock();
        threads.push_back(th);
    }

    for (std::thread* x: threads) {
        x -> join();
    }
}

int main() {


    std::vector<int> v;
    int total = 200000000;
    int* count = new int(0);
    
    for (int i = 0; i < total; i++) {
        v.push_back(1);
    }
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    create_threads(2, v, count);
    delete count;
    // Dog* newDog = new Dog(); 1.3, 1.11, 17
    // newDog->setName("A");
    //delete newDog;

    // std::multiset<int, greater<int>> mySet {5, 5, 5, 5, 7, 1, 9, 10, 11, 67, 2, 5};
    // for (const auto &i: mySet) {
    //     std::cout << i << ' ';
    // }
    // for (int i = 0; i < 1000000000; i++) {
    //     int x = 5 + 25;
    // }

    


    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_spent = t2 - t1;
    std::cout << "\n";
    std::cout << time_spent.count() << "\n"; //0.066781

}




int findMedian(std::multiset<int> s) {
    int middlePosition = s.size() / 2;
    int count = 0;
    for (auto i: s) {
        count++;
        if (count == middlePosition) {
            return i;
        }
    }
    return 0;
}