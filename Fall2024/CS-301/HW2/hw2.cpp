//Name: Jacob Ativo 
//NetID: gd3470
//Email: jativo@horizon.csueastbay.edu

#include "./hw2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

ItemType::ItemType(int number) {
    value = number;
}

int ItemType::getValue() const {
    return value;
}

UnsortedType::UnsortedType() {
    head = nullptr;
}

UnsortedType::~UnsortedType() {
    while(head) {
        deleteItem(head->info.getValue());
    }
}

void UnsortedType::putItem(ItemType toAdd) {
    if(!head) {
        head = new NodeType{toAdd, nullptr};
        return;
    }
    
    NodeType *curr = head;
    while(curr->next) {
        curr = curr->next;
    }
    curr->next = new NodeType{toAdd, nullptr};
}

void UnsortedType::putItem(ItemType toAdd, int position) {
    if(position == 0) {
        head = new NodeType{toAdd, head};   // WIP errm... what the sigma
        return;
    }
    
    NodeType *curr = head;
    int i = 1;
    while(i < position && curr->next) {    //Get curr to node before position
        curr = curr->next;
        i++;
    }
    if(i == position) curr->next = new NodeType{toAdd, curr->next};
}

void UnsortedType::deleteItem(int key) {
    NodeType *temp = nullptr;
    
    if(head->info.getValue() == key) {
        temp = head;
        head = head->next;
        delete temp;

        return;
    }
    
    for(NodeType *curr = head; curr->next; curr = curr->next) {
        if(curr->next->info.getValue() == key) {
            temp = curr->next;
            curr->next = curr->next->next;
            delete temp;

            return;
        } 
    }
}

void UnsortedType::printAll(NodeType *head) const {
    std::cout << "List:";
    while(head) {
        std::cout << " " << head->info.getValue();
        if(head->next) std::cout << ",";

        head = head->next;
    }
}

NodeType* UnsortedType::getHead() const {
    return head;
}

int main(int argc, char *argv[]) {
    // WIP declarations
    if(argc < 2) throw std::runtime_error("ERROR: No file given.\n");
    std::ifstream fin(argv[1]);
    std::stringstream sstream;
    std::string currLine = "";
    std::string currStr = "";

    // Create an empty unsorted list by yourself
    UnsortedType list;
    
    // just in case...
    if(!fin.is_open()) 
        throw std::runtime_error("ERROR: Could not open file.\n");

    // Add the numbers from the first line to the list using putItem() function
    std::getline(fin, currLine);
    sstream.str(currLine);
    while(sstream >> currStr) {
        list.putItem(ItemType(std::stoi(currStr)));
    }
    // Then print all the current keys to command line in one line using printAll()
    list.printAll(list.getHead());
    std::cout << "\n";

    // Delete the numbers given by the second line in the list by using deleteItem() function
    std::getline(fin, currLine);
    sstream.str(currLine);
    sstream.clear();
    while(sstream >> currStr) {
        list.deleteItem(std::stoi(currStr));
    }
    // Then print all the current keys to command line in one line using printAll()
    list.printAll(list.getHead());
    std::cout << "\n";

    // putItem () the numbers in the third line of the data file 
    // to the corresponding location in the list. For example, 
    // 1@0 means adding number 1 at position 0 of the list
    std::getline(fin, currLine);
    sstream.str(currLine);
    sstream.clear();
    while(sstream >> currStr) {
        const size_t at = currStr.find('@');
        ItemType key;

        try {
            key = ItemType(std::stoi(currStr.substr(0, at)));
        } catch(const std::invalid_argument& ia) {
            key = ItemType();
        }

        try {
            list.putItem(key, std::stoi(currStr.substr(at + 1)));
        } catch(const std::invalid_argument& ia) {
            list.putItem(key);
        }
    }
    // Then print all the current keys to command line in one line using printAll()
    list.printAll(list.getHead());
    std::cout << "\n";

    fin.close();
    
    return 0;
}