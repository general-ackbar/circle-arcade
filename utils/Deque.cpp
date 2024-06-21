
#include "Deque.h"

void Deque::push_front(Vector2D key) {
    if (isFull()) {        
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    } else if (front == 0){
        front = size - 1;
    } else {
         front = front - 1;
    }

    this->elements += 1;
    array[front] = key;
}

void Deque::push_end(Vector2D key) {
    if (isFull()) {
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    } else if (rear == size - 1) {
        rear = 0;
    } else {
        rear = rear + 1;
    }

    this->elements += 1;
    array[rear] = key;
}

void Deque::deletefront() {
    if (isEmpty()) {
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        if (front == size - 1) {
            front = 0;
        } else {
            front = front + 1;
        }
    }

    this->elements -= 1;
}

void Deque::deleterear() {
    if (isEmpty()) {
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (rear == 0) {
        rear = size - 1;
    } else {
        rear = rear - 1;
    }

    this->elements -= 1;
}

Vector2D Deque::pop_front() {
    if (isEmpty()) {
        // You might want to handle this differently
        return Vector2D{-1, -1}; // Assuming Vector2D constructor takes x and y values
    }
    Vector2D tmp = array[front];
    this->deletefront();
    return tmp;
}

Vector2D Deque::pop_end() {
    if (isEmpty() || rear < 0) {
        // You might want to handle this differently
        return Vector2D{-1, -1}; // Assuming Vector2D constructor takes x and y values
    }
    Vector2D tmp = array[rear];
    this->deleterear();
    return tmp;
}


Vector2D Deque::peek_front()
{
    return array[front];
}

Vector2D Deque::peek_end()
{
    return array[rear];
}

Vector2D Deque::peek(int index)
{
    int postion = front + index;
    if(postion >= this->size)
    {
        postion = index - (this->size - front);
    }
    
    return array[postion];
}

void Deque::clear()
{
    this->elements = 0;
    front = -1;
    rear = 0;
}

bool Deque::Contains(Vector2D element)
{
    for (int i = 0; i < this->elements; i++)
    {
        if (Math::Vector2DEquals(this->peek(i), element))
        {
            return true;
        }
    }
    return false;
}