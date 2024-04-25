#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "/Users/jaquen/Documents/Git-Stuff/Programs/CPP-Stuff/CS20/Stacks/ArrayStack.h"
#include <stdexcept>

template <class T>
class ArrayQueue {
    public:
    static const int MAXSIZE = 50;

    private:
    T values[MAXSIZE];
    int size, backIndex;

    public:
    ArrayQueue() {
        size = backIndex = 0;
    }

    ArrayQueue(const ArrayStack<T>& arrStack) {
        size = backIndex = 0;
        ArrayStack<T> trueStack = arrStack;

        while(!trueStack.empty()) {
            enqueue(trueStack.top());
            trueStack.pop();
        }

        while(!empty()) {
            trueStack.push(front());
            dequeue();
        }

        while(!trueStack.empty()) {
            enqueue(trueStack.top());
            trueStack.pop();
        }
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == MAXSIZE;
    }

    void dequeue() {
        if(empty())return;

        size--;
    }

    void enqueue(const T& val) {
        if(isFull()) return;
        
        backIndex++;
        if(backIndex == MAXSIZE) backIndex = 0;

        values[backIndex] = val;
        size++;
    }

    T& front() {
        if (empty()) {
            throw std::logic_error("Cannot get front of an empty queue!");
        }

        int frontIndex = backIndex - size + 1;
        if(frontIndex < 0) {
            frontIndex += MAXSIZE;
        }

        return values[frontIndex];
    }
};

#endif