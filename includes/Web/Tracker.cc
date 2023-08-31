#include<iostream>
#include <ostream>
#include "Tracker.h"

namespace Web {
    std :: ostream& operator << (std :: ostream &ostreamObj, const Tracker &tObj) {
        int size = tObj.size;
        if (size == 0) return ostreamObj;

        for (int i = 0; i < size; i++)
            ostreamObj << tObj.data[i] << '\n';

        return ostreamObj;
    }
}

Web :: Tracker :: Tracker () {
    this->data = nullptr;
    this->capacity = 0;
    this->size = 0;
}

Web :: Tracker :: ~Tracker () {
    this->deleteTracker();
}

Web :: Tracker :: Tracker (Tracker &tObj) : data {nullptr}, capacity{0}, size{0} {
    int tSize = tObj.getSize();
    if (tSize == 0) return;

    for (int i = 0; i < tSize; i++){
        this->push(tObj[i]);
        //std :: cout << tObj[i];
    } 
}

void Web :: Tracker :: deleteTracker () {
    delete [] this->data;
    this->data = nullptr;
    this->size = 0;
    this->capacity = 0;
}

void Web :: Tracker :: stats (long value = -1, int i = -1) {
    std :: cout << ">> I:" << i << " V:" << value << " C:" << this->capacity << " S:" << this->size<< std :: endl;
}

long Web :: Tracker :: push (const long value) {
    int index = this->search(value);    
    if (index != -1) return -1;

    if (capacity > size) {

        if (value > this->data[this->size-1]) {
            this->data[this->size] = value;
            index = this->size;
        }

        else {            
            long i{this->size};
            while (i > 0) {
                if (value < this->data[i-1]) {
                    this->data[i] = value;
                    index = i;
                    break;
                }
                this->data[i] = this->data[i-1];
                i--;
            }
        }        
    }

    if (capacity != 0) {
        capacity == this->size && (capacity *= 2);

        long *temp = new long[capacity];
        long i{0}, j{0};
        bool flag = true;
        while (j < this->size) {
            if (flag && value < this->data[j]) {
                temp[i] = value;
                index = i;
                i++, flag = false;
            }
            temp[i] = this->data[j];
            i++, j++;
        }
        temp[i] = value;

        delete [] this->data;
        this->data = temp;
    }

    else {        
        capacity = 1;
        this->data = new long[capacity];
        this->data[0] = value;
    }

    this->size++;
    return index;
}

bool Web :: Tracker :: search (const long value, int &index) {

    if (size == 0) {
        index = 0;
        return false;        
    }

    int start = 0, end = this->size, mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (value == this->data[mid]) {
            index = mid;
            return true;
        }

        else if (value > this->data[mid])
            start = mid + 1;

        else
            end = mid - 1;
    }

    index = end;
    return false;
}

long Web :: Tracker :: search (const long value) {
    if (this->size == 0) return -1;
    int start = 0, end = this->size-1, mid;
    while (start <= end) {
        mid = (start + end) / 2;        
        if (value == this->data[mid])
            return mid;        

        else if (value > this->data[mid])
            start = mid + 1;

        else
            end = mid - 1;
    }
    return -1;
}

void Web :: Tracker :: print () {
    for (int i = 0; i < size; i++)
        std :: cout << this->data[i] << ' ';
}

long Web :: Tracker :: getSize () {
    return this->size;
}

long Web :: Tracker :: getCapacity () {
    return this->capacity;
}

long Web :: Tracker :: operator [] (const long index) {
    return this->data[index];
}

Web :: Tracker Web :: Tracker :: operator = (const Web :: Tracker &tObj) {
    int tSize = tObj.size;
    if (tSize == 0) return *this;

    this->deleteTracker();
    for (int i = 0; i < tSize; i++)
        this->push(tObj.data[i]);
    return *this;
}