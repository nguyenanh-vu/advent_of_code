#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

vector<unsigned long long> read_int_line(string line) {
    string read = "";
    vector<unsigned long long> res = {};
    int i;

    for (char c : line) {
        if (isdigit(c)) {
            read += c;
        } else if (read != "") {
            res.push_back(stoul(read));
            i++;
            read  = "";
        }
    }
    if (read != "") {
        res.push_back(stoul(read));
    }
    return res;
}

void parse_entry(vector<vector<unsigned long long>>* res, vector<string> input) {
    int phase = 0;
    string toread;
    map<string, int> phases = {
        {"seed-to-soil map:", 1},
        {"soil-to-fertilizer map:", 2},
        {"fertilizer-to-water map:", 3},
        {"water-to-light map:", 4},
        {"light-to-temperature map:", 5},
        {"temperature-to-humidity map:", 6},
        {"humidity-to-location map:", 7}
    };

    for (string line : input) {
        if (line.substr(0, 6) == "seeds:") {
            res[0].push_back(read_int_line(line.substr(6)));
            phase  = 1;
        } else if (phases.count(line)) {
            phase = phases[line];
        } else if (line != "") {
            res[phase].push_back(read_int_line(line));
        }
    }
}

unsigned long long compute_map(vector<vector<unsigned long long>> phase_map, unsigned long long in) {
    int line1;
    for (vector<unsigned long long> line : phase_map) {
        line1 = line[1];
        if (in >= line1 && in < line1 + line[2]) {
            return in + line[0] - line1;
        }
    } 
    return in;
}

unsigned long long part1(vector<string> input) {
    unsigned long long res = -1;
    unsigned long long processing;
    vector<vector<unsigned long long>> parsed[] = { {}, {}, {}, {}, {}, {}, {}, {}};

    parse_entry(parsed, input);

    for (unsigned long long i : parsed[0][0]) {
        processing = i;
        for (int j = 1; j < 8; j++) {
            processing = compute_map(parsed[j], processing);
        }
        if (res == -1 || processing < res) {
            res = processing;
        }
    }

    return res;
}

vector<vector<unsigned long long>> compute_range(vector<vector<unsigned long long>> phase_map, vector<unsigned long long> in) {
    vector<vector<unsigned long long>> queue = { in };
    vector<unsigned long long> totreat;
    vector<unsigned long long> phase;
    vector<vector<unsigned long long>> out = {};
    bool found;

    while (queue.size() > 0) {
        totreat = queue.back();
        queue.pop_back();
        found = false;
        for (int i = 0; i < phase_map.size() && !found; i++) {
            phase = phase_map[i];
            if (totreat[0] < phase[1] && totreat[0] + totreat[1] > phase[1]) {
                if (totreat[0] + totreat[1] <= phase[1] + phase[2]) {
                    out.push_back( {phase[0], totreat[0] + totreat[1] - phase[1]} );
                    queue.push_back( {totreat[0], phase[1] - totreat[0]} );
                    found = true;
                } else {
                    out.push_back( {phase[0], phase[2]} );
                    queue.push_back( {totreat[0], phase[1] - totreat[0]} );
                    queue.push_back( {phase[1] + phase[2], totreat[0] + totreat[1] - phase[1] - phase[2]} );
                    found = true;
                }
            } else if ( totreat[0] >= phase[1] && totreat[0] < phase[1] + phase[2]) {
                if (totreat[0] + totreat[1] <= phase[1] + phase[2]) {
                    out.push_back( {totreat[0] + phase[0] - phase[1] , totreat[1]} );
                    found = true;
                } else {
                    out.push_back( {totreat[0] + phase[0] - phase[1] , phase[1] + phase[2] - totreat[0]} );
                    queue.push_back( {phase[1] + phase[2], totreat[0] + totreat[1] - phase[1] - phase[2]} );
                    found = true;
                }
            }
        }
        if (!found) {
            out.push_back(totreat);
        }
    }
    return out;
}

unsigned long long part2(vector<string> input) {
    unsigned long long res = -1;
    unsigned long long processing;
    vector<vector<unsigned long long>> parsed[] = { {}, {}, {}, {}, {}, {}, {}, {}};
    vector<unsigned long long> entries;
    vector<vector<unsigned long long>> queuein = {};
    vector<vector<unsigned long long>> queueout = {};
    vector<vector<unsigned long long>> out;

    parse_entry(parsed, input);

    for (int i = 0; i < parsed[0][0].size() / 2; i++) {
        queuein.push_back( {parsed[0][0][2 * i], parsed[0][0][2 * i + 1]} );
    }

    for (int i = 1; i < 8; i++) {
        for (vector<unsigned long long> in : queuein) {
            out = compute_range(parsed[i], in);
            for (vector<unsigned long long> o : out) {
                queueout.push_back(o);
            }
        }
        queuein.clear();

        for (vector<unsigned long long> in : queueout) {
            queuein.push_back(in);
        }
        queueout.clear();
    }

    for (vector<unsigned long long> in : queuein) {
        if (res == -1 || in[0] < res) {
            res = in[0];
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