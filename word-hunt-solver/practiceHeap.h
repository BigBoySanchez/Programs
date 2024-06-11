#ifndef PRACTICE_HEAP_H
#define PRACTICE_HEAP_H

#include <stdexcept>
#include <functional>
#include <iostream>

#define EXP 15

template <typename T, typename C = std::less<T>>
class practiceHeap {
    private:
    static constexpr size_t MAX_CAPACITY = 1 << EXP;
    T heap[MAX_CAPACITY] = { T() };
    size_t size = 0;
    C compare;

    void fixHeap(size_t root);
    void heapLoop();

    public:
    practiceHeap(const C& comp = C()) { compare = comp; }

    const T& top() const;
    void insert(T& toInsert);
    void remove();
    size_t getSize() const { return size; }
    bool empty() const { return size == 0; }
};

#undef EXP

#endif