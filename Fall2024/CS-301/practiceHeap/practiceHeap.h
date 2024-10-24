#ifndef PRACTICE_HEAP
#define PRACTICE_HEAP

#include <vector>
#include <functional>
#include <iostream>

template < typename T, typename Compare = std::less<T> >
class PracticeHeap {
public:
    PracticeHeap();
    PracticeHeap(const std::vector<T>& init);
    
    T top() const;
    size_t size() const;
    bool empty() const;

    void push(const T toPush);
    void pop();

    friend std::ostream& operator<<(std::ostream& os, const PracticeHeap<T, Compare>& toPrint);

private:
    std::vector<T> container;
    Compare compFunc;

    void reheapUp();
    void reheapDown();
};

#include "practiceHeap.cpp"

#endif