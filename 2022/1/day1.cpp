#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

std::vector<int> read_file() {
    string line;
    std::vector<int> res = {0};
    int number;

    fstream file("./input");

    if (file.is_open()) {
        while(std::getline(file, line)) {
            if (line.empty()) {
                res.push_back(0);
            } else {
                res[res.size() - 1] += stoi(line);
            }
        }
    }
    file.close();
    return res;
}

int find_max(std::vector<int> input) {
    int res = 0;

    for (int i : input) {
        if (i > res) {
            res = i;
        }
    }
    return res;
}

int main() {
    int max;
    int size;

    std::vector<int> input = read_file();

    max = find_max(input);
    std::cout << max << '\n';

    std::sort(input.begin(), input.end());
    size = input.size();
    std::cout << input[size-1] + input[size-2] + input[size-3] << '\n';

    return 0;
}