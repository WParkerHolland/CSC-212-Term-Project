// TermProj / bench.cpp

#include "bench.h"
#include <iostream>
#include <ctime>

void bench::benchRK(const std::string& fileName, const std::string& targetString) {

    clock_t startTime = clock(); // start clock
    TwoWayQ rabinKarpObj; // run rabin-karp
    clock_t endTime = clock(); // end clock
    double timeRK = double(endTime - startTime) / CLOCKS_PER_SEC; // calculate seconds

    std::cout << "Rabin-Karp Execution Time: " << timeRK << " seconds" << std::endl; // output time
}

void bench::benchBM(std::string& fileName, std::string& targetString) {

    clock_t startTime = clock(); // start clock
    BoyerMoore boyerMoore(fileName); // run boyer-moore
    boyerMoore.search(targetString);
    clock_t endTime = clock(); // end clock
    double timeBM = double(endTime - startTime) / CLOCKS_PER_SEC; // calculate seconds

    std::cout << "Boyer-Moore Execution Time: " << timeBM << " seconds" << std::endl; // output time
}