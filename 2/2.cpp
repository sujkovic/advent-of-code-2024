#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

std::vector<std::vector<int>> readFile(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<int>> data;

    if (!file) {
        std::cerr << "Error opening file " << filename << std::endl;
        return {};
    }

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<int> curLine;
        int num;

        while (lineStream >> num) {
            curLine.push_back(num);
        }

        if (!curLine.empty()) {
            data.push_back(curLine);
        }
    }

    file.close();
    return data;
}

int countSafeReports(std::vector<std::vector<int>> &reports) {
    int numSafeReports = 0;

    for (int i = 0; i < reports.size(); i++) {
        bool isIncreasing = true;
        bool isDecreasing = true;

        //  Check if increasing
        for (int j = 1; j < reports[i].size(); j++) {
            int cur = reports[i][j];
            int prev = reports[i][j - 1];
            int dif = abs(cur - prev);

            if (!(cur > prev && dif >= 1 && dif <= 3)) {
                isIncreasing = false;
                break;
            }
        }

        //  Check if decreasing
        for (int j = 1; j < reports[i].size(); j++) {
            int cur = reports[i][j];
            int prev = reports[i][j - 1];
            int dif = abs(cur - prev);

            if (!(cur < prev && dif >= 1 && dif <= 3)) {
                isDecreasing = false;
                break;
            }
        }

        if (isIncreasing || isDecreasing) {
            numSafeReports++;
        }
        else {
        }
    }

    return numSafeReports;
}


int main() {
    std::vector<std::vector<int>> data = readFile("input.txt");
    int result = countSafeReports(data);

    std::cout << result << std::endl;
    return 0;
}


//  Part 1 - 35 min (most of which was i accidentally initialized isDecreasing to false
//                   and also didnt read the second part of instructions w/ 1 <= dif <= 3)
//  Part 2 -