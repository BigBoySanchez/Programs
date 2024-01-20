#ifndef LETTERBAG1_H
#define LETTERBAG1_H
#include <iostream>
#include <string>
class LetterBag1
{
    friend std::ostream &operator<<(std::ostream &out, const LetterBag1 &lb); // call print
private:
    static const int MAXSIZE = 10000;
    char letters[MAXSIZE]; // lowercase letters in sorted order
    int size;              // total number of letters
public:
    LetterBag1(std::string s = "");                                        // initialize *this based on letters in s
    void insertOne(char ch);                                               // add one more occurrence of ch to *this
    void removeOne(char ch);                                               // remove one occurrence of ch from *this
    int getCount(char ch) const;                                           // return number of occurrences of ch in *this
    bool contains(char ch) const;                                          // return true iff ch occurs in *this
    void clear();                                                          // set size to 0.
    int getSize() const;                                                   // return size
    char getSmallest() const;                                              // return alphabetically smallest letter in *this, or '\0' if size is 0.
    LetterBag1 getUnion(const LetterBag1 &other) const;                    // return union of current object and other
    bool isEmpty() const;                                                  // return true if size is 0, false otherwise
    bool isSubbagOf(const LetterBag1 &other) const;                        // return true iff, for each letter, count in *this <= count in other
    bool operator==(const LetterBag1 &other) const;                        // return true iff *this and other contain same multiset of letters
    bool operator!=(const LetterBag1 &other) const;                        // return negation of *this == other
    bool operator<(const LetterBag1 &other) const;                         // return true iff 1st mismatch in 'a',...,'z’ has count in *this < cnt in other.
    bool operator<=(const LetterBag1 &other) const;                        // return true iff *this < other or *this == other
    bool operator>(const LetterBag1 &other) const;                         // return true iff other < *this
    bool operator>=(const LetterBag1 &other) const;                        // return true iff other <= *this
    void print(std::ostream &out = std::cout, bool endline = false) const; // See sample output
    std::string toString() const;                                          // See sample output
};
#endif