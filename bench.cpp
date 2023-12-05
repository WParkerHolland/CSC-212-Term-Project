// TermProj / bench.cpp

#include "bench.h"
#include <iostream>
#include <ctime>
#include <vector>

double bench::benchRK(std::string& fileName, std::string& targetString) {

    clock_t startTime = clock(); // start clock
    TwoWayQ rabinKarpObj; // run rabin-karp
    rabinKarpObj.rabin_karp(fileName, targetString);
    clock_t endTime = clock(); // end clock
    double timeRK = double(endTime - startTime) / CLOCKS_PER_SEC; // calculate seconds

    std::cout << "Rabin-Karp Execution Time: " << timeRK << " seconds" << std::endl; // output time
    return timeRK;
}

double bench::benchBM(std::string& fileName, std::string& targetString) {

    clock_t startTime = clock(); // start clock
    BoyerMoore boyerMooreObj(fileName); // run boyer-moore
    boyerMooreObj.search(targetString);
    clock_t endTime = clock(); // end clock
    double timeBM = double(endTime - startTime) / CLOCKS_PER_SEC; // calculate seconds

    std::cout << "Boyer-Moore Execution Time: " << timeBM << " seconds" << std::endl; // output time
    return timeBM;
}