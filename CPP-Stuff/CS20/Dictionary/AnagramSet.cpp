#include "AnagramSet.h"

ostream& operator<<(ostream& out, const AnagramSet& s) {
    out << "{ " << s.key.toString() << ":";
    for(int i = 0; i < s.words.size(); i++) {
        out << " " << s.words[i];
        if(i != s.words.size() - 1) out << ",";
    }
    out << " }";

    return out;
}

AnagramSet::AnagramSet(const LetterBag& theKey) {
    key = theKey;
    next = nullptr;
}

void AnagramSet::insert(const string& s) {
    int l = 0, r = words.size() - 1;
    
    //binary search for s
    while(l <= r) {
        int m = ((r - l) / 2) + l;
        if(words[m] < s) l = m + 1;
        else if(words[m] > s) r = m - 1;
        else return; 
    }

    //l is where s should be
    words.insert(words.begin() + l, s);
}

void AnagramSet::remove(const string& s) {
    vector<string>::iterator toRemove = find(words.begin(), words.end(), s);
    if(toRemove != words.end()) words.erase(toRemove);
}

int AnagramSet::getSize() const {
    return words.size();
}

bool AnagramSet::contains(const string& s) const {
    return find(words.begin(), words.end(), s) != words.end();
}

void AnagramSet::clear() {
    words.clear();
}

vector<string> AnagramSet::getWords() const {
    return words;
}

int AnagramSet::hashKey(int tableSize) const {
    int hash = 0;
    const unsigned char base = 31;
    unsigned int currPow = 1;

    //method 1: use letter frequency as digits for a base
    for(char c = 'a'; c <= 'z'; c++) {
        hash = (hash + (key.getFrequency(c) * currPow)) % tableSize;
        currPow = (currPow * base) % tableSize;
    }

    return hash;
}