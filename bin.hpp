#ifndef BIN_HPP
#define BIN_HPP

#define MAX_SIZE 1

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
};

#endif