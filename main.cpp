/***************************************************************
  Student Name: Ari Palanjian
  File Name: main.cpp
  Project 4

  Driver program for Project 4
***************************************************************/
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include "maxHeap.hpp"
#include "heuristic.hpp"
#include "brute.hpp"

#define MAX_BIN_SIZE 1.0

bool debug = false;

void printTable(int binsOptimal, int onFirst, int onNext, int onBest, int offFirst, int offBest){
    using std::cout; using std::endl; using std::setw; using std::left; using std::fixed;
    cout << std::string(50, '-') << endl;
    cout << "|" << setw(23) << left << "Policy" << "|" << setw(24) << left << "Total Bins Used" << "|" << endl;
    cout << "|" << std::string(23, '-') << "|" << std::string(24, '-') << "|" << endl;
    cout << "|" << setw(23) << left << "Optimal Solution" << "|" << setw(24) << left << binsOptimal << "|" << endl;
    cout << "|" << std::string(23, '-') << "|" << std::string(24, '-') << "|" << endl;
    cout << "|" << setw(23) << left << "Online Solution" << "|" << setw(24) << left << " " << "|" << endl;    
    cout << "|" << setw(23) << left << "  First Fit" << "|" << setw(24) << left << onFirst << "|" << endl;
    cout << "|" << setw(23) << left << "  Next Fit" << "|" << setw(24) << left << onNext << "|" << endl;
    cout << "|" << setw(23) << left << "  Best Fit" << "|" << setw(24) << left << onBest << "|" << endl;
    cout << "|" << std::string(23, '-') << "|" << std::string(24, '-') << "|" << endl;
    cout << "|" << setw(23) << left << "Offline Solution" << "|" << setw(24) << left << " " << "|" << endl; 
    cout << "|" << setw(23) << left << "  First Fit" << "|" << setw(24) << left << offFirst << "|" << endl;
    cout << "|" << setw(23) << left << "  Best Fit" << "|" << setw(24) << left << offBest << "|" << endl;
    cout << std::string(50, '-') << endl;
}

void run(int size, double* onlineValues, MaxHeap<double>& offlineValues){
    double offlineData[size];
    double optimalData[size];
    for (int i = 0; i < size; i++){
        offlineData[i] = offlineValues.pop();
    }

    for (int i = 0; i < size; i++){
        optimalData[i] = offlineData[size - 1 - i];
    }

    // Brute Force Optimal Approach
    Brute brute(optimalData, size);
    brute.run();
    Heuristic optimal(size, brute.getOptimal());
    optimal.bestFit();

    // //Online Tests
    Heuristic onlineFirst(size, onlineValues);
    Heuristic onlineNext(size, onlineValues);
    Heuristic onlineBest(size, onlineValues);
    onlineFirst.firstFit();
    onlineNext.nextFit();
    onlineBest.bestFit();

    //Offline Tests(Use same packing methods as online but with the data set sorted in descending order)
    Heuristic offlineFirst(size, offlineData);
    Heuristic offlineBest(size, offlineData);
    offlineFirst.firstFit();
    offlineBest.bestFit();

    printTable(optimal.getSize(), onlineFirst.getSize(), onlineNext.getSize(), onlineBest.getSize(), offlineFirst.getSize(), offlineBest.getSize());

    std::cout << "Optimal:\n";
    optimal.getSnapshot();
    if (debug){
        std::cout << "  Permutations: " << brute.getComputationTimeS() << "s to complete.\n";
        std::cout << "  Packing Bins: " << brute.getComputationTimeSPack() << "s to complete.\n";
    }
    
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
        if (value - MAX_BIN_SIZE <= 0){
            onlineValues[i] = value;
        }
    }
    file.close();

    MaxHeap<double> offlineValues(onlineValues, size);

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