#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <set>
#include <chrono>
#include <thread>
#include "animal.h"

class Dog: private animal {
    public:
    Dog(std::string p_name = "") {
        name = p_name;
    }
    void setName(std::string p_name) {
        name = p_name;
    }

};


int findMedian(std::multiset<int> s);

template <typename T>
struct greater {
    bool operator()(const T &a, const T &b) const {
        return (a > b);
    }
};



int main() {

    // std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

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
    // std::cout << time_spent.count() << "\n";

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