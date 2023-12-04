// TermProj / bench.cpp

#include "bench.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"
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

void bench::graph(std::string& fileName, std::string& targetString) {
    RGBABitmapImageReference imageReference = *CreateRGBABitmapImageReference();
    StringReference errorMessage = *new StringReference();
    ScatterPlotSettings settings = *GetDefaultScatterPlotSettings();
//    settings.xLabel = "X axis".toCharArray();
//    settings.yLabel = "Y axis".toCharArray();

    std::vector<double> xs;
    std::vector<double> RKys;
    std::vector<double> BMys;

    for (int i = 1; i < 7; i++) {
        xs.push_back(i);

        std::string temp = "example";
        temp += i;
        temp += ".txt";
        RKys.push_back(benchRK(temp, targetString));
        BMys.push_back(benchBM(temp, targetString));
    }

    bool success = DrawScatterPlot(&imageReference, 600, 400, &xs, &RKys, &errorMessage);
    bool success2 = DrawScatterPlot(&imageReference, 600, 400, &xs, &BMys, &errorMessage);

    if(success){
        std::vector<double>* pngdata = ConvertToPNG(imageReference.image);
        WriteToFile(pngdata, "plotTest.png");
        DeleteImage(imageReference.image);
    }

    if(success2){
        std::vector<double>* pngdata = ConvertToPNG(imageReference.image);
        WriteToFile(pngdata, "plotTest2.png");
        DeleteImage(imageReference.image);
    }
}