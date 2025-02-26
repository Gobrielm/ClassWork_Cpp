#include <iostream>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

int addOne(int num);
bool compare(int num1, int num2);


int main() {
    list<int> l = {3, 6, 4, 1, 2, 8, 10};
    list<int> lOne = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    transform(l.begin(), l.end(), lOne.begin(), addOne);
    for (auto item: lOne) {
        cout << item;
    }

}

int addOne(int num) {return num + 1;}

bool compare(int num1, int num2) {return num1 < num2;}