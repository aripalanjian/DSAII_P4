#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP
#include "bin.hpp"

class Heuristic{
    Bin* bins;
    double* data;
    int capacity;
    int size;

public:
    Heuristic(int capacity, double data[]);
    ~Heuristic();

    bool firstHelper(int index);
    void firstFit();
    void nextFit();
    void bestFit();

    void getSnapshot();

    int getSize(){return size;}
    double dataAt(int index){return data[index];}
};

#endif