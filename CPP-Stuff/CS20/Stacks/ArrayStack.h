#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H


#include <stdexcept>
using namespace std;




template <class T>
class ArrayStack {

public:
    static const int MAXSIZE = 10000;

private:
    T values[MAXSIZE];
    int size;

public:

    ArrayStack() {
        size = 0;
    }
    void push(const T& val)  {
        if (size < MAXSIZE)
            values[size++] = val;
    }

    void pop() {
        if (size > 0) 
            size--;
    }

    T& top() {
        if (size == 0)
            throw logic_error("Cannot get the top of an empty stack!");
        return values[size-1];
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    bool full() const {
        return size == MAXSIZE;
    }




};
#endif

/*
x  b
_  _  _  _  _  _  _  _ ...  (values array)
0  1  2  3  4  5 

size: 2

ArrayStack<char> myStack;
myStack.push('x');
myStack.push('y');
myStack.pop();
myStack.push('b');


*/