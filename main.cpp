//this is a working concept, probably will change to something simpler, just due to the fact that the legislation websites are weird

//okay this just straight up doesnt work im gonna fix it tmr (11/29)


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

int main(){

    std::string algorithm;
    std::string websiteName;

    std::string websiteContents;

    std::cout << "Enter website name:" << std::endl;
        std::cin >> websiteName;

    try{
        std::ifstream webStream(websiteName);
        
        if(!webStream){
            throw std::runtime_error("Unable to open website");
        }

        std::ostringstream stringStream;

        //extracting contents of website
        stringStream << webStream.rdbuf();
        //converting contents of website to a string 
        websiteContents = stringStream.str();
    }
    catch(const std::exception& e){
        std::cerr << "Unknown error occurred, please try again" << e.what() << std::endl;
        return 1;
    }

    do {
    
        std::cout << "Enter the name of the algorithm you would like to use, Booyer Moore, or Rabin Karp" << std::endl;
        std::cin >> algorithm;

        if (algorithm == "Booyer Moore") {
            //run the booyer moore algorithm
            break;
        } else if (algorithm == "Rabin Karp") {
            //run rabin karp algorithm 
            break;
        } else {
            std::cout << "Invalid algorithm. Please enter either 'Booyer Moore' or 'Rabin Karp'." << std::endl;
        }
    } while (true); 


}