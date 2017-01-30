#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

std::vector< size_t > handleRow(std::string line) {
    std::vector< size_t > row;
    size_t j, k, minimum_count;
    size_t base_count = 0;
    bool done;
    for (j = 0; j < line.length(); j++) {
        auto symbol = line.at(j);
        done = false;
        for (k = 0; k < j; k++) {
            if (symbol == line.at(k)) {
                minimum_count = row.at(k);
                done = true;
                break;
            }
        }
        if (!done) {
            if (j == 0) {
                // First number cannot be 0.
                minimum_count = 1;
            } else {
                minimum_count = base_count;
                base_count++;
                if (base_count == 1) {
                    // 1 is already taken, jump over.
                    base_count++;
                }
            }
        }
        row.push_back(minimum_count);
    }
    auto base = base_count < 2 ? 2 : base_count; // Base must be atleast 2
    row.push_back(base); // save base as last element
    return row;
}

std::vector< std::vector< size_t > > readFile(std::string filename) {
    std::vector< std::vector< size_t > > rows;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return rows;
    }
    std::string temp, line;
    getline(file, temp);
    size_t count = stoi(temp);
    for (size_t i = 0; i < count; i++) {
        std::getline(file, line);
        rows.push_back(handleRow(line));
    }
    file.close();
    return rows;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Specify input file." << std::endl;
        return 1;
    }
    auto rows = readFile(argv[1]);
    for (size_t i = 0; i < rows.size(); i++) {
        uint64_t sum = 0, power = 0;
        auto base = rows.at(i).back();
        for (auto j = rows.at(i).size() - 2; j != -1; j--) {
            auto number = rows.at(i).at(j);
            sum += number * std::pow(base, power);
            power++;
        }
        std::cout << "Case #" << i + 1 << ": " << sum << std::endl;
    }
}
