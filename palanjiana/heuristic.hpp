/***************************************************************
  Student Name: Ari Palanjian
  File Name: heuristic.hpp
  Project 4

  Defines the class Heuristic, the three heuristics developed
    in this class include First Fit, Next Fit, and Best Fit.
    Online and offline can utilize all methods, where online
    does not sort the list of data values and offline sorts
    them in descedning order.
***************************************************************/
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
    double* getData(){return data;}
};

#endif