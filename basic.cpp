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

int part1(vector<string> input) {
    int res = 0;

    return res;
}

int part2(vector<string> input) {
    int res = 0;

    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();

    //std::cout << part1(input) << endl;
    //std::cout << part2(input) << endl;

    return 0;
}