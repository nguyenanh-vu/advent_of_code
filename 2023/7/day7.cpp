#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
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

map<char, int> VALUESMAP = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},
    {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7},
    {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}  
};

int switch_hand_type(int high, int second) {
    switch(high) {
        case 1:
        //high card
            return 1;
        case 2:
        //pair 2, two pair 3
            return 1 + second;
        case 3:
        //three of a kind 4, full house 5
            return 3 + second;
        case 4:
            return 6;
        case 5:
            return 7;
        default:
            return 0;
    }
}

void hand_type(char* hands, int* types, int index) {
    int found[13];
    int high = 0, second = 0;

    std::fill_n(found, 13, 0);

    for (int i = 0; i < 5; i++) {
        found[VALUESMAP[hands[5 * index + i]]] ++;
    }

    for (int i : found) {
        if (i > high) {
            second = high;
            high = i;
        } else if (i > second) {
            second = i;
        }
    }

    types[index] = switch_hand_type(high, second);
}

void readline(string line, char* hands, int* bids, int index) {
    string read = "";

    for (int i = 0; i < 5; i++) {
        hands[5 * index + i] = line[i];
    }
    for (int i = 6; i < line.size(); i++) {
        read += line[i];
    }
    bids[index] = stoi(read);
}

//true if hand1 >= hand2
bool compare(char* hands, int* types, int index1, int index2) {
    if (types[index1] > types[index2]) {
        return true;
    } else if (types[index1] < types[index2]) {
        return false;
    } else {
        for (int i = 0; i < 5; i++) {
            if (VALUESMAP[hands[index1 * 5 + i]] > VALUESMAP[hands[index2 * 5 + i]]) {
                return true;
            } else if (VALUESMAP[hands[index1 * 5 + i]] < VALUESMAP[hands[index2 * 5 + i]]) {
                return false;
            }
        }
        return true;
    }
}

int part1(vector<string> input) {
    int res = 0;
    int len = input.size();
    char hands[len * 5];
    int types[len];
    int bids[len];
    int j;
    list<int> ordered = {};
    list<int>::iterator it;

    std::fill_n(hands, len*5, 0);
    std::fill_n(types, len, 0);
    std::fill_n(bids, len, 0);

    for (int i = 0; i < len; i++) {
        readline(input[i], hands, bids, i);
        hand_type(hands, types, i);
    }

    for (int i = 0; i < len; i++) {
        it = ordered.begin();
        while (it != ordered.end() && compare(hands, types, *it, i)) {
            ++it;
        }
        ordered.insert(it, i);
    }

    it = ordered.end();
    for (int i = 0; i < len; i++) {
        --it;
        res += (i + 1) * bids[*it];
    }

    return res;
}

void hand_type_2(char* hands, int* types, int index) {
    int found[13];
    int high = 0, second = 0;

    std::fill_n(found, 13, 0);

    for (int i = 0; i < 5; i++) {
        found[VALUESMAP[hands[5 * index + i]]] ++;
    }

    for (int i = 0; i < 13; i++) {
        if (i != 9) {
            found[i] += found[9];
        }
    }

    for (int i : found) {
        if (i > high) {
            second = high;
            high = i;
        } else if (i > second) {
            second = i;
        }
    }

    types[index] = switch_hand_type(high, second - found[9]);
}

//true if hand1 >= hand2
bool compare_2(char* hands, int* types, int index1, int index2) {
    int value1, value2;
    if (types[index1] > types[index2]) {
        return true;
    } else if (types[index1] < types[index2]) {
        return false;
    } else {
        for (int i = 0; i < 5; i++) {
            value1 = VALUESMAP[hands[index1 * 5 + i]];
            value2 = VALUESMAP[hands[index2 * 5 + i]];
            value1 = value1 == 9 ? -1 : value1;
            value2 = value2 == 9 ? -1 : value2;
            if (value1 > value2) {
                return true;
            } else if (value1 < value2) {
                return false;
            }
        }
        return true;
    }
}

int part2(vector<string> input) {
    int res = 0;
    int len = input.size();
    char hands[len * 5];
    int types[len];
    int bids[len];
    int j;
    list<int> ordered = {};
    list<int>::iterator it;

    std::fill_n(hands, len*5, 0);
    std::fill_n(types, len, 0);
    std::fill_n(bids, len, 0);

    for (int i = 0; i < len; i++) {
        readline(input[i], hands, bids, i);
        hand_type_2(hands, types, i);
    }

    for (int i = 0; i < len; i++) {
        it = ordered.begin();
        while (it != ordered.end() && compare_2(hands, types, *it, i)) {
            ++it;
        }
        ordered.insert(it, i);
    }

    it = ordered.end();
    for (int i = 0; i < len; i++) {
        --it;
        res += (i + 1) * bids[*it];
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