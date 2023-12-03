#include "boyer_moore.h"

BoyerMoore::BoyerMoore(std::string& userInput){
    // Constructor
    this->pattern = userInput;
    this->patternLength = pattern.length();
    good_suffix_compute();
    bad_char_compute();
}

void BoyerMoore::search(std::string& givenText) { 
    int textLength = givenText.length();

    // Below finds all matches within the given text and adds it to a list (vector) of indexes
    int i = 0;
    while (i <= textLength - patternLength) {
        int j = patternLength - 1;
        while (j >= 0 && pattern[j] == givenText[i + j]) {
            --j;
        }if (j < 0) {
            // if J is < 0, then that means a pattern was found within the text
            // index is then pushed into vector
            indexes.push_back(i);
            i += 1;
        } else {
            // Calculate shift and shifts by the larger value
            int badCharShift = badCharTable[givenText[i + j]] - (patternLength - 1 - j);
            int goodSuffixShift = goodSuffixTable[j + 1];
            i += shiftCalc(badCharShift, goodSuffixShift);
        }
    }
}

void BoyerMoore::bad_char_compute(){ // Computes bad character table (skip table)
     int patternLength = pattern.length();
    badCharTable.resize(256, patternLength); // Initialize with default shift value

    // Below is used to compute values for the bad character Table
    // Bad character table is table that determines how big of a shift to make if there is a mismatch between the text & pattern
    for (int i = 0; i < patternLength - 1; ++i) {
        badCharTable[pattern[i]] = patternLength - 1 - i;
    }
}

void BoyerMoore::good_suffix_compute(){ // Comutes the good suffix table (skip table)
    int patternLength = pattern.length();
    goodSuffixTable.resize(patternLength + 1, patternLength); // Initialize with default shift value

    // Below is used to compute values for the suffix Table
    // Good suffix table computes common patterns within the text/pattern itself and shifts by those patterns
    for (int i = patternLength - 1; i >= 0; --i) {
        int suffixLen = 0;
        while (suffixLen <= i && pattern[i - suffixLen] == pattern[patternLength - 1 - suffixLen]) {
            ++suffixLen;
            goodSuffixTable[suffixLen] = i - suffixLen + 1;
        }
    }

}

int BoyerMoore::shiftCalc(int a, int b){
    // Compare badCharTable and goodSuffixTable value to see which is higher, and returns the higher of the two
    // This is used to determine how many characters to skip
    return std::max(a, b);
}

// Print out the indexes where the pattern can be found
void BoyerMoore::printResults(){
    if(indexes.size() > 1){
        std::cout << indexes.size() << " Matches found at indexes: ";
        for(int i = 0; i < indexes.size(); i++){
            if(i != indexes.size()-1){
            std::cout << indexes[i] << ", ";
            }else{
                std::cout << indexes[i] << std::endl;;
            }
        }
    }else if(indexes.size() == 1){
        std::cout << indexes.size() << " Match found at index: " << indexes[0] << std::endl;
    }else{
        std::cout << "No match found in text.";
    }
}
