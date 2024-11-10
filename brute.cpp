/***************************************************************
  Student Name: Ari Palanjian
  File Name: brute.cpp
  Project 4

  Defines the member functions of class Brute
***************************************************************/
#include "brute.hpp"
#include <iostream>

Brute::Brute(double values[],int size){
    this->size = size;
    this->minBins = size;
    data = new double[size];
    best = new double[size];
    
    for(int i =0; i < size; i++){
        data[i] = values[i];
    }
    calculateFactorial();
    permutations = new double*[nFact];
    permutations[count++] = data;
}

Brute::~Brute(){
    delete [] data;
    delete [] best;
}

void Brute::calculateFactorial(){
    int i = 1;
    while(i<=size){
        nFact *= i++;
    }
}

void Brute::swap(int a, int b){
    double tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

void Brute::perm1(double s[]){
    int m, k, p , q;

    m = size-2;
    while(s[m] > s[m+1]){
        m = m - 1;
    }

    k = size-1;
    while(s[m] > s[k]){
        k = k - 1;
    }
    swap(m,k);

    p = m + 1;
    q = size-1;
    while(p < q){
        swap(p,q);
        p++;
        q--;
    }
    permutations[count++] = s;
}

void Brute::printS(double data[]){
    using std::cout;
    for(int i = 0; i < size; i++){
        cout << data[i] << " ";
    }
    cout << "\n";
}

int Brute::modNextFit(double s[]){
    /*Modified version of nextFit heuristic
     */
    int binCount = 0;
    double bins[size];
    bins[binCount++] += s[0];
    for (int i = 1; i < size; i++){
        if (1 - (bins[binCount - 1] + s[i]) >= 0){
            bins[binCount - 1] += s[i];
        } else {
            bins[binCount++] +=s[i];
        }
    }

    return binCount;
}

void Brute::run(){
    struct timespec start;
    struct timespec finish;

    struct timespec startPack;
    struct timespec finishPack;

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 1; i < nFact; i++){
        perm1(data);
    }
    clock_gettime(CLOCK_REALTIME, &finish);

    clock_gettime(CLOCK_REALTIME, &startPack);
    for (int i = 0; i < nFact; i++){
        int testSize = modNextFit(permutations[i]);
        if(testSize < minBins){
            minBins = testSize;
            for (int j = 0; j < size; j++){
                best[j] = permutations[i][j];
            }
        }
    }
    clock_gettime(CLOCK_REALTIME, &finishPack);

    if (start.tv_nsec > finish.tv_nsec){
        computationTimeS = finish.tv_sec - 1 - start.tv_sec;
        computationTimeNS = (long)1e9 + finish.tv_nsec - start.tv_nsec;
    } else {
        computationTimeS = finish.tv_sec - start.tv_sec;
        computationTimeNS = finish.tv_nsec - start.tv_nsec;
    }

    if (startPack.tv_nsec > finishPack.tv_nsec){
        computationTimeSPack = finishPack.tv_sec - 1 - startPack.tv_sec;
        computationTimeNSPack = (long)1e9 + finishPack.tv_nsec - startPack.tv_nsec;
    } else {
        computationTimeSPack = finishPack.tv_sec - startPack.tv_sec;
        computationTimeNSPack = finishPack.tv_nsec - startPack.tv_nsec;
    }
}