//Name: Jacob Ativo 
//NetID: gd3470
//Email: jativo@horizon.csueastbay.edu

using namespace std;

#include "./hw4.h"
#include <fstream>
#include <string>
#include <iostream>

ItemType::ItemType(char info) {
    this->info = info;
}

char ItemType::getInfo() const {
    return info;
}

DoubleList::DoubleList() {
    head = nullptr;
    tail = nullptr;
}

DoubleList::~DoubleList() {
    while(head) {
        NodeType *temp = head;
        head = head->next;

        delete temp;
    }
}

NodeType *DoubleList::begin() const {
    return head;
}

NodeType *DoubleList::end() const {
    return tail;
}

void DoubleList::putItem(const ItemType& toPut) {
    if(!tail) {
        head = new NodeType(toPut);
        tail = head;

        return;
    }

    tail->next = new NodeType(toPut, tail);
    tail = tail->next;
}


int main(int argc, char **argv) {
    // Create a doubly linked list by reading the 26 letters from Letters.txt.
    DoubleList dl;
    ifstream letterFile(argv[2]);
    if(!letterFile.is_open()) throw runtime_error("Could not open Letters.\n");

    string currLine;
    while(!letterFile.eof()) {
        getline(letterFile, currLine);

        dl.putItem(ItemType(currLine[0]));
    }
    letterFile.close();

    // The initial position is at the beginning of the list which is ‘A’.
    NodeType *loc = dl.begin();

    // You need to output all letters indicated in sequence.txt
    ifstream seqFile(argv[1]);
    if(!seqFile.is_open()) throw runtime_error("Could not open Sequence.\n");
    string curr;

    // look at numbers in sequence individually
    while(!seqFile.eof()) {
        getline(seqFile, curr, ',');

        // move loc by relative position
        loc = loc->getAt(stoi(curr));
        cout << loc->info.getInfo();
    }
    cout << "\n";
    seqFile.close();
    
    return 0;
}