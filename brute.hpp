#ifndef BRUTE_HPP
#define BRUTE_HPP

#include <time.h>


class Brute{
    int size; //Number of data points
    int minBins;
    long int nFact = 1;

    double* data;
    double* bestArr;

    time_t computationTimeS;
    long computationTimeNS;

    void calculateFactorial();    
    void swap(int i, int j);
    void perm1(double s[]);
    void packBins();
    
    void printS(double s[]);
public:
    Brute(double values[],int size);
    ~Brute();
    void run();
    double* getOptimal(){return bestArr;}
    time_t getComputationTimeS(){return computationTimeS;}
    long getComputationTimeNS(){return computationTimeNS;}
};

#endif