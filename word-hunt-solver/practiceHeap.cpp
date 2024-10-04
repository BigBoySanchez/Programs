#include "practiceHeap.h"

template <typename T, typename C>
void practiceHeap<T, C>::fixHeap(size_t root) {
    size_t best = root;
    const size_t LEFT = (root << 1) + 1, RIGHT = (root << 1) + 2;

    if(LEFT < size && compare(heap[best], heap[LEFT])) best = LEFT;
    if(RIGHT < size && compare(heap[best], heap[RIGHT])) best = RIGHT;

    if(best != root) {
        std::swap(heap[root], heap[best]);
        fixHeap(best);
    }
}

template <typename T, typename C>
void practiceHeap<T, C>::heapLoop() {
    size_t start = (size >> 1);
    for(size_t i = start; i > 0; i--) fixHeap(i - 1);
}

template<typename T, typename C>
const T& practiceHeap<T, C>::top() const {
    if(empty()) throw std::runtime_error("Heap is empty.\n");
    return heap[0];
}

template <typename T, typename C>
void practiceHeap<T, C>::insert(T& toInsert) {
    if(size >= MAX_CAPACITY + 1) throw std::runtime_error("Heap reached MAX_CAPACITY.\n");

    heap[size++] = toInsert;
    heapLoop();
}

template <typename T, typename C>
void practiceHeap<T, C>::remove() {
    if(empty()) throw std::runtime_error("Cannot remove from empty heap.\n");

    std::swap(heap[0], heap[--size]);
    heapLoop();
}


typedef std::pair<unsigned int, unsigned int> coords;
typedef std::vector<coords> coordVec;
typedef bool(*CVComp)(const coordVec&, const coordVec&);

/*
template <>
void practiceHeap<coordVec, CVComp>::print() const {
    if(empty()) {
        std::cout << "[]";
        return;
    }
    
    std::cout << "[ " << heap[0];
    for(size_t i = 1; i < size; i++) std::cout << ", " << heap[i]; 
    std::cout << " ]";
}*/

template class practiceHeap<int, std::less<int>>;
template class practiceHeap<coordVec, CVComp>;