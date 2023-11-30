
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool isValidAlgorithm(const std::string& algorithm) {
    return algorithm == "Booyer Moore" || algorithm == "Rabin Karp";
}

void processAlgorithm(std::string& algorithm) {
    do {
        std::cout << "Enter the name of the algorithm you would like to use, Booyer Moore, or Rabin Karp" << std::endl;
        std::cin >> algorithm;

        if (!isValidAlgorithm(algorithm)) {
            std::cout << "Invalid algorithm. Please enter either 'Booyer Moore' or 'Rabin Karp'." << std::endl;
        }

    } while (!isValidAlgorithm(algorithm));
}

int main(int argc, char* argv[]) {
    
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

    return 0;
}
