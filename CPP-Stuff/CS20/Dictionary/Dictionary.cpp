#include "Dictionary.h"

AnagramSet * Dictionary::find(AnagramSet * head, const LetterBag & key) const {
    if(head && head->key == key) return head;
    AnagramSet * prev = findPrevious(head, key);

    return prev;
}

AnagramSet * Dictionary::findWord(const string &w) const {
    LetterBag stringToBag(w);

    return find(hashTable[AnagramSet(stringToBag).hashKey(tableSize)], stringToBag);
}

AnagramSet * Dictionary::findPrevious(AnagramSet * head, const LetterBag & key) const {
    if(!head) return nullptr;

    while(head->next) {
        if(head->next->key == key) return head;
        head = head->next;
    }

    return nullptr;
}

void Dictionary::insertNew(int index, AnagramSet * toInsert) {
    toInsert->next = hashTable[index];
    hashTable[index] = toInsert;
}

Dictionary::Dictionary() {
    numWords = 0;
}

Dictionary::Dictionary(string fileName) {
    numWords = 0;
    ifstream wordsStream;
    wordsStream.open(fileName);

    if(!wordsStream.is_open()) throw "Could not open \"" + fileName + "\".\n";

    //WIP may extract weird chars
    while(!wordsStream.eof()) {
        string newWord;
        wordsStream >> newWord;
        insertWord(newWord);
    }

    wordsStream.close();
}

Dictionary::Dictionary(string words[], int arraySize) {
    numWords = 0;
    for(int i = 0; i < arraySize; i++) insertWord(words[i]);
}

Dictionary::Dictionary(const Dictionary & d) {
    for(int i = 0; i < tableSize; i++) {
        if(!d.hashTable[i]) continue;

        hashTable[i] = new AnagramSet(d.hashTable[i]->key);
        AnagramSet * thisCurr = hashTable[i], * dCurr = d.hashTable[i]->next;

        while(dCurr) {
            thisCurr->next = new AnagramSet(d.hashTable[i]->key);

            thisCurr = thisCurr->next;
            dCurr = dCurr->next;
        }
    }

    numWords = d.numWords;
}

int Dictionary::getNumWords() const {
    return numWords;
}

Dictionary::~Dictionary() {
    clear();
}

void Dictionary::clear() {
    for(int i = 0; i < tableSize; i++) {
        AnagramSet * curr = hashTable[i];

        while(curr) {
            AnagramSet *toDelete = curr;
            curr = curr->next;

            delete toDelete;
        }
    }

    numWords = 0;
}

bool Dictionary::insertWord(const string &w) {
    LetterBag stringToBag(w);
    int keyHash = AnagramSet(stringToBag).hashKey(tableSize);
    AnagramSet * set = find(hashTable[keyHash], stringToBag);

    if(set) {
        int ogSize = set->getSize();
        set->insert(w);
        numWords += set->getSize() - ogSize;
        return set->getSize() != ogSize;
    } else {
        insertNew(keyHash, new AnagramSet(stringToBag));
        numWords++;
        return true;
    }
}

int Dictionary::insertWords(const vector<string> & v) {
    int numInserted = 0;
    for(int i = 0; i < v.size(); i++) numInserted += insertWord(v[i]);
    return numInserted;
}