#pragma once
#ifndef DEQUE_H
#define DEQUE_H

#include "Math.h" 


#define MAX_SIZE 200 // Maximum size of array or Deque 
//template<typename T>
class Deque {

private:
    Vector2D array[MAX_SIZE];
    int front;
    int rear;
    int size;
    int elements;

    void deletefront();
    void deleterear();    


public:
    Deque(int size) {
        front = -1;
        rear = 0;
        this->size = size;
        this->elements = 0;
    }

    Deque() {
        front = -1;
        rear = 0;
        this->size = MAX_SIZE;
        this->elements = 0;
    }

    void clear();
    void push_front(Vector2D key);
    void push_end(Vector2D key);
    Vector2D peek(int index);
    Vector2D peek_front();
    Vector2D peek_end();
    Vector2D pop_front();
    Vector2D pop_end();
    bool Contains(Vector2D element);

    int count() {
        return this->elements;
    }

    int length()
    {
        return this->size;
    }


    bool isFull() {
        return ((front == 0 && rear == size - 1) || front == rear + 1);
    }

    bool isEmpty() {
        return (front == -1);
    }
};
#endif