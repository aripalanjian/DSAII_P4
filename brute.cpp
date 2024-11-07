#include "brute.hpp"
#include "heuristic.hpp"
#include <iostream>

Brute::Brute(double values[],int size){
    this->size = size;
    this->minBins = size;
    data = new double[size];
    for(int i =0; i < size; i++){
        data[i] = values[i];
    }
    bestArr = new double[size];
    calculateFactorial();
    std::cout << "Factorial: " << nFact << "\n";
    packBins();
}

Brute::~Brute(){
    delete [] data;
    delete [] bestArr;
}

void Brute::calculateFactorial(){
    int i = 1;
    while(i<=size){
        nFact *= i++;
    }
}

void Brute::swap(int a, int b){
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

void Brute::perm1(double s[]){
    // int size = n;
    int m, k, p , q;

    m = size-2;
    while(s[m] - s[m+1] > 0){
        m = m - 1;
    }

    k = size-1;
    while(s[m] - s[k] > 0){
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
    // printS(s);
}

void Brute::packBins(){
    Heuristic optimalTest(size, data);
    optimalTest.bestFit();
    int testSize = optimalTest.getSize();
    if(testSize < minBins){
        minBins = testSize;
        for (int i = 0; i < size; i++) {
            bestArr[i] = optimalTest.dataAt(i);
        }
    }
}

void Brute::printS(double data[]){
    using std::cout;
    cout << 0 << " ";
    for(int i = 0; i <= size; i++){
        cout << data[i] << " ";
    }
}

void Brute::run(){
    struct timespec start;
    struct timespec finish;

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 1; i < 10000000; i++){
        perm1(data);
        packBins();
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    if (start.tv_nsec > finish.tv_nsec){
        computationTimeS = finish.tv_sec - 1 - start.tv_sec;
        computationTimeNS = (long)1e9 + finish.tv_nsec - start.tv_nsec;
    } else {
        computationTimeS = finish.tv_sec - start.tv_sec;
        computationTimeNS = finish.tv_nsec - start.tv_nsec;
    }
}