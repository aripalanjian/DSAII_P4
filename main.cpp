#include <iostream>
#include <fstream>
#include "bin.hpp"

int main(int argC, char** argV){
    if (argC>1){
        std::cout << "CMD line args: ";
        for (int i = 1; i < argC; i++){
            std::cout << argV[i] << " ";
        }
        std::cout << "\n";
    }
    Bin values = Bin();

    //Read Data from file
    const char* filename = "items.txt";
    std::ifstream file("items.txt");
    int size = 0;
    double value = 0;
    file >> size;
    for (int i = 0; i < size; i++){
        file >> value;
        std::cout << "file good " << value << "\n";        
        Item* tmp = new Item(value);
        std::cout << "Pushing to bin...";
        values.push(tmp);
        std::cout << "complete\n";
    }
    file.close();

    for (int i = 0; i < size; i++){
        Item* val = values.pop();
        std::cout << val->getValue() << " ";
        delete val;
    }

    return 0;
}