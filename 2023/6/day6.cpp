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

vector<int> read_int_line(string line) {
    string read = "";
    vector<int> res = {};
    int i;

    for (char c : line) {
        if (isdigit(c)) {
            read += c;
        } else if (read != "") {
            res.push_back(stoi(read));
            i++;
            read  = "";
        }
    }
    if (read != "") {
        res.push_back(stoi(read));
    }
    return res;
}

int part1(vector<string> input) {
    int res = 1;
    int len, count;
    vector<int> times, distances;

    times = read_int_line(input[0]);
    distances = read_int_line(input[1]);
    len = times.size();

    for (int i = 0; i < len; i++) {
        count = 0;
        for (int j = 1; j < times[i]; j++) {
            if (j * (times[i] - j) > distances[i]) {
                count ++;
            }
        }
        res *= count;
    }

    return res;
}

long long read_line_single_int(string line) {
    string read = "";

    for (char c : line) {
        if (isdigit(c)) {
            read += c;
        }
    }
    return stoll(read);
}

int part2(vector<string> input) {
    long long time, distance;
    float delta;
    int up, down, deltafloor;

    time = read_line_single_int(input[0]);
    distance = read_line_single_int(input[1]);


    delta = pow( time * time - 4 * distance , 0.5);

    deltafloor = round(floor(delta));

    up = (time + deltafloor) / 2;
    down = (time - deltafloor) / 2;

    while (up * (time - up) > distance) {
        up ++;
    }

    while (down * (time - down) > distance) {
        down--;
    }
    return up - down - 1;
}

int main() {
    
    vector<string> input;

    input = read_file();

    std::cout << part1(input) << endl;
    std::cout << part2(input) << endl;

    return 0;
}