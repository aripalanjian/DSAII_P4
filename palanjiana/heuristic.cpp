/***************************************************************
  Student Name: Ari Palanjian
  File Name: heuristic.cpp
  Project 4

  Defines the member functions of class Heuristic
***************************************************************/
#include "heuristic.hpp"
#include <iostream>

Heuristic::Heuristic(int capacity, double values[]){
    this->capacity = capacity;
    bins = new Bin[capacity];
    data = new double[capacity];
    size = 0;

    for (int i = 0; i < capacity; i++){
        data[i] = values[i];
    }
}

Heuristic::~Heuristic(){
    for(int i = 0; i < size; i++){
        while(!bins[i].isEmpty()){
            Item* tmp = bins[i].pop();
            delete tmp;
        }
    }
    delete[] bins;
    delete[] data;

}

bool Heuristic::firstHelper(int index){
    for(int j = 0; j < size; j++){
        if( bins[j].canFit(data[index]) ){
            bins[j].push(new Item(data[index]));
            return true;
        }
    }
    return false;
}

void Heuristic::firstFit(){
    //Identifying the first bin in the list of bins that can hold the current item. If none can, get a new bin and place it there.
    bins[size++].push(new Item(data[0]));
    for (int i = 1; i < capacity; i++){
        if (!firstHelper(i)) {
            bins[size++].push(new Item(data[i]));
        }
    }

}

void Heuristic::nextFit(){
    //If the current bin can hold the item, place it there. Otherwise, get a new bin and place the item in the new bin.
    bins[size++].push(new Item(data[0]));
    for (int i = 1; i < capacity; i++){
        if (bins[size - 1].canFit(data[i])){
            bins[size - 1].push(new Item(data[i]));
        } else {
            bins[size++].push(new Item(data[i]));
        }
    }
}

void Heuristic::bestFit(){
    /*Scan the list of bins and place the item in the bin that will be most full as a result of the item being placed there. 
     *If it does not fit in any of the bins so far, place it in a new bin.
     */
    bins[size++].push(new Item(data[0]));
    for (int i = 1; i < capacity; i++){
        double leastRemainingSpace = 1.0;
        int binIndexLRS = 0;
        for(int j = 0; j < size; j++){
            if( bins[j].canFit(data[i]) ){
                if (leastRemainingSpace - bins[j].remainingSpace(data[i]) > 0){
                    leastRemainingSpace = bins[j].remainingSpace(data[i]);
                    binIndexLRS = j;
                }
            }
        }
        if (binIndexLRS == 0 && !bins[binIndexLRS].canFit(data[i])) {
            bins[size++].push(new Item(data[i]));
            // size++;
        } else if (!bins[binIndexLRS].canFit(data[i])){
            bins[size++].push(new Item(data[i]));
        } else {
            bins[binIndexLRS].push(new Item(data[i]));
        }
    }
}

void Heuristic::getSnapshot() {
    for(int i = 0; i < size; i++){
        int binSize = bins[i].getSize();
        std::cout << "\tb" << i+1 << ": ";
        for(int j = 0; j < binSize; j++){
            Item* tmp = bins[i].pop();
            std::cout << tmp->getValue() << " ";
            delete tmp;
        }
        std::cout << "\n";
    }
}