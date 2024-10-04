#include "LetterBag2.h"
#include <iostream>
#include <string>

//print letter bag
std::ostream& operator<<(std::ostream& out, const LetterBag2& lb) {
    lb.print(out);
    return out;
}

//insert each char in s to letterbag
LetterBag2::LetterBag2(std::string s) {
    clear();
    for(int i = 0; i < s.length() && i < MAXSIZE; ++i)
        insertOne(s[i]);
}

//insert ch into letterbag
void LetterBag2::insertOne(char ch) {
    if(size == MAXSIZE || !isalpha(ch)) return; //can't insert if letterbag is full or ch isn't a letter
    ch = tolower(ch);

    ++counts[ch - 'a']; //increment count for letter
    ++size;
}

//remove 1 occurrence of ch from bag
void LetterBag2::removeOne(char ch) {
    if(isEmpty() || !isalpha(ch)) return; //can't remove something that ain't there...

    ch = tolower(ch);
    if(contains(ch)) --counts[ch - 'a'];
    --size;
}

//returns amount of ch in letterbag
int LetterBag2::getCount(char ch) const {
    return counts[ch - 'a'];
}

//tests if ch is in letterbag
bool LetterBag2::contains(char ch) const {
    return getCount(ch) > 0;
}

//reset counts and size
void LetterBag2::clear() {
    size = 0;
    for(char c = 'a'; c <= 'z'; ++c) //initialize each letter in counts
        counts[c - 'a'] = 0;
}

//return size of letterbag
int LetterBag2::getSize() const {
    return size;
}

//returns smallest char in the bag
char LetterBag2::getSmallest() const {
    if(isEmpty()) return '\0';
    
    //go thru the alphabet
    for(char c = 'a'; c <= 'z'; ++c)
        if(getCount(c) != 0) return c;
    return '\0'; //just in case...
}

//return the union of both bags
LetterBag2 LetterBag2::getUnion(const LetterBag2& other) const {
    //return non-empty bag if either is empty. return empty bag if both are empty
    if(this->isEmpty()) return other;
    if(other.isEmpty()) return *this;
    
    LetterBag2 temp = other;
    //add char counts of curr object and other together in temp
    for(char c = 'a'; c <= 'z'; ++c) {
        int charCount = this->getCount(c);
        for(int i = 0; i < charCount; ++i) 
            temp.insertOne(c);
    }
    return temp;
}

//test if bag is empty
bool LetterBag2::isEmpty() const {
    return size == 0;
}

//test if curr object is a subset of other
bool LetterBag2::isSubbagOf(const LetterBag2& other) const {
    if(this->getSize() > other.getSize()) return false; //subset < og set. remember that...
    for(char c = 'a'; c <= 'z'; ++c)
        if(this->getCount(c) > other.getCount(c)) return false; //same here...
    return true;
}

//test if both bags are tha same
bool LetterBag2::operator==(const LetterBag2& other) const {
    if(this->getSize() != other.getSize()) return false; //they GOTTA have the same size

    for(char c = 'a'; c <= 'z'; ++c)
        if(this->getCount(c) != other.getCount(c)) return false; //gotta have the same count too
    return true; //passed all the tests o7 <- salute
}

//test is both bags aren't the same
bool LetterBag2::operator!=(const LetterBag2& other) const {
    return !(*this == other);
}

//test if curr < other
bool LetterBag2::operator<(const LetterBag2& other) const {
    //find first mismatch
    for(char c = 'a'; c <= 'z'; ++c) {
        int thisCount = this->getCount(c);
        int otherCount = other.getCount(c);

        if(thisCount != otherCount) return thisCount < otherCount; //check if curr < other
    }
    return false; //both bags are the same
}

//test if curr <= other
bool LetterBag2::operator<=(const LetterBag2& other) const {
    //find first mismatch
    for(char c = 'a'; c <= 'z'; ++c) {
        int thisCount = this->getCount(c);
        int otherCount = other.getCount(c);

        if(thisCount != otherCount) return thisCount < otherCount; //check if curr < other
    }
    return true; //both bags are the same
}

//test if curr > other
bool LetterBag2::operator>(const LetterBag2& other) const {
    return !(*this <= other);
}

//test if curr >= other
bool LetterBag2::operator>=(const LetterBag2& other) const {
    return !(*this < other);
}

//print letterbag w/ format "{ch1,ch2,ch3,...,chn}"
void LetterBag2::print(std::ostream& out, bool endline) const {
    int numPrinted = 0;
    out << "{";
    for(char c = 'a'; c <= 'z'; ++c) {
        int charCount = getCount(c);
        for(int i = 0; i < charCount; ++i) {
            out << c;
            if(numPrinted != size - 1) out << ",";
            ++numPrinted;
        }
    }
    out << "}";
    if(endline) out << "\n";
}

//return the letterbag as a string
std::string LetterBag2::toString() const {
    std::string ret = "";
    
    //add each char in the bag to ret
    for(char c = 'a'; c <= 'z'; ++c) {
        int charCount = getCount(c);

        for(int i = 0; i < charCount; ++i)
            ret += c;
    }
    return ret;
}