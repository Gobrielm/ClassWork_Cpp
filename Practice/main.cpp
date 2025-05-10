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

int main() {


    // std::vector<int> v;
    // int total = 10000000;
    // int* count = new int(0);
    
    // for (int i = 0; i < total; i++) {
    //     v.push_back(rand() % 20);
    // }
    // std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    // std::thread th1(sum_v, 0, total / 4, v, count);
    // std::thread th2(sum_v, total / 4, total / 2, v, count);
    // std::thread th3(sum_v, total / 2, total / 4 * 3, v, count);
    // std::thread th4(sum_v, total / 4 * 3, total, v, count);

    // th1.join();
    // th2.join();
    // th3.join();
    // th4.join();
    // delete count;
    // Dog* newDog = new Dog();
    // newDog->setName("A");
    //delete newDog;

    // std::multiset<int, greater<int>> mySet {5, 5, 5, 5, 7, 1, 9, 10, 11, 67, 2, 5};
    // for (const auto &i: mySet) {
    //     std::cout << i << ' ';
    // }
    // for (int i = 0; i < 1000000000; i++) {
    //     int x = 5 + 25;
    // }

    


    // std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    // std::chrono::duration<double> time_spent = t2 - t1;
    // std::cout << "\n";
    // std::cout << time_spent.count() << "\n"; //0.066781

}

void sum_v(int from, int to, std::vector<int> v, int* count) {
    int temp_count = 0;
    for (int i = from; i < to; i++) {
        temp_count += (v)[i];
    }
    m.lock();
    *count = *count + temp_count;
    m.unlock();
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