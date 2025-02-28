#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <set>

int findMedian(std::multiset<int> s);

template <typename T>
struct greater {
    bool operator()(const T &a, const T &b) const {
        return (a > b);
    }
};

int main() {
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