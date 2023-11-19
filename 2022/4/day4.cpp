#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

void read_pair_from_string(string s, int* read_to) {
    std::fill_n(read_to, 4, 0);
    int reading = 0;
    string acc = "";

    for (char c : s) {
        if ( c == '-' || c == ',' ) {
            read_to[reading] = stoi(acc);
            reading ++;
            acc = "";
        } else {
            acc += c;
        }
    }
    read_to[reading] = stoi(acc);
}

int part_1(vector<string> input) {
    int res = 0;
    int read [4];

    for (string s : input) {
        read_pair_from_string(s, read);
        if ( (( read[0] <= read[2]) && (read[1] >= read[3]) ) ||  ( (read[0] >= read[2]) && (read[1] <= read[3]) ) ) {
            res += 1;
        }
    }

    return res;
}

int part_2(vector<string> input) {
    int res = 0;
    int read [4];

    for (string s : input) {
        read_pair_from_string(s, read);
        if ( (( read[0] <= read[2]) && (read[1] >= read[2]) ) ||  ( (read[0] >= read[2]) && (read[0] <= read[3]) ) ) {
            res += 1;
        }
    }

    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();

    std::cout << part_1(input) << '\n';
    std::cout << part_2(input) << '\n';

    return 0;
}