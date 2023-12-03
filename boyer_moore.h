#pragma once

#define BOYERMOORE
#ifndef BOYERMOORE

#endif

#include <iostream>
#include <string>
#include <vector>

class BoyerMoore{
    public:
        BoyerMoore(std::string& userInput);
        void search(std::string& givenText);
        void printResults();
    private:
        int patternLength;
        std::vector<int> indexes;
        std::string pattern;
        std::string givenText;

        std::vector<int> badCharTable;
        std::vector<int> goodSuffixTable;

        void bad_char_compute();
        void good_suffix_compute();
        int shiftCalc(int a, int b);
};
