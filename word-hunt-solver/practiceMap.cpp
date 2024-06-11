#include "practiceMap.h"

template <typename k>
unsigned int getHash(const k& toHash, unsigned int tableSize) {
    return (toHash & INT_MIN) % tableSize;
}

template<>
unsigned int getHash(const std::string& key, unsigned int tableSize) {
    unsigned int hash = 0;
    const unsigned char BASE = 31;
    unsigned int currPow = 1;

    for(char c : key) {
        char cl = tolower(c);
        hash = (hash + (currPow * (cl - 'a' + 1))) % tableSize;
        currPow = (currPow * BASE) % tableSize;
    }

    return hash;
}

template <typename k, typename v>
practiceMap<k, v>::~practiceMap() {
    for(unsigned int i = 0; i < TABLE_SIZE; i++) {
        node<k, v> *curr = buckets[i];
        if(curr == nullptr) continue;

        while(curr->next) {
            node<k, v> *toDelete = curr;
            curr = curr->next;

            delete toDelete;
        }
    }
}

template <typename k, typename v>
v& practiceMap<k, v>::operator[](const k& key) {
    unsigned int index = getHash(key, TABLE_SIZE);
    node<k, v> *curr = buckets[index];

    if(curr == nullptr) {
        buckets[index] = new node<k, v>(key);
        if(buckets[index] == nullptr) throw std::runtime_error("Could not make node.\n");

        size++;
        return buckets[index]->val;
    }

    while(curr->next != nullptr && curr->next->key != key) curr = curr->next;
    if(curr->key != key && curr->next == nullptr)  {
        curr->next = new node<k, v>(key);
        if(curr->next == nullptr) throw std::runtime_error("Could not make node.\n");

        curr = curr->next;
        size++;
    }

    if(getLoadFactor() > 1.0) throw std::runtime_error("Load factor too high.\n");

    return curr->val;
}

template <typename k, typename v>
void practiceMap<k, v>::print() const {
    for(unsigned int i = 0; i < TABLE_SIZE; i++) {
        node<k, v> *curr = buckets[i];
        if(curr == nullptr) continue;

        std::cout << std::setw(7) << i << ": " << "{" << curr->key << ", " << curr->val << "}";
        while(curr->next) {
            std::cout << ", " << "{" << curr->next->key << ", " << curr->next->val << "}";
            curr = curr->next;
        }
        std::cout << "\n";
    }
}

template <typename k, typename v>
double practiceMap<k, v>::getLoadFactor() const {
    return (double)(size / TABLE_SIZE);
}

template class practiceMap<std::string, bool>;