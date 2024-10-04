#ifndef ANAGRAM_SET_H
#define ANAGRAM_SET_H

#include "LetterBag.h"

class AnagramSet {
    friend ostream& operator<<(ostream& out, const AnagramSet& s);
    
    private:
    vector<string> words;

    public:
    LetterBag key;
    AnagramSet *next;

    AnagramSet(const LetterBag& theKey);        //: key(theKey)
    void insert(const string& s);               // insert s into the words vector in sorted order. Don't insert if it's already there.
    void remove(const string& s);               // remove s from the words vector, if it's there. Otherwise do nothing.
    int getSize() const;                        // Return the size of the words vector.
    bool contains(const string& s) const;       // Return true  iff s is in the words vector.
    void clear();                               // remove all the words i.e. set words to the empty vector.
    vector<string> getWords() const;            // return words.
    int hashKey(int tableSize) const;           // Hash the key. Make sure to come up with a good hash function.
};

#endif