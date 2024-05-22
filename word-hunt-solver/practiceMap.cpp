#include "practiceMap.h"

template <typename keyType, typename valType>
ostream & operator<<(ostream & out, const practiceMap<keyType, valType> & toPrint) {
    for(int i = 0; i < toPrint.TABLE_SIZE; i++) {
        practiceMap<keyType, valType>::node * curr = toPrint.buckets[i];
        if(curr == nullptr) continue;

        out << setw(7) << i << ":" << setw(11);
        while(curr != nullptr) {
            out << "{" << curr->key << ", " << curr->val << "}";
            if(curr->next != nullptr) out << ", "; 
        }
        out << "\n";
    }
}

template <typename keyType, typename valType>
practiceMap<keyType, valType>::~practiceMap() {
    clear();
}

template <typename keyType, typename valType>
unsigned int practiceMap<keyType,valType>::getHash(const keyType & toHash) const {
    unsigned int hash = toHash & UINT_MAX;
    return hash % TABLE_SIZE;
}

template <typename keyType, typename valType>
unsigned int practiceMap<keyType, valType>::getHash(const string & toHash) const {
    unsigned int hash = 0;
    const unsigned char BASE = 31;
    unsigned int currPow = 1;

    for(int i = 0; i < toHash.length(); i++) {
        hash = (hash + ((toHash[i] - 'a' + 1) * currPow)) % UINT_MAX;
        currPow = (currPow * BASE) % UINT_MAX;
    }

    return hash;
}

template <typename keyType, typename valType>
void practiceMap<keyType, valType>::clear() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        practiceMap<keyType, valType>::node * curr = buckets[i];
        if(curr == nullptr) continue;

        while(curr != nullptr) {
            practiceMap<keyType, valType>::node * toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        buckets[i] = nullptr;
    }
}

template <typename keyType, typename valType>
valType & practiceMap<keyType, valType>::operator[](const keyType & key) {
    unsigned int index = getHash(key);

    if(buckets[index] == nullptr) {
        buckets[index] = new practiceMap<keyType,valType>::node;
        if(buckets[index] == nullptr) throw "ERROR: Could not make new node.\n";
        
        buckets[index] = {key, valType(), nullptr};
        return buckets[index]->val;
    }
    
    //WIP return for existing key/bucket
}