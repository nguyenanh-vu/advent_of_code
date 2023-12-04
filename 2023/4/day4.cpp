#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

void parse_line(string s, vector<int>* res) {
    char c;
    string read = "";
    int part = 0;
    for (int i = 0; i < 3; i++) {
        res[i].clear();
    }

    for (int i = 0; i < s.length(); i++) {
        c = s[i];
        if (isdigit(c)) {
            read += c;
        } else if (c == '|' || c == ':') {
            if (read != "") {
                res[part].push_back(stoi(read));
                read = "";
            }
            part += 1;
        } else if (c == ' ' && read != "") {
            res[part].push_back(stoi(read));
            read = "";
        }
    }
    res[part].push_back(stoi(read));
}

int part1(vector<string> input) {
    int res = 0;
    int score;
    bool found[100];
    vector<int> parsed[3] = { {}, {}, {} };

    for (string s : input) {
        score = 0;
        parse_line(s, parsed);
        std::fill_n(found, 100, false);

        for (int i : parsed[1]) {
            found[i] = true;
        }
        for (int i : parsed[2]) {
            if (found[i]) {
                score += 1;
            }
        }
        if (score > 0) {
            res += pow(2, score - 1);
        }
    }

    return res;
}

int score_line(vector<string> input, int line_number) {
    bool found[100];
    vector<int> parsed[3] = { {}, {}, {} };
    string line;
    int res = 0;
    
    
    std::fill_n(found, 100, false);

    line = input[line_number];
    parse_line(line, parsed);

    for (int i : parsed[1]) {
        found[i] = true;
    }
    for (int i : parsed[2]) {
        if (found[i]) {
            res += 1;
        }
    }

    return res;
}

int part2(vector<string> input) {
    int res = 0;
    int size = input.size();
    int cards[size];
    int cardsi;
    std::fill_n(cards, size, 1);

    for (int i = 0; i < input.size(); i++) {
        cardsi = cards[i];
        res += cardsi;
        for (int j = 1; j <= score_line(input, i); j++) {
            cards[i + j] += cardsi;
        }
    }

    return res;
}

int main() {
    
    vector<string> input;

    input = read_file();

    std::cout << part1(input) << endl;
    std::cout << part2(input) << endl;

    return 0;
}