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

    template < typename TT, typename CCompare >
    friend std::ostream& operator<<(std::ostream& os, const PracticeHeap<TT, CCompare>& toPrint);

private:
    std::vector<T> container;
    Compare compFunc;

    void reheapUp();
    void reheapDown();
};

template <typename T, typename Compare>
PracticeHeap<T, Compare>::PracticeHeap() {
    compFunc = Compare();
}

template <typename T, typename Compare>
PracticeHeap<T, Compare>::PracticeHeap(const std::vector<T>& init) {
    compFunc = Compare();

    for(const T& curr : init) push(curr);
}

template <typename T, typename Compare>
T PracticeHeap<T, Compare>::top() const {
    return container.front();
}

template <typename T, typename Compare>
size_t PracticeHeap<T, Compare>::size() const {
    return container.size();
}

template <typename T, typename Compare>
bool PracticeHeap<T, Compare>::empty() const {
    return container.empty();
}

template <typename T, typename Compare>
void PracticeHeap<T, Compare>::push(const T toPush) {
    container.push_back(toPush);
    reheapUp();
}

template <typename T, typename Compare>
void PracticeHeap<T, Compare>::pop() {
    std::swap(container.back(), container.front());
    container.pop_back();
    reheapDown();
}

template <typename T, typename Compare>
std::ostream& operator<<(std::ostream& os, const PracticeHeap<T, Compare>& toPrint) {
    for(const T& curr : toPrint.container) {
        os << curr << ", ";
    }
    
    return os;
}

template <typename T, typename Compare>
void PracticeHeap<T, Compare>::reheapUp() {
    size_t curr = container.size() - 1, parent = (curr - 1) / 2;

    while(curr > 0 && compFunc(container[curr], container[parent])) {
        std::swap(container[curr], container[parent]);
        
        // move up the heap
        curr = parent;
        parent = (curr - 1) / 2;
    }    
}

template <typename T, typename Compare>
void PracticeHeap<T, Compare>::reheapDown() {
    size_t curr = 0;

    while(curr < container.size()) {
        //std::cout << curr << "\n";
        
        size_t left = (curr * 2) + 1;
        size_t right = (curr * 2) + 2;
        if(left >= container.size()) left = curr;
        if(right >= container.size()) right = curr;

        size_t best = (compFunc(container[left], container[right]))? left : right;

        // need to move curr down
        if(compFunc(container[best], container[curr])) {
            std::swap(container[curr], container[best]);
            curr = best;
        } else { // nothing to change
            break;
        }
    }
}

#endif

/*
12, 
17, 69,
20, 1000, 87, 420, 
10000, 300
*/