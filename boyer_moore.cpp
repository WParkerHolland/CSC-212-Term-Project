#include "boyer_moore.h"
#include <algorithm>

BoyerMoore::BoyerMoore(std::string& userInput, std::string& fname){
    // Constructor
    this->pattern = userInput;
    std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower); // Helps with case insensitivity

    this->patternLength = pattern.length();

    readFile(fname);
    good_suffix_compute();
    bad_char_compute();
}

void BoyerMoore::readFile(std::string& fname){
    std::ifstream file(fname);
        std::string fileContent;
        std::string line;

        while (std::getline(file, line)) {
            fileContent += line;
        }

    file.close();
    this->givenText = fileContent;
    std::transform(givenText.begin(), givenText.end(), givenText.begin(), ::tolower);

    
    return;
}

void BoyerMoore::search() { 

    if(pattern.size() > givenText.size()){ // Return if pattern has more characters than text
        return;
    }else if (pattern.size() == 0 || givenText.size() == 0){ // return if either pattern or text has no characters
        return;
    }
    int textLength = givenText.length();

    // Below finds all matches within the given text and adds it to a list (vector) of indexes
    int i = 0;
    while (i <= textLength - patternLength) {
        int j = patternLength - 1;
        while (j >= 0 && std::tolower(pattern[j]) == std::tolower(givenText[i + j])) { // Using tolower function to impose case insensitivity when comparing
            --j;
        }if (j < 0) {
            // if J is < 0, then that means a pattern was found within the text
            // index is then pushed into vector
            indexes.push_back(i);
            i += patternLength; 
            
        } else {
            // Calculate shift and shifts by the larger value
            int badCharShift = badCharTable[givenText[i + patternLength - 1]];
            int goodSuffixShift = goodSuffixTable[patternLength - 1 - j];
            i += shiftCalc(badCharShift, goodSuffixShift);
        }
    }
}

void BoyerMoore::bad_char_compute(){ // Computes bad character table (skip table)
   int patternLength = pattern.length();
    badCharTable.resize(256, patternLength); // Initialize with default shift value for all characters
    
    for(int i = 0; i < patternLength; i++){
        badCharTable[i] = -1;
    }

    for (int i = 0; i < patternLength; i++) {
        badCharTable[(int) pattern[i]] = i;
    }
}

void BoyerMoore::good_suffix_compute() {
    int patternLength = pattern.length();
    goodSuffixTable.resize(patternLength + 1, patternLength); // Initialize with default shift value for the entire pattern

    int lastPrefixPosition = patternLength;

    // Compute the first part of the table: suffixes that are also prefixes
    for (int i = patternLength - 1; i >= 0; i--) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[patternLength - 1 - i + j]) {
            j--;
        }if (j == -1) {
            lastPrefixPosition = i + 1;
        }
        goodSuffixTable[patternLength - i - 1] = lastPrefixPosition - i + patternLength - 1;
    }
    // Compute the second part of the table: remaining suffixes
    for (int i = 0; i < patternLength - 1; ++i) {
        int suffixLen = 0;
        int j = i;
        int k = patternLength - 1;
        while (j >= 0 && pattern[j] == pattern[k]) {
            ++suffixLen;
            --j;
            --k;
        }
        goodSuffixTable[suffixLen] = patternLength - i - 1 + suffixLen;
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
        std::cout << indexes.size() << " Matches were found:\n" ;
        for(int i = 0; i < indexes.size(); i++){
            std::cout << "Match found at index: " << indexes[i] << std::endl;;
        }
    }else if(indexes.size() == 1){
        std::cout << "1 Match was found:\n" << "Match found at index: " << indexes[0] << std::endl;
    }else{
        std::cout << "No match found";
    }
}