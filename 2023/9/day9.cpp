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

vector<int> readline(string line) {
    vector<int> res = {};
    string read = "";

    for (char c : line) {

        if (isdigit(c) || c == '-') {
            read += c;
        } else if (read != "") {
            res.push_back(stoi(read));
            read = "";
        }
    }
    if (read != "") {
        res.push_back(stoi(read));
    }

    return res;
}

vector<int> diff(vector<int> line) {
    vector<int> res = {};

    for (int i = 0; i < line.size() - 1; i++ ) {
        res.push_back(line[i+1] - line[i]);
    }

    return res;
}

bool allzero(vector<int> line) {
    for (int i : line) {
        if (i) {
            return false;
        }
    }
    return true;
}

long part1(vector<string> input) {
    long res = 0;
    long read;
    vector<vector<int>> grid = {};
    vector<int> lastread;
    
    for (string s : input) {
        grid.clear();

        lastread = readline(s);
        grid.push_back(lastread);

        while (!allzero(lastread)) {
            lastread = diff(lastread);
            grid.push_back(lastread);
        }

        read = 0;

        for (int i = grid.size() - 2; i >= 0; i--) {
            read += grid[i].back();
        }
        res += read;
    }

    return res;
}

int part2(vector<string> input) {
    long res = 0;
    long read;
    vector<vector<int>> grid = {};
    vector<int> lastread;
    
    for (string s : input) {
        grid.clear();

        lastread = readline(s);
        grid.push_back(lastread);

        while (!allzero(lastread)) {
            lastread = diff(lastread);
            grid.push_back(lastread);
        }

        read = 0;

        for (int i = grid.size() - 2; i >= 0; i--) {
            read = grid[i][0] - read;
        }
        //std::cout << read << endl;
        res += read;
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