#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

int part1(vector<string> input) {
    int res = 0;
    char first, last;
    char read[2];

    for (string s : input) {
        first = 0;
        last = 0;

        for (char c : s) {
            if (isdigit(c)) {
                last = c;
                if (first == 0) {
                    first = c;
                }
            }
        }
        read[0] = first;
        read[1] = last;
        res += stoi(read);
    }

    return res;
}

int valueFromString(string s, map<string, int> valuemap ) {
    if (valuemap.count(s)) {
        return valuemap[s];
    } else {
        return 0;
    }
}

int part2(vector<string> input) {
    int res = 0;
    map<string, int> valuemap = {
        {"one", 1}, {"two", 2}, {"three", 3},
        {"four", 4}, {"five", 5}, {"six", 6},
        {"seven", 7}, {"eight", 8}, {"nine", 9}
    };
    string last3, last4, last5;
    char c;
    char read[1];
    int first, last, value;

    for (string s : input) {
        first = 0;
        last = 0;

        for (int i = 0; i < s.length(); i++) {
            value = 0;
            c = s[i];
            last3 = "";
            last4 = "";
            last5 = "";
            if (isdigit(c)) {
                read[0] = c;
                value = stoi(read);
            } else if (i >=2) {
                for (int j = 0; j < 3; j++) {
                    last3 += s[i + j - 2];
                }
                value = valueFromString(last3, valuemap);
                if (value == 0 && i>=3) {
                    for (int j = 0; j < 4; j++) {
                        last4 += s[i + j - 3];
                    }
                    value = valueFromString(last4, valuemap);  
                    if (value == 0 && i >= 4) {
                        for (int j = 0; j < 5; j++) {
                            last5+=s[i + j - 4];
                        }
                        value = valueFromString(last5, valuemap);                        
                    }
                }
            }

            if (value != 0) {
                last = value;
                if (first == 0) {
                    first = value;
                }
            }
        }
        res += 10 * first + last;
    }

    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();

    //std::cout << part1(input) << '\n';
    std::cout << part2(input) << '\n';

    return 0;
}