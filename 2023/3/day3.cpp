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

void check_adjacent(bool* res, int length, int width, vector<string> input) {
    char c;

    std::fill_n(res, length * width, false);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            c = input[i][j];
            if (!isdigit(c) && c != '.') {
                for (int i1 = max(0, i-1); i1 < min(length, i+2); i1++) {
                    for (int j1 = max(0, j-1); j1 < min(width, j+2); j1++) {
                        res[i1*width + j1] = true;
                    }
                }
            }
        }
    }
}

int part1(vector<string> input) {
    int res = 0;
    int length = input.size();
    int width = input[0].length();
    bool adjacent[length * width];
    string read = "";
    bool isdig;
    bool checked = false;
    char c;

    check_adjacent(adjacent, length, width, input);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            c = input[i][j];
            isdig = isdigit(c);
            if (isdig) {
                if (adjacent[i*width + j]) {
                    checked  = true;
                }
                read += c;
            }
            if (read != "" && (!isdig || j == width - 1)) {
                if (checked) {
                    res += stoi(read);
                }
                read = "";
                checked = false;
            }
        }
        
    }
    return res;
}

void check_adjacent_2(int* res, int length, int width, vector<string> input) {
    char c;

    std::fill_n(res, length * width, -1);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            c = input[i][j];
            if (c == '*') {
                for (int i1 = max(0, i-1); i1 < min(length, i+2); i1++) {
                    for (int j1 = max(0, j-1); j1 < min(width, j+2); j1++) {
                        res[i1*width + j1] = i*width + j;
                    }
                }
            }
        }
    }
}

int part2(vector<string> input) {
    int res = 0;
    int length = input.size();
    int width = input[0].length();
    int adjacent[length * width];
    int values[length * width * 3];
    string read = "";
    bool isdig;
    int checked = -1;
    char c;
    int k, index;

    check_adjacent_2(adjacent, length, width, input);
    std::fill_n(values, length * width * 3, 1);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            c = input[i][j];
            isdig = isdigit(c);
            if (isdig) {
                if (adjacent[i*width + j] != -1) {
                    checked  = adjacent[i*width + j];
                }
                read += c;
            }
            if (read != "" && (!isdig || j == width - 1)) {
                if (checked != -1) {
                    k = 0;
                    while (k < 3 && values[checked * 3 + k] != 1) {
                        k++;
                    }
                    if (k < 3) {
                        values[checked * 3 + k] = stoi(read);
                    }
                }
                read = "";
                checked = -1;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            c = input[i][j];
            index = i*width + j;
            if (c == '*' && values[index * 3 + 2] == 1 && values[index * 3 + 1] != 1) {
                res += values[index * 3] * values[index * 3 + 1];
            }
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