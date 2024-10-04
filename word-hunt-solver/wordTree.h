#ifndef WORD_TREE_H
#define WORD_TREE_H

#define NUM_LETTERS 26

#include <string>       
#include <stack>
#include <iostream>  
#include <fstream>
#include <limits>
#include <stdexcept>

typedef struct letterNode {
    struct letterNode * kids[NUM_LETTERS] = { nullptr };
    bool isWord = false; 
}letterNode;

//put word into root
void insertWord(letterNode * root, const std::string & word);

//put words from a dictionary into root
void insertFromDict(letterNode * root, 
                    const std::string& filename, 
                    const unsigned int TO_SKIP = 0, 
                    const unsigned int MIN = 1, 
                    const unsigned int MAX = UINT_MAX);

//delete root
void clearTree(letterNode * root);

#endif