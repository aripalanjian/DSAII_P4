#include <iostream>
#include <fstream>
#include "bin.hpp"
#include "maxHeap.hpp"
#include "heuristic.hpp"

int main(int argC, char** argV){
    if (argC>1){
        std::cout << "CMD line args: ";
        for (int i = 1; i < argC; i++){
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
        onlineValues[i] = value;
    }
    file.close();

    std::cout << "Online Values: ";
    for (int i = 0; i < size; i++){     
        std::cout << onlineValues[i] << " ";
    }    
    std::cout << "\n";
    
    MaxHeap offlineValues(onlineValues, size);
    std::cout << "Offline Values: ";
    for(int i = 0; i < size; i++){
        std::cout << offlineValues.pop() << " ";
    }
    std::cout << "\n";

    Heuristic onlineFirst(size, onlineValues);
    Heuristic onlineNext(size, onlineValues);
    Heuristic onlineBest(size, onlineValues);
    onlineFirst.onlineFirst();
    onlineNext.onlineNext();
    onlineBest.onlineBest();
    std::cout << "Online First Fit:" << "\n";
    onlineFirst.getSnapshot();
    std::cout << "Online Next Fit:" << "\n";
    onlineNext.getSnapshot();
    std::cout << "Online Best Fit:" << "\n";
    onlineBest.getSnapshot();

    return 0;
}