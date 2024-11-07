#include <iostream>
#include <fstream>
#include <string.h>
#include "bin.hpp"
#include "maxHeap.hpp"
#include "heuristic.hpp"
#include "brute.hpp"

#define MAX_BIN_SIZE 1.0

bool debug = false;

void run(int size, double* onlineValues, MaxHeap<double>& offlineValues){
    // Brute Force Optimal Approach
    Brute brute(onlineValues, size);
    brute.run();
    Heuristic optimal(size, brute.getOptimal());
    std::cout << "Optimal:\n";
    optimal.getSnapshot();

    //Online Tests
    Heuristic onlineFirst(size, onlineValues);
    Heuristic onlineNext(size, onlineValues);
    Heuristic onlineBest(size, onlineValues);
    onlineFirst.firstFit();
    onlineNext.nextFit();
    onlineBest.bestFit();

    //Offline Tests(Use same packing methods as online but with the data set sorted in descending order)
    double offlineData[size];
    for (int i = 0; i < size; i++){
        offlineData[i] = offlineValues.pop();
    }

    Heuristic offlineFirst(size, offlineData);
    Heuristic offlineBest(size, offlineData);
    offlineFirst.firstFit();
    offlineBest.bestFit();

    std::cout << "Online First Fit:\n";
    onlineFirst.getSnapshot();
    std::cout << "Online Next Fit:\n";
    onlineNext.getSnapshot();
    std::cout << "Online Best Fit:\n";
    onlineBest.getSnapshot();

    std::cout << "Offline First Fit:\n";
    offlineFirst.getSnapshot();
    std::cout << "Offline Best Fit:\n";
    offlineBest.getSnapshot();

}

int main(int argC, char** argV){
    if (argC>1){
        std::cout << "CMD line args: ";
        for (int i = 1; i < argC; i++){
            if (strcmp(argV[i], "-debug") == 0 || strcmp(argV[i], "-d") == 0 || strcmp(argV[i], "-Debug") == 0){
                debug = true;
            }
            std::cout << argV[i] << " ";
        }
        std::cout << "\n";
    }

    //Read Data from file
    const char* filename = "items.txt";
    std::ifstream file(filename);

    //Initialize read file values
    int size = 0;
    double value = 0;

    file >> size;
    double onlineValues[size];
    for (int i = 0; i < size; i++){
        file >> value;
        if (value - MAX_BIN_SIZE < 0){
            onlineValues[i] = value;
        }
    }
    file.close();

    MaxHeap offlineValues(onlineValues, size);

    if (debug){
        std::cout << "Online Values: ";
        for (int i = 0; i < size; i++){     
            std::cout << onlineValues[i] << " ";
        }    
        std::cout << "\n";
        
        std::cout << "Offline Values: ";
        offlineValues.print();
    }

    run(size, onlineValues, offlineValues);    

    return 0;
}

/*
TODO:
    Fix Best Fit
    Fix Brute
*/