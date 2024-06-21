
#pragma once

#include <circle/alloc.h>

template<typename T>
class Array {
private:
    T* array;
    size_t capacity;
    

    void resize() {
        capacity = capacity ? capacity * 2 : 1;
        T* newArray = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newArray[i] = array[i]; // Direct copy; consider using std::move for non-trivial types
        }
        delete[] array;
        array = newArray;
    }

public:
    size_t size;
    Array() : array(nullptr), capacity(0), size(0) {}
    
    ~Array() {
        delete[] array;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        array[size++] = value;
    }

    T& operator[](size_t index) {
        if (index >= size) {
//            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    int getSize() const { return size; }

    void erase(size_t index) {
        if (index >= size) {
            //throw "Index out of range";
        }
        for (size_t i = index; i < size - 1; ++i) {
            array[i] = array[i + 1]; // Shift elements left
        }
        size--;
    }

    bool isEmpty(){
        return size == 0;
    }

    void clear(){
         size = 0;
    }

    T& getItemAt(int index){
        return array[index];
    }

};
