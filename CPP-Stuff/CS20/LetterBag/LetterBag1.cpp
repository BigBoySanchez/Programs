#include "LetterBag1.h"
#include <iostream>
#include <string>

//print da lettr bag
std::ostream& operator<<(std::ostream& out, const LetterBag1& lb) {
    lb.print(out, true);
    return out;
}

//insert each char in s to letters
LetterBag1::LetterBag1(std::string s = "") {
    size = 0;
    for(char c : s)
        insertOne(c);
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
    ++size;
    while(right > index) {
        letters[right] = letters[right - 1];
        --right;
    }
    
    //put ch into proper spot
    letters[right] = ch;
}

void LetterBag1::removeOne(char ch) {
    if(size == 0) return;
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

int LetterBag1::getCount(char ch) const {
    if(size == 0) return 0;
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

bool LetterBag1::contains(char ch) const {
    if(size == 0) return false;
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

    return letters[m] == ch;
}

