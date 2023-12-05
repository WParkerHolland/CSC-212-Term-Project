#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "rabin_karp.h"
#include "boyer_moore.h"
#include "bench.h"

bool isValidAlgorithm(std::string& algorithm) {
    return algorithm == "boyer moore" || algorithm == "rabin karp" || algorithm == "both" || algorithm == "benchmark rabin karp" || algorithm == "benchmark boyer moore";
}

void processAlgorithm(std::string& algorithm) {
    do {
        std::cout << "Please enter what you would like to run. Your choices are: 'Boyer Moore', 'Rabin Karp', 'both', 'benchmark rabin karp', or 'benchmark boyer moore'" << std::endl;
        std::getline(std::cin, algorithm);

        std::transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);

        if (!isValidAlgorithm(algorithm)) {
            std::cout << "Invalid algorithm. Please check your spelling and spacing." << std::endl;
        }

    } while (!isValidAlgorithm(algorithm));
}

int main(int argc, char* argv[]) {
    
    std::string result;
    std::string secondResult;
    std::string algorithm;

    std::ifstream inputFile(argv[1]);
    std::string temp = argv[1];

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    //reading file into a string 
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();

    inputFile.close(); 

    processAlgorithm(algorithm);
    
    //optional
    //std::cout << "File Content: " << fileContent << std::endl;
    std::cout << "Selected Algorithm: " << algorithm << std::endl;
    
    bench benchmark;
    TwoWayQ twoWayQueue;
    if (algorithm == "boyer moore"){
        std::string pattern;
        std::string boyerMoore_target;

        std::cout << "Enter desired search pattern" << std::endl;
        std::getline(std::cin, pattern);

        BoyerMoore boyerMoore(pattern, temp);

        boyerMoore.search();
        boyerMoore.printResults();
    }
    else if(algorithm == "rabin karp"){
        std::string targetString;
        std::cout << "Enter the target string: " << std::endl;
        std::cin >> targetString;
        
        std::vector<int>* rabinKarpResult = twoWayQueue.rabin_karp(argv[1], targetString);
        
        if (rabinKarpResult != nullptr) {
            std::cout << "Matches found at positions:";
            for (int i = 0; i < rabinKarpResult->size(); i += 2) {
                std::cout << " (" << (*rabinKarpResult)[i] << ", " << (*rabinKarpResult)[i + 1] << ")";
            }
            std::cout << std::endl;
            delete rabinKarpResult;
        } else {
            std::cout << "No matches found." << std::endl;
        }
    }
    else if(algorithm == "both"){
        std::string targetString;
        std::string pattern;
    
        std::cout << "Enter target string (Rabin Karp)" << std::endl;
        std::cin >> targetString;

        std::cout << "Enter target string (Boyer Moore)" << std::endl;
        std::cin >> pattern;

        std::vector<int>* rabinKarpResult = twoWayQueue.rabin_karp(argv[1], targetString);

        if (rabinKarpResult != nullptr) {
            std::cout << "Matches found at positions:";
            for (int i = 0; i < rabinKarpResult->size(); i += 2) {
                std::cout << " (" << (*rabinKarpResult)[i] << ", " << (*rabinKarpResult)[i + 1] << ")";
            }
            std::cout << std::endl;
            delete rabinKarpResult;
        } else {
            std::cout << "No matches found." << std::endl;
        }
        
        BoyerMoore boyerMoore(pattern, temp);

        boyerMoore.search();
        boyerMoore.printResults();
    }
    else if(algorithm == "benchmark rabin karp"){
        std::string benchmark_targetStringRK;

        std::cout << "Enter target string (Rabin Karp)" << std::endl;
        std::cin >> benchmark_targetStringRK;

        benchmark.benchRK(temp, benchmark_targetStringRK);
    }
    else if(algorithm == "benchmark boyer moore"){
        std::string benchmark_targetStringBM;

        std::cout << "Enter target string (Boyer Moore)" << std::endl;
        std::cin >> benchmark_targetStringBM;

        benchmark.benchBM(temp, benchmark_targetStringBM);
    }

    return 0;
}
