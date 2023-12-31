// TermProj / bench.h
#include "rabin_karp.h"
#include "boyer_moore.h"
#include <iostream>

#ifndef CSC212_BENCH_H
#define CSC212_BENCH_H


class bench {
private:

public:

    double benchRK(std::string& fileName, std::string& targetString);
    double benchBM(std::string& fileName, std::string& targetString);

};


#endif //CSC212_BENCH_H
