#pragma once

template<typename T>
class FixedList {

private:
    T* data;
    int capacity;
    int size;

public:


    FixedList(int capacity) : data(nullptr), capacity(0), size(0) { this->capacity = capacity; }
    ~FixedList(){
        delete[] data;
    }

    int GetSize() {return size; };
    void push(const T& value) {
        
        if (size == capacity) {
            // Shift elements to the right, dropping the oldest one at the end
            for (int i = capacity-1; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value; // Insert the new element at the front
        } else {
            // Shift elements to the right to make space at the front
            for (int i = size; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value; // Insert the new element at the front
            size++; // Increase the size of the list
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            
        }
        return data[index];
    }

    void clear()
    {
        size = 0;
    }
};