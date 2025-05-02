#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <set>
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
    Dog* newDog = new Dog();
    newDog->setName("A");

    std::multiset<int, greater<int>> mySet {5, 5, 5, 5, 7, 1, 9, 10, 11, 67, 2, 5};
    for (const auto &i: mySet) {
        std::cout << i << ' ';
    }

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