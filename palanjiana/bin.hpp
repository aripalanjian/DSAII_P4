/***************************************************************
  Student Name: Ari Palanjian
  File Name: bin.hpp
  Project 4

  Defines the class Bin which stores Item nodes that are
   linked, calculates if a given value can fit in the bin,
   calculates remaining space.

  Defines the class Item which is used to store the data 
    value and holds pointers to the previous and next
    Item in the bin.
***************************************************************/
#ifndef BIN_HPP
#define BIN_HPP

#define MAX_SIZE 1.0

class Item{
    Item* next;
    Item* prev;
    double value;
public:
    Item(){value = 0.0;next = nullptr;prev=nullptr;}
    Item(double value){this->value = value;next = nullptr;prev=nullptr;}
    Item(Item& copy);
    ~Item();
    Item& operator= (Item& copy);

    void setNext(Item* next) {this->next = next;}
    Item* getNext(){return next;}
    void setPrev(Item* prev){this->prev = prev;}
    Item* getPrev(){return prev;}
    void setValue(double value){this->value = value;}
    double getValue(){return value;}
};

class Bin{
    Item* head;
    Item* tail;
    int size;
    double value; //sum of items in bin

public:
    Bin();
    ~Bin();
    void push(Item* newTail);
    Item* pop();
    double peek(){return tail->getValue();}
    bool isEmpty(){return size > 0 ? false:true;}
    int getSize(){return size;}
    void setValue(double val){value += val;}
    double getValue(){return value;}
    bool canFit(double val);
    double remainingSpace(double value){return MAX_SIZE - (this->value + value);}
};

#endif