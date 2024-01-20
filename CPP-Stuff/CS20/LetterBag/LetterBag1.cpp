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
    for(int i = 0; i < s.length() && i < MAXSIZE; ++i) {
        if(isalpha(s[i])) {
            char currChar = tolower(s[i]);
            ++size;
            letters[size - 1] = currChar;
        }
    }

    //modified insertion sort. og code from "https://www.geeksforgeeks.org/insertion-sort/"
    for (int i = 1; i < size; i++) {
        int key = letters[i];
        int j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && letters[j] > key) {
            letters[j + 1] = letters[j];
            j = j - 1;
        }
        letters[j + 1] = key;
    }
}

//insert ch into letters while keeping letters sorted
void LetterBag1::insertOne(char ch) {
    if(size == MAXSIZE || !isalpha(ch)) return; //dont insert ch if letters is full or ch isn't a letter
    int i = size;
    ch = tolower(ch);
    ++size;

    //move elements to the right until a spot for ch is found
    for(; i > 0 && letters[i - 1] > ch; --i)
        letters[i] = letters[i - 1];
    letters[i] = ch;
}

//remove one instance of ch
void LetterBag1::removeOne(char ch) {
    if(isEmpty() || !isalpha(ch)) return;
    int l = 0;
    int r = size - 1;
    int m = 0;
    ch = tolower(ch);

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
    int count = 1;
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

    l = m - 1;
    r = m + 1;

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
    //return non-empty bag if either is empty. return empty bag if both are empty
    if(this->isEmpty()) return other;
    if(other.isEmpty()) return *this;
    
    LetterBag1 temp; //build temp from scratch to avoid insert calls
    int i = 0, j = 0;

    //copy both bags into temp
    while(i < this->size || j < other.size) {        
        //copy "smaller" letters first
        if(j == other.size || (i < this->size && this->letters[i] <= other.letters[j])) {
            ++temp.size;
            temp.letters[temp.size - 1] = this->letters[i];
            ++i;
        }

        else if(i == this->size || (j < other.size && this->letters[i] >= other.letters[j])) {
            ++temp.size;
            temp.letters[temp.size - 1] = other.letters[j];
            ++j;
        }
    }
    return temp;
}

//returns true if letters is empty. false otherwise
bool LetterBag1::isEmpty() const {
    return size == 0;
}

//return true if curr object is a subset of other
bool LetterBag1::isSubbagOf(const LetterBag1& other) const {
    if(this->isEmpty()) return true; //empty set is tha subset of every set
    if(this->size > other.size) return false;
    int i = this->size - 1, j = other.size - 1;

    while(i >= 0 && j >= 0) {
        if(this->letters[i] < other.letters[j]) --j; //go backwards in other until familiar char is found
        else if(this->letters[i] == other.letters[j]) { //check next char in curr bag
            --i;
            --j;
        }
        if(this->letters[i] > other.letters[j]) return false; //bc this object is stuck on char that shouldn't be there
    }
    return i == -1; //check if this bag was completely checked
}

//return true if both bags are the same
bool LetterBag1::operator==(const LetterBag1& other) const {
    if(this->size != other.size) return false;

    //try to find mismatching char
    for(int i = 0; i < this->size; ++i)
        if(this->letters[i] != other.letters[i]) return false;
    return true; //no mismatching chars found
}

//test if both object aren't equal
bool LetterBag1::operator!=(const LetterBag1& other) const {
    return !(*this == other);
}

//tests if char count of curr object is less than char count of other object on the first mismatch
bool LetterBag1::operator<(const LetterBag1& other) const {
    if(this->isEmpty()) return !other.isEmpty(); //empty bag < other iff other isn't also empty
    if(other.isEmpty()) return false; //nothing is less than an empty bag
    
    for(int i = 0; i < std::min(this->size, other.size); ++i)
        //bc this->letter would be greater if other had a "smaller" letter
        if(this->letters[i] != other.letters[i]) return this->letters[i] > other.letters[i];
    return false; //both bags must be equal
}

//same as < or =
bool LetterBag1::operator<=(const LetterBag1& other) const {
    if(this->isEmpty()) return true; //an empty bag is always <= other
    if(other.isEmpty()) return false; //bc this bag can't be empty & nothing is smaller than empty
    
    for(int i = 0; i < std::min(this->size, other.size); ++i)
        //bc this->letter would be greater if other had a "smaller" letter
        if(this->letters[i] != other.letters[i]) return this->letters[i] > other.letters[i];
    return this->size == other.size; //test if both bags are equal
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