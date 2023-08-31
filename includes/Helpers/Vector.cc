#include "Vector.h"
#include <iostream>
#include <ostream>
/*
namespace Helpers {
    template <typename T>
    std :: ostream& operator << (std :: ostream &ostreamObj, Vector<T> vObj) {
        std :: size_t vSize = vObj.getSize();
        if (vSize == 0) return ostreamObj;

        for (int i = 0; i < vSize; i++)
            ostreamObj << vObj[i];
        
        return ostreamObj;
    }
};
*/
template <typename T>
Helpers :: Vector<T> :: Vector () : size(0), capacity(0), data(nullptr) {};

template <typename T> 
Helpers :: Vector<T> :: Vector (std :: size_t newCapacity) : capacity(newCapacity) {
    this->reserve(newCapacity);
}

template <typename T>
void Helpers :: Vector<T> :: push (T value) {    
    if (this->size == this->capacity)
        this->reserve((this->capacity == 0) ? 1 : this->capacity * 2);
    this->data[size] = value;
    size++;
}

template <typename T>
void Helpers :: Vector<T> :: reserve (std :: size_t newCapacity) {
    if (newCapacity > this->capacity) {
        T *temp = new T[size];

        if (this->capacity > 0) {
            for (long i = 0; i < this->size; i++)
                temp[i] = this->data[i];
            delete [] this->data;
            this->data = temp;
        }

        this->capacity = newCapacity;
    }
}

template <typename T>
T Helpers :: Vector<T> :: pop () {
    T value = this->data[size];
    delete this->data[size];
    size--;
    return value;
}

template <typename T>
T& Helpers :: Vector<T> :: operator [] (const long index) {
    return this->data[index];
}

template <typename T>
long Helpers :: Vector<T> :: getCapacity () {
    return this->capacity;
}

template <typename T>
long Helpers :: Vector<T> :: getSize () {
    return this->size;
}