#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void drawTile(int x, int y, vector<vector<string>> &output);
void drawSegment(int x, int y, int l, vector<vector<string>> &output);

int main() {
    vector<vector<string>> output;
    for (int i = 0; i < 100; i++) {
        output.push_back({});
        for (int j = 0; j < 100; j++) {
            output[i].push_back("-");
        }
    }
    drawSegment(50, 99, 25, output);
    ofstream file("output.txt");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            file << output[i][j];
        }
        file << '\n';
    }
    file.close();
    return 0;
}

void drawSegment(int x, int y, int l, vector<vector<string>> &output)  {
    if (l <= 1 || x - l <= 0 || y - l <= 0 || x + l >= 100) {
        return;
    }
    for (int i = 0; i < l; i++) {
        drawTile(x + i, y - i, output);
        drawTile(x - i, y - i, output);
    }
    drawSegment(x + l, y - l, l / 2, output);
    drawSegment(x - l, y - l, l / 2, output);
}

void drawTile(int x, int y, vector<vector<string>> &output) {
    output[y][x] = "B";
}