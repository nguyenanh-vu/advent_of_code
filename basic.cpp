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

int main() {
    
    vector<string> input;

    input = read_file();

    return 0;
}