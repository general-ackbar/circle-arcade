#pragma once
#ifndef DEQUE2_H
#define DEQUE2_H

#include "Math.h" 


#define MAX_SIZE 200 // Maximum size of array or Deque 
template<typename T>

class Deque2 {

private:
    T& array[MAX_SIZE];
    int front;
    int rear;
    int capacity;
    int size;

    void deletefront(){
            if (isEmpty()) {
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        if (front == capacity - 1) {
            front = 0;
        } else {
            front = front + 1;
        }
    }

    this->size -= 1;
    };
    void deleterear(){
            if (isEmpty()) {
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (rear == 0) {
        rear = capacity - 1;
    } else {
        rear = rear - 1;
    }

    this->size -= 1;
    };    


public:
    Deque(int capacity) {
        front = -1;
        rear = 0;
        this->capacity = capacity;
        this->size = 0;
    }

    Deque() {
        front = -1;
        rear = 0;
        this->capacity = MAX_SIZE;
        this->size = 0;
    }

    void clear(){
        this->size = 0;
        front = -1;
        rear = 0;
    };
    
    void push_front(const T& value){
        if (isFull()) {        
            return;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        } else if (front == 0){
            front = capacity - 1;
        } else {
            front = front - 1;
        }

        this->size += 1;
        array[front] = value;

    };

    void push_end(const T& value){
        if (isFull()) {
            return;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        } else if (rear == capacity - 1) {
            rear = 0;
        } else {
            rear = rear + 1;
        }

        this->size += 1;
        array[rear] = value;
    };


    T& operator[](size_t index) {
        if (index >= capacity) {

        }
        return array[index];
    }

    T& peek_front(){
        return array[front];
    };

    T& peek_end(){
        return array[rear];
    };

    T& pop_front(){
        if (isEmpty()) {
            // You might want to handle this differently
            return Vector2D{-1, -1}; // Assuming Vector2D constructor takes x and y values
        }
        Vector2D tmp = array[front];
        this->deletefront();
        return tmp;
    };

    T& pop_end(){
        if (isEmpty() || rear < 0) {
            // You might want to handle this differently
            return Vector2D{-1, -1}; // Assuming Vector2D constructor takes x and y values
        }
        Vector2D tmp = array[rear];
        this->deleterear();
        return tmp;
    };
    

    int count() {
        return this->size;
    }

    int length()
    {
        return this->capacity;
    }


    bool isFull() {
        return ((front == 0 && rear == capacity - 1) || front == rear + 1);
    }

    bool isEmpty() {
        return (front == -1);
    }
};
#endif