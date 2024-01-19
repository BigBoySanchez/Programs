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
}

//remove 1 occurrence of ch from bag
void LetterBag2::removeOne(char ch) {
    if(contains(ch)) --counts[ch - 'a'];
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