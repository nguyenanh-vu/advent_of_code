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

int value(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 27;
    } else if ('a' <= c && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return 0;
    }
}

int find_common_value(vector<string> list) {
    bool previous [52];
    bool found [52];
    std::fill_n(found, 52, 1);
    int v;

    for (string s : list) {
        std::copy(std::begin(found), std::end(found), std::begin(previous));
        std::fill_n(found, 52, 0);

        for (char c : s) {
            v = value(c) - 1;
            found[v] = previous[v];
        }

    }

    for (int i = 0; i < 52; i++) {
        if (found[i]) {
            return i + 1;
        }
    }

    return 0;
}

int part_1(vector<string> input) {
    vector<string> toTry;
    int res = 0;
    int half;

    for (string s : input) {
        half = s.size() / 2;
        toTry = { s.substr(0, half), s.substr(half, half) };
        res += find_common_value(toTry);
    }

    return res;
}

int part_2(vector<string> input) {
    vector<string> toTry;
    int res = 0;

    for (int i = 0; i < input.size(); i+= 3) {
        toTry = { input[i], input[i + 1], input[i + 2] };
        res += find_common_value(toTry);
    }

    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();
    std::cout << part_1(input) << '\n' ;
    
    std::cout << part_2(input) << '\n' ;

    return 0;
}