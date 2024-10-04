#ifndef PRACTICE_MAP_H
#define PRACTICE_MAP_H

#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

#define EXP 15

template <typename k, typename v>
class node {
    public:
    k key;
    v val;
    node *next;

    node(const k& key = k(), const v& val = v(), node *next = nullptr) {
        this->key = key;
        this->val = val;
        this->next = next;
    }
};

template <typename k>
unsigned int getHash(const k& key, unsigned int tableSize);

template <>
unsigned int getHash(const std::string& key, unsigned int tableSize);


template <typename k, typename v>
class practiceMap {
    private:
    static constexpr unsigned int TABLE_SIZE = 1 << EXP;
    node<k, v> *buckets[TABLE_SIZE] = { nullptr };

    public:
    size_t size = 0;

    ~practiceMap();

    v& operator[](const k& key);

    void print() const;

    double getLoadFactor() const;
};

#undef EXP

#endif