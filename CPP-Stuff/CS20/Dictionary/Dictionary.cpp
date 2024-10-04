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
            thisCurr->next = new AnagramSet(dCurr->key);

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
    //make sure w is a word
    if(!isalnum(w[0])) return false;

    AnagramSet * set = findWord(w);

    if(set) {
        int ogSize = set->getSize();
        set->insert(w);
        numWords += set->getSize() - ogSize;
        return set->getSize() != ogSize;
    } else {
        AnagramSet * toInsert = new AnagramSet(LetterBag(w));
        toInsert->insert(w);
        if(!toInsert) throw "Could not make new Anagramset.\n";
        insertNew(toInsert->hashKey(tableSize), toInsert);
        numWords++;
        return true;
    }
}

int Dictionary::insertWords(const vector<string> & v) {
    int numInserted = 0;
    for(int i = 0; i < v.size(); i++) numInserted += insertWord(v[i]);
    return numInserted;
}

bool Dictionary::removeWord(string & w) {
    //get set w/ key = to stringToBag
    LetterBag stringToBag(w);
    int index = AnagramSet(stringToBag).hashKey(tableSize);
    AnagramSet * head = hashTable[index];
    AnagramSet * prevSet = findPrevious(head, stringToBag);
    if(!prevSet && (!head || head->key != stringToBag)) return false;

    int ogWords = numWords;
    if(head->key == stringToBag) {
        numWords -= head->getSize();
        head->remove(w);
        numWords += head->getSize();

        //remove head if empty
        if(!head->getSize()) {
            delete head;
            hashTable[index] = nullptr;
        }
    } else {
        numWords -= prevSet->next->getSize();
        prevSet->next->remove(w);
        numWords += prevSet->next->getSize();

        //remove next set if empty
        if(!prevSet->next->getSize()) {
            AnagramSet * toDelete = prevSet->next;
            prevSet->next = toDelete->next;

            delete toDelete;
        }   
    }

    return ogWords != numWords;
}

bool Dictionary::contains(string & word) const {
    LetterBag stringToBag(word);
    int index = AnagramSet(stringToBag).hashKey(tableSize);

    //needs this bc there's another find
    return this->find(hashTable[index], stringToBag);
}

vector<string> Dictionary::getWords(const string & word) const {
    AnagramSet * set = findWord(word);
    return (set)? set->getWords() : vector<string>();
}

int Dictionary::getNumAnagrams(const string & word) const {
    LetterBag stringToBag(word);
    int index = AnagramSet(stringToBag).hashKey(tableSize);

    return this->find(hashTable[index], stringToBag)->getSize();
}

void Dictionary::printDictionary(int limit, ostream & out) const {
    for(int i = 0, numPrinted = 0; numPrinted < limit && i < tableSize; i++) {
        AnagramSet * curr = hashTable[i];
        if(!curr) continue;
        
        out << setw(6) << i << "..." << setw(9);
        while(curr->next) {
            out << *curr << "  ";
            numPrinted++;
            curr = curr->next;
        }
        out << *curr << "\n";
        numPrinted++;
    }
}