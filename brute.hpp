/***************************************************************
  Student Name: Ari Palanjian
  File Name: brute.hpp
  Project 4

  Defines the class Brute which computes the optimal amount of
    bins to hold the items in the data set.

    *Note: this will only hold the first arrangement of bins
      that the permutation finds to need less bins than the
      previous minimum number of bins. 
***************************************************************/
#ifndef BRUTE_HPP
#define BRUTE_HPP

#include <time.h>


class Brute{
    int size; //Number of data points
    int minBins;
    long int nFact = 1;
    int count = 0;

    double* data;
    double* best;
    double** permutations;

    time_t computationTimeS;
    long computationTimeNS;
    
    time_t computationTimeSPack;
    long computationTimeNSPack;

    void calculateFactorial();    
    void swap(int i, int j);
    void perm1(double s[]);
    int modNextFit(double s[]);
    
    void printS(double s[]);
public:
    Brute(double values[],int size);
    ~Brute();
    void run();
    double* getOptimal(){return best;}
    time_t getComputationTimeS(){return computationTimeS;}
    long getComputationTimeNS(){return computationTimeNS;}
    time_t getComputationTimeSPack(){return computationTimeSPack;}
    long getComputationTimeNSPack(){return computationTimeNSPack;}
};

#endif