#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>    //  sort
#include <unordered_map>
using namespace std;


void readInput(std::string filename, vector<int> &list1, vector<int> &list2) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {    //  get the delimiter position
            try {
                int first = std::stoi(line.substr(0, spacePos));
                int second = std::stoi(line.substr(spacePos + 1));
                list1.push_back(first);
                list2.push_back(second);
            } catch (const std::exception &e) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }

    file.close();
}

//  Part 1
int getListDistance(vector<int> &list1, vector<int> &list2) {
    int listDistance = 0;
    
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    if (list1.size() != list2.size()) {
        std::cerr << "lists are different sizes\n";
    }

    for (int i = 0; i < list1.size(); i++) {
        listDistance += abs(list1[i] - list2[i]);
    }

    return listDistance;
}

//  Part 2
int getSimilarityScore(vector<int> &list1, vector<int> &list2) {
    int similarityScore = 0;
    unordered_map<int, int> map;    //  num : frequency

    //  Get frequency of each number in list 2
    for (int i = 0; i < list2.size(); i++) {
        map[list2[i]]++;
    }

    for (int i = 0; i < list1.size(); i++) {
        if (map.find(list1[i]) != map.end()) {  //  if doesn't exist, skip
            similarityScore += list1[i] * map[list1[i]];
        }
    }

    return similarityScore;
}

int main(int argc, char **argv) {
    vector<int> list1;
    vector<int> list2;

    readInput("input.txt", list1, list2);

    int result1 = getListDistance(list1, list2);
    int result2 = getSimilarityScore(list1, list2);

    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
    return 0;
}

//  wow didn't have a single compilation error and test cases passed on first try
//  used chatgpt just for the readFile function since I always forget file stream syntax