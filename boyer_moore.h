#pragma once

#define BOYERMOORE
#ifndef BOYERMOORE

#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class BoyerMoore{
    public:
        BoyerMoore(std::string& userInput, std::string& fname);
        void search();
        std::string givenText;
        void printResults();
    private:
        int patternLength;
        std::vector<int> indexes;
        std::string pattern;
        
        std::vector<int> badCharTable;
        std::vector<int> goodSuffixTable;

        void readFile(std::string& fname);
        void bad_char_compute();
        void good_suffix_compute();
        int shiftCalc(int a, int b);
};