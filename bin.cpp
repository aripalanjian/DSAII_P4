#include "bin.hpp"

Item::Item(Item& copy){
    this->next = copy.next;
    this->prev = copy.prev;
    this->value = copy.value;
}

Item::~Item(){
    this->next = nullptr;
    this->prev = nullptr;
    this->value = 0;
}

Item& Item::operator= (Item& copy){
    if(this != &copy){
        this->next = copy.next;
        this->prev = copy.prev;
        this->value = copy.value;
    }

    return *this;
}

Bin::Bin(){
    head = nullptr;
    // tail = nullptr;
    // head = tail;
    tail = head;
    size = 0;
    value = 0.0;
}

Bin::~Bin(){
    for (int i = 0; i < size; i++){
        pop();
    }
    size = 0;
}

void Bin::push(Item* newTail){
    if (isEmpty()){
        head = newTail;
        tail = newTail;
    } else {
        tail->setNext(newTail);
        tail = newTail;
    }
    size++;
}

Item* Bin::pop(){
    Item* tmp = tail;
    tail = tail->getPrev();
    tail->setNext(nullptr);
    size--;
    return tmp;
}

bool Bin::canFit(double val){
    if ((value + val) - MAX_SIZE > 0){
        return false;
    }
    return true;
}