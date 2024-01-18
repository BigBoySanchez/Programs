#include "LetterBag1.h"
#include <iostream>
#include <string>

//print da lettr bag
std::ostream& operator<<(std::ostream& out, const LetterBag1& lb) {
    lb.print(out);
    return out;
}

//insert each char in s to letters
LetterBag1::LetterBag1(std::string s) {
    size = 0;
    for(int i = 0; i < s.length(); ++i)
        insertOne(s[i]);
}

//insert char into proper position in letters
void LetterBag1::insertOne(char ch) {
    if(size == MAXSIZE) return;
    int index = 0;
    int right = size + 1;
    ch = tolower(ch);

    //find proper spot for ch
    while(index < size && letters[index] < ch)
        ++index;
    
    //shift elements after index one place to the right. starting from the last one
    while(right > index) {
        letters[right] = letters[right - 1];
        --right;
    }
    
    //put ch into proper spot
    letters[right] = ch;
    ++size;
}

//remove one instance of ch
void LetterBag1::removeOne(char ch) {
    if(isEmpty()) return;
    int l = 0;
    int r = size - 1;
    int m = 0;


    //modified binary search. og code from "https://www.geeksforgeeks.org/binary-search/"
    while (l <= r) {
        m = l + (r - l) / 2;
        
        if (letters[m] < ch) l = m + 1; // If ch greater, ignore left half
        else if(letters[m] > ch) r = m - 1; // If ch is smaller, ignore right half
        else break; //ch must be present at mid
    }
    if(letters[m] != ch) return; //return early if ch was not found

    //shift elements after m to the left to remove letters[m]
    for(; m < size - 1; ++m)
        letters[m] = letters[m + 1];
    letters[m] = '\0';
    --size;
}

//returns amount of ch in letters
int LetterBag1::getCount(char ch) const {
    if(isEmpty()) return 0;
    int count = 0;
    int l = 0;
    int r = size - 1;
    int m = 0;


    //modified binary search. og code from "https://www.geeksforgeeks.org/binary-search/"
    while (l <= r) {
        m = l + (r - l) / 2;
        
        if (letters[m] < ch) l = m + 1; // If ch greater, ignore left half
        else if(letters[m] > ch) r = m - 1; // If ch is smaller, ignore right half
        else break; //ch must be present at mid
    }
    if(letters[m] != ch) return 0; //return early if ch was not found

    l = m;
    r = m;

    //count the amount of ch to the left of m
    while (letters[l] == ch && l >= 0) {
        ++count;
        --l;
    }

    //same for the right of m
    while (letters[r] == ch && r <= size - 1) {
        ++count;
        ++r;
    }
    
    return count;
}

//returns true if ch is in letters. false otherwise
bool LetterBag1::contains(char ch) const {
    if(isEmpty()) return false;
    int l = 0;
    int r = size - 1;
    int m = 0;


    //modified binary search. og code from "https://www.geeksforgeeks.org/binary-search/"
    while (l <= r) {
        m = l + (r - l) / 2;
        
        if (letters[m] < ch) l = m + 1; // If ch greater, ignore left half
        else if(letters[m] > ch) r = m - 1; // If ch is smaller, ignore right half
        else break; //ch must be present at mid
    }
    return letters[m] == ch; //return "ch was found at m"
}

//set size to 0. effectively removes everything from letters
void LetterBag1::clear() {
    size = 0;
}

//returns size
int LetterBag1::getSize() const {
    return size;
}

//returns letter w/ smallest ascii value (aka earliest in the alphabet). returns '\0' when letters is empty
char LetterBag1::getSmallest() const {
    return (isEmpty())? '\0' : letters[0];
}

//return union of curr object and another one.
LetterBag1 LetterBag1::getUnion(const LetterBag1& other) const {
    //return non-empty object or an empty object if both are empty
    if(other.isEmpty()) return *this;
    if(this->isEmpty()) return other;

    //copy other into temp, then add letters in curr object to temp
    LetterBag1 temp = other;
    for(int i = 0; i < size; ++i)
        temp.insertOne(letters[i]);
    return temp;
}

//returns true if letters is empty. false otherwise
bool LetterBag1::isEmpty() const {
    return size == 0;
}

//return true if curr object is a subset of other
bool LetterBag1::isSubbagOf(const LetterBag1& other) const {
    if(this->isEmpty()) return true; //empty set is tha subset of every set
    if(this->getSize() > other.getSize()) return false;
    char lastChar = '\0';

    for(int i = 0; i < this->getSize(); ++i) {
        if(this->letters[i] == lastChar) continue; //ignore current letter if it's not new

        lastChar = this->letters[i];
        if(this->getCount(lastChar) > other.getCount(lastChar)) return false; //too many characters in curr object
    }
    return true;
}

//return true if both bags are the same
bool LetterBag1::operator==(const LetterBag1& other) const {
    if(this->getSize() != other.getSize()) return false;
    char lastChar = '\0';

    for(int i = 0; i < this->getSize(); ++i) {
        if(this->letters[i] == lastChar) continue; //ignore current letter if it's not new

        lastChar = this->letters[i];
        if(this->getCount(lastChar) != other.getCount(lastChar)) return false; //char counts aren't the same
    }
    return true;
}

//test if both object aren't equal
bool LetterBag1::operator!=(const LetterBag1& other) const {
    return !(*this == other);
}

//note for me: b < c -> other < this
//tests if char count of curr object is less than char count of other object on the first mismatch
bool LetterBag1::operator<(const LetterBag1& other) const {
    //find first mismatch
    for(char c = 'a'; c <= 'z'; ++c) {
        int thisCount = this->getCount(c);
        int otherCount = other.getCount(c);

        if(thisCount <)
    }
}

//same as < or =
bool LetterBag1::operator<=(const LetterBag1& other) const {
    char lastChar = '\0';

    //find first mismatch
    for(int i = 0; i < this->getSize() && i < other.getSize(); ++i) {
        if(this->letters[i] == lastChar) continue; //ignore current letter if it's not new

        lastChar = letters[i];
        int thisCount = this->getCount(lastChar);
        int otherCount = other.getCount(lastChar);
        if(thisCount != otherCount) return otherCount < thisCount; //check if curr object has less of lastChar than other object
    }
    return true; //no mismatches
}

//returns !(curr <= other). same as curr > other
bool LetterBag1::operator>(const LetterBag1& other) const {
    return !(*this <= other);
}

//returns !(curr < other). same as curr >= other
bool LetterBag1::operator>=(const LetterBag1& other) const {
    return !(*this < other);
}

//print w/ format = {ch1,ch2,ch3...,chn}
void LetterBag1::print(std::ostream & out, bool endline) const {
    out << "{";
    for(int i = 0; i < size; ++i) {
        out << letters[i];
        if(i != size - 1) out << ",";
    }
    out << "}";

    if(endline) out << "\n";
}

//return letters array as a string
std::string LetterBag1::toString() const {
    std::string ret = "";

    //build string from chars in letters
    for(int i = 0; i < size; ++i)
        ret += letters[i];
    return ret;
}