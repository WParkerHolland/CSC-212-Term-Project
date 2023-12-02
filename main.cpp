#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "rabin_karp.h"

bool isValidAlgorithm(std::string& algorithm) {
    return algorithm == "Booyer Moore" || algorithm == "Rabin Karp" || algorithm == "both" || algorithm == "run a benchmark";
}

void processAlgorithm(std::string& algorithm) {
    do {
        std::cout << "Please enter what you would like to run. Your choices are: Booyer Moore, Rabin Karp, both, or run a benchmark" << std::endl;
        std::cin >> algorithm;

        if (!isValidAlgorithm(algorithm)) {
            std::cout << "Invalid algorithm. Please check your spelling and spacing." << std::endl;
        }

    } while (!isValidAlgorithm(algorithm));
}

int main(int argc, char* argv[]) {
    
    std::string result;
    std::string secondResult;
    std::string algorithm;

    float benchmarkResult;

    std::ifstream inputFile(argv[1]);

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

    TwoWayQ twoWayQueue;
    if (algorithm == "Booyer Moore"){
        
    }
    else if(algorithm == "Rabin Karp"){
        std::string targetString;
        std::cout << "Enter the target string: ";
        std::cin >> targetString;
        
        std::vector<int>* rabinKarpResult = twoWayQueue.rabin_karp(argv[1], targetString);
        delete rabinKarpResult;
    }
    else if(algorithm == "both"){
        
    }
    else if(algorithm == "run a benchmark"){

    }

    return 0;
}
