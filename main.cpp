#include <iostream>
#include <fstream>
#include "bin.hpp"
#include "maxHeap.hpp"
#include "heuristic.hpp"

bool debug = false;

void run(int size, double* onlineValues, MaxHeap<double>& offlineValues){

    Heuristic onlineFirst(size, onlineValues);
    Heuristic onlineNext(size, onlineValues);
    Heuristic onlineBest(size, onlineValues);
    onlineFirst.onlineFirst();
    onlineNext.onlineNext();
    onlineBest.onlineBest();

    Heuristic offlineFirst(size, offlineValues.getArray());
    Heuristic offlineBest(size, offlineValues.getArray());
    offlineFirst.onlineFirst();
    offlineBest.onlineBest();

    std::cout << "Online First Fit:" << "\n";
    onlineFirst.getSnapshot();
    std::cout << "Online Next Fit:" << "\n";
    onlineNext.getSnapshot();
    std::cout << "Online Best Fit:" << "\n";
    onlineBest.getSnapshot();

    std::cout << "Offline First Fit:" << "\n";
    offlineFirst.getSnapshot();
    std::cout << "Offline Best Fit:" << "\n";
    offlineBest.getSnapshot();

}

int main(int argC, char** argV){
    if (argC>1){
        std::cout << "CMD line args: ";
        for (int i = 1; i < argC; i++){
            if (argV[i] == "-debug" || argV[i] == "-d" || argV[i] == "-Debug"){
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
        onlineValues[i] = value;
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