#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
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

void add_value(int* res, string value, string read) {
    int v = stoi(value);
    if (read == "blue" && v > res[1]) {
        res[1] = v;
    } else if (read == "red" && v > res[2]) {
        res[2] = v;
    } else if (read == "green" && v > res[3]) {
        res[3] = v;
    }
}

void parse_line(string line, int* res) {
    // res[0] = game no, res[1] = blue, res[2] = red, res[3] = green
    std::fill_n(res, 4, 0);
    string read = "";
    string intread = "";
    int value = 0;
    char c;

    for (int i = 0; i < line.length(); i++) {
        c = line[i];
        if (isdigit(c)) {
            intread += c;
            read = "";
        } else if (c == ':') {
            res[0] = stoi(intread);
            intread = "";
            read = "";
        } else if (c == ',' || c == ';') {
            add_value(res, intread, read);
            value = 0;
            intread = "";
            read = "";
        } else if (c != ' ') {
            read += c;
            if (i == line.length() - 1) {
                add_value(res, intread, read);
                value = 0;
                intread = "";
                read = "";
            }
        } 
    }
}


int part1(vector<string> input) {
    int res = 0;
    int parsed[4] = {0,0,0,0};
    int ok[3] = {14,12,13};
    bool possible;

    for (string line : input) {
        parse_line(line, parsed);
        possible = true;
        for (int i = 0; i < 3; i++) {
            if (parsed[i+1] > ok[i]) {
                possible = false;
            }
        }
        if (possible) {
            res += parsed[0];
        }
    }
    return res;
}

int part2(vector<string> input) {
    int res = 0;
    int parsed[4] = {0,0,0,0};

    for (string line : input) {
        parse_line(line, parsed);

        res += parsed[1] * parsed[2] * parsed[3];
    }
    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();
    //part1(input);
    std::cout << part1(input) << '\n';
    std::cout << part2(input) << '\n';

    return 0;
}