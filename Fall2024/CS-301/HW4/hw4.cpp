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

        cout << temp->info.getInfo() << "|\n";
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


int main(int argc, char *argv[]) {
    // Create a doubly linked list by reading the 26 letters from Letters.txt.
    DoubleList dl;
    ifstream inFile(argv[2]);

    // WIP: sux
    string currLine;
    while(!inFile.eof()) {
        getline(inFile, currLine);

        dl.putItem(ItemType(currLine[0]));
    }



    
    return 0;
}