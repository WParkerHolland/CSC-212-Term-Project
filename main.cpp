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
    return algorithm == "BoyerMoore" || algorithm == "RabinKarp" || algorithm == "both" || algorithm == "benchmark";
}

void processAlgorithm(std::string& algorithm) {
    do {
        std::cout << "Please enter what you would like to run. Your choices are: Boyer Moore, Rabin Karp, both, or run a benchmark" << std::endl;
        std::cin >> algorithm;

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
    if (algorithm == "BoyerMoore"){
        std::string pattern;
        std::string boyerMoore_target;

        std::cout << "Enter desired search pattern" << std::endl;
        std::getline(std::cin, pattern);

        std::cout << "Enter the target string: " << std::endl;
        std::cin >> boyerMoore_target;

        BoyerMoore boyerMoore(pattern);

        boyerMoore.search(boyerMoore_target);
        boyerMoore.printResults();
    }
    else if(algorithm == "RabinKarp"){
        std::string targetString;
        std::cout << "Enter the target string: " << std::endl;
        std::cin >> targetString;

        std::vector<int>* rabinKarpResult = twoWayQueue.rabin_karp(argv[1], targetString);
        delete rabinKarpResult;
    }
    else if(algorithm == "both"){
        std::string targetString;
        std::string pattern;

        std::cout << "Enter target string" << std::endl;
        std::cin >> targetString;

        std::cout << "Enter desired search pattern (Boyer Moore)" << std::endl;
        std::cin >> pattern;


        std::vector<int>* rabinKarpResult = twoWayQueue.rabin_karp(argv[1], targetString);
        delete rabinKarpResult;

        BoyerMoore boyerMoore(pattern);

        boyerMoore.search(targetString);
        boyerMoore.printResults();
    }
    else if(algorithm == "benchmark"){
        std::string benchmark_targetString;
        std::cout << "Enter target string" << std::endl;
        std::cin >> benchmark_targetString;

        std::string temp = argv[1];


        std::cout << "test" << std::endl;
        double timeBM = benchmark.benchBM(temp, benchmark_targetString);
        std::cout << "test2" << std::endl;
        double timeRK = benchmark.benchRK(temp, benchmark_targetString);
        std::cout << "test3" << std::endl;
        benchmark.graph(temp, benchmark_targetString);
        // benchmark.graph(timeRK, timeBM, temp, benchmark_targetString);

    }

    return 0;
}