#include <string>

class LetterBag1 {
private:
    static const int MAXSIZE = 10000;
    char letters[MAXSIZE]; // lowercase letters in sorted order
    int size;              // total number of letters
public:
    LetterBag1::LetterBag1(std::string s = "") {
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
    
    bool LetterBag1::isEmpty() const {
        return size == 0;
    }
    
    char LetterBag1::getBiggest() const {
        return (isEmpty())? '\0' : letters[size - 1];
    }

    LetterBag1 LetterBag1::toSet() const {
        LetterBag1 ret;
        if(this->isEmpty()) return ret;
        char last_char = this->letters[0];

        for(int i = 1; i < this->size && last_char < this->getBiggest(); ++i) {
            if(this->letters[i] == last_char) continue;
            ret.letters[ret.size] = this->letters[i];
            ++ret.size;
        }

        return ret;
    }
};

class LetterBag2
{
    friend std::ostream &operator<<(std::ostream &out, const LetterBag2 &lb); // call print
private:
    static const int MAXSIZE = 10000;
    unsigned short counts[26]; // to count the number of occurrences per char
    int size;

public:
    //insert each char in s to letterbag
    LetterBag2::LetterBag2(std::string s = "") {
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
    //reset counts and size
    void LetterBag2::clear() {
        size = 0;
        for(char c = 'a'; c <= 'z'; ++c) //initialize each letter in counts
            counts[c - 'a'] = 0;
    }
    //test if bag is empty
    bool LetterBag2::isEmpty() const {
        return size == 0;
    }
    char LetterBag2::getBiggest() const {
        if(isEmpty()) return '\0';

        for(char c = 'z'; c >= 'a'; --c)
            if(counts[c - 'a'] > 0) return c;
        return '\0';
    }
    LetterBag2 LetterBag2::toSet() const {
        LetterBag2 ret;
        if(this->isEmpty()) return ret;

        for(char c = 'a'; c <= 'z'; ++c)
            if(this->counts[c - 'a'] != 0) ++ret.counts[c - 'a'];
        return ret;
    }
};