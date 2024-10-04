#ifndef LETTERBAG2_H
#define LETTERBAG2_H
#include <iostream>
#include <string>
class LetterBag2
{
    friend std::ostream &operator<<(std::ostream &out, const LetterBag2 &lb); // call print
private:
    static const int MAXSIZE = 10000;
    unsigned short counts[26]; // to count the number of occurrences per char
    int size;

public:
    // Same specifications as for LetterBag1
    LetterBag2(std::string s = "");
    void insertOne(char ch);
    void removeOne(char ch);
    int getCount(char ch) const;
    bool contains(char ch) const;
    void clear();
    int getSize() const;
    char getSmallest() const;
    LetterBag2 getUnion(const LetterBag2 &other) const;
    bool isEmpty() const;
    bool isSubbagOf(const LetterBag2 &other) const;
    bool operator==(const LetterBag2 &other) const;
    bool operator!=(const LetterBag2 &other) const;
    bool operator<(const LetterBag2 &other) const;
    bool operator<=(const LetterBag2 &other) const;
    bool operator>(const LetterBag2 &other) const;
    bool operator>=(const LetterBag2 &other) const;
    void print(std::ostream &out = std::cout, bool endline = false) const;
    std::string toString() const;
};
#endif