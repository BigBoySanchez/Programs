//Name: Jacob Ativo 
//NetID: gd340
//Email: jativo@horizon.csueastbay.edu

#include "hw3.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

Card::Card() {
    info = "";
}

Card::Card(const std::string& info) {
    this->info = info;
}

std::string Card::getInfo() const {
    return info;
}

int Card::compareTo(const Card& other) const {
    if(info.empty() || other.info.empty())
        throw std::runtime_error("Can't compare empty card\n");
    
    int eval = 0;

    // compare suits
    eval = charToSuit(info[0]) - charToSuit(other.info[0]);
    eval *= 13; // since values are 2-14

    // compare values
    try {
        eval += std::stoi(info.substr(1));
    } catch(const std::invalid_argument& ia) {
        eval += faceToValue(info[1]);
    }

    try {
        eval -= std::stoi(other.info.substr(1));
    } catch(const std::invalid_argument& ia) {
        eval -= faceToValue(other.info[1]);
    }

    return eval;
}

suit Card::charToSuit(char toConvert) const {
    switch(toupper(toConvert)) {
    case 'C':
        return CLUBS;
    case 'D':
        return DIAMONDS;
    case 'H':
        return HEARTS;
    case 'S':
        return SPADES;    
    }

    return NO_SUIT;
}

int Card::faceToValue(char toConvert) const {
    switch (toupper(toConvert)) {
    case 'J':
        return 11;
    case 'Q':
        return 12;
    case 'K':
        return 13;
    case 'A':
        return 14;
    }

    return 0;
}

ItemType::ItemType() {
    info = Card();
}

ItemType::ItemType(const Card& info) {
    this->info = info;
}

Card ItemType::getInfo() const {
    return info;
}

SortedList::SortedList(size_t size) {
    arr = new ItemType[size];
    if(arr == nullptr)
        throw std::runtime_error("No space for SortedList of size " + 
                                 std::to_string(size) + ".\n");

    capacity = size;
    length = 0;
}

void SortedList::putItem(ItemType toPut) {
    int curr = length;

    if(isFull()) throw std::length_error("Too many cards.\n");
    
    while(curr > 0) {
        arr[curr] = arr[curr - 1];

        if(compareTo(arr[curr], toPut) <= 0) {
            arr[curr] = toPut;
            break;
        }

        curr--;
    }
    if(length == 0) arr[0] = toPut;

    length++;
}

void SortedList::deleteItem(const ItemType& toDelete) {
    int l = 0, r = length - 1, m;

    // find toDelete in list
    while(l < r) {
        m = l + ((r - l) / 2);
        
        if(compareTo(arr[m], toDelete) > 0) {
            r = m - 1;
        } else if(compareTo(arr[m], toDelete) < 0) {
            l = m + 1;
        } else {
            break;
        }
    }
    if(length == 0 || compareTo(arr[m], toDelete) != 0) return;

    // now arr[m] needs to be removed
    while(m < length - 1) {
        arr[m] = arr[m + 1];

        m++;
    }

    length--;
}

ItemType SortedList::getItem(const ItemType& toGet, bool& found) const {
    int l = 0, r = length - 1, m;
    
    found = false;
    if(length == 0) return ItemType();

    while(l < r) {
        m = l + ((r - l) / 2);

        if(compareTo(arr[m], toGet) > 0) {
            r = m - 1;
        } else if(compareTo(arr[m], toGet) < 0) {
            l = m + 1;
        } else {
            found = true;
            break;
        }
    }

    return arr[m];
}

void SortedList::printAll() const {
    std::cout << "List:";

    for(int i = 0; i < length; i++) {
        if(i != 0) std::cout << ", ";
        std::cout << arr[i].getInfo().getInfo();
    }
}

int SortedList::compareTo(const ItemType& curr, const ItemType& other) const {
    return curr.getInfo().compareTo(other.getInfo());
}

bool SortedList::isFull() const {
    return length >= capacity;
}

int main() {
    std::ifstream fin("./HW3DataFile.txt");
    std::string currLine;

    if(!fin.is_open()) throw std::runtime_error("Could not open data file.\n");

    //Create a list by dynamic allocated array and set the size to 20
    SortedList deck(20);

    // Read  the  first  20  different  cards  in  the  first  line  of  the  file,  
    std::getline(fin, currLine);
    if(currLine.back() == '\r') currLine.pop_back();

    // then  put  them  one  by  one into  the  list  by  implementing  and  using  putItem().
    for(int i = 0; !deck.isFull() && i < currLine.size(); i++) {
        bool found;
        ItemType toAdd;
    }

    fin.close();

    return 0;
}