#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> read_file() {
    string line;
    vector<string> res = {};

    fstream file("./input");

    if (file.is_open()) {
        while(std::getline(file, line)) {
            res.push_back(line);
        }
    }
    file.close();
    return res;
}

int part_1(vector<string> input) {
    int res = 0;

    for (string s : input) {
        res += 3 * ( (s[2] - s[0] + 'A' - 'W' + 3) % 3 ) + s[2] - 'W';
    }
    return res;
}

int part_2(vector<string> input) {
    int res = 0;
    int win;

    for (string s : input) {
        win = s[2] - 'X';
        res += 3 * win + ((s[0] - 'A' + win + 2) % 3) + 1;
    }
    return res;
}

int main() {
    
    vector<string> input;
    int score;

    input = read_file();

    score = part_1(input);
    std::cout << score << '\n';

    score = part_2(input);
    std::cout << score << '\n';

    return 0;
}