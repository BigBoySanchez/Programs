#include "wordTree.h"

void insertWord(letterNode * root, const std::string & word) {
    for(std::size_t i = 0; i < word.length(); i++) {
        char c = toupper(word[i]);
        letterNode * curr = root->kids[c - 'A'];

        if(curr == nullptr) {
            curr = new letterNode;
            if(curr == nullptr) throw "ERROR: Could not make new node.\n";

            root->kids[c - 'A'] = curr;
        }

        root = curr;
    }

    root->isWord = true;
}

void insertFromDict(letterNode * root, 
                    const std::string& filepath, 
                    const unsigned int TO_SKIP, 
                    const unsigned int MIN, 
                    const unsigned int MAX) {
    
    std::ifstream dictionary;
    std::string toInsert;
    
    dictionary.open(filepath);
    if(!dictionary.is_open()) throw std::runtime_error("Could not open dictionary.\n");

    //skip first (TO_SKIP) lines of dictionary
    for(int i = 0; i < TO_SKIP; i++) dictionary.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(dictionary >> toInsert) 
        if(toInsert.length() >= MIN && toInsert.length() <= MAX) 
            insertWord(root, toInsert);
    
    dictionary.close();
}

void clearTree(letterNode * root) {
    if(root == nullptr) return;
    
    for(size_t i = 0; i < NUM_LETTERS; i++) clearTree(root->kids[i]);

    delete root;
}