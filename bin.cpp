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
    tail = head;
    size = 0;
    value = 0.0;
}

Bin::~Bin(){
    while (!isEmpty()) {
        pop();
    }
}

void Bin::push(Item* newTail){
    if (isEmpty()){
        head = newTail;
        tail = head;
    } else {
        tail->setNext(newTail);
        newTail->setPrev(tail);
        tail = newTail;
    }
    value += newTail->getValue();
    size++;
}

Item* Bin::pop(){
    Item* tmp;
    if (tail == head){
        tmp = head;
        head = nullptr;
        tail = nullptr;
    } else {
        tmp = tail;
        tail = tail->getPrev();
        tmp ->setPrev(nullptr);
        tail->setNext(nullptr);
    }
    value -= tmp->getValue();
    size--;
    return tmp;
}

bool Bin::canFit(double val){
    if ((value + val) - MAX_SIZE > 0){
        return false;
    }
    return true;
}