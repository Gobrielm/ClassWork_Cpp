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
        for (int j = 0; j < 500; j++) {
            output[i].push_back("-");
        }
    }
    drawSegment(250, 100, 50, output);
    ofstream file("output.txt");
    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < output[i].size(); j++) {
            file << output[i][j];
        }
        file << '\n';
    }
    file.close();
    return 0;
}

void drawSegment(int x, int y, int l, vector<vector<string>> &output)  {
    if (l <= 2) {
        return;
    }
    for (int i = 0; i < l; i++) {
        drawTile(x + 2 * i, y - i, output);
        drawTile(x - 2 * i, y - i, output);
    }
    drawSegment(x + 2 * l, y - l, l / 2 + 1, output);
    drawSegment(x - 2 * l, y - l, l / 2 + 1, output);
}

void drawTile(int x, int y, vector<vector<string>> &output) {
    if (y >= 0 && output.size() > y && output[y].size() > x && x >= 0) {
        output[y][x] = "B";
    }
}