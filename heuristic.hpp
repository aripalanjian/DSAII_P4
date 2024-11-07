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
    void onlineFirst();
    void onlineNext();
    void onlineBest();

    void offlineFirst();
    void offlineBest();

    void getSnapshot();

    int getSize(){return size;}
};

#endif