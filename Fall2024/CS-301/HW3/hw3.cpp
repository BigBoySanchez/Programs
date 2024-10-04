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
        if(compareTo(arr[curr - 1], toPut) <= 0) {
            arr[curr] = toPut;
            break;
        }

        arr[curr] = arr[curr - 1];
        curr--;
    }
    if(curr == 0) arr[0] = toPut;

    length++;
}

void SortedList::deleteItem(const ItemType& toDelete) {
    int l = 0, r = length - 1;
    size_t m;

    // find toDelete in list
    while(l <= r) {
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

    while(l <= r) {
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
    for(size_t i = 0; i < length; i++) {
        if(i != 0) std::cout << ",";
        std::cout << arr[i].getInfo().getInfo();
    }
}

int SortedList::compareTo(const ItemType& curr, const ItemType& other) const {
    return curr.getInfo().compareTo(other.getInfo());
}

bool SortedList::isFull() const {
    return length >= capacity;
}

size_t SortedList::size() const {
    return length;
}

int main(int argc, char *argv[]) {
    std::ifstream fin;
    std::string currLine;
    size_t lineLoc;

    if(argc < 2) throw std::runtime_error("No file given.\n");

    fin.open(argv[1]);
    if(!fin.is_open()) throw std::runtime_error("Could not open data file.\n");

    //Create a list by dynamic allocated array and set the size to 20
    SortedList deck(20);

    // Read  the  first  20  different  cards  in  the  first  line  of  the  file,  
    std::getline(fin, currLine);
    if(currLine.back() == '\r') currLine.pop_back();

    // then  put  them  one  by  one into  the  list  by  implementing  and  using  putItem().
    lineLoc = 0;
    while(!deck.isFull()) {
        bool found;
        ItemType toAdd;
        std::string currStr = "";

        while(lineLoc < currLine.size() && isalnum(currLine[lineLoc])) {
            currStr += currLine[lineLoc];
            lineLoc++;
        }
        // ignore separators
        while(lineLoc < currLine.size() && !isalnum(currLine[lineLoc])) lineLoc++;
        if(currStr.empty()) break;
        
        toAdd = ItemType(Card(currStr));
        deck.getItem(toAdd, found);
        if(found) continue;

        deck.putItem(toAdd);
    }

    // Then print out all the cards in the list in one line separating by commas.
    deck.printAll();
    std::cout << "\n";

    // Then delete the cards indicated in the second line of the file by using deleteItem()
    std::getline(fin, currLine);
    if(currLine.back() == '\r') currLine.pop_back();

    lineLoc = 0;
    while(lineLoc < currLine.size()) {
        std::string currStr = "";

        while(lineLoc < currLine.size() && isalnum(currLine[lineLoc])) {
            currStr += currLine[lineLoc];
            lineLoc++;
        }
        // ignore separators
        while(lineLoc < currLine.size() && !isalnum(currLine[lineLoc])) lineLoc++;

        deck.deleteItem(ItemType(Card(currStr)));
    }

    // Then print out all the cards in the list in one line separating by commas.
    deck.printAll();
    std::cout << "\n";

    // Then put the items in the third line in to the list. Must use putItem()
    std::getline(fin, currLine);
    if(currLine.back() == '\r') currLine.pop_back();

    lineLoc = 0;
    while(!deck.isFull()) {
        ItemType toAdd;
        std::string currStr = "";

        while(lineLoc < currLine.size() && isalnum(currLine[lineLoc])) {
            currStr += currLine[lineLoc];
            lineLoc++;
        }
        // ignore separators
        while(lineLoc < currLine.size() && !isalnum(currLine[lineLoc])) lineLoc++;
        if(currStr.empty()) break;
        
        toAdd = ItemType(Card(currStr));
        deck.putItem(toAdd);
    }

    // Then print out all the cards in the list in one line separating by commas.
    deck.printAll();
    std::cout << "\n";

    // Search the current list for the elements in the list.
    std::getline(fin, currLine);
    if(currLine.back() == '\r') currLine.pop_back();

    lineLoc = 0;
    while(lineLoc < currLine.size()) {
        std::string currStr = "";
        bool found;

        while(lineLoc < currLine.size() && isalnum(currLine[lineLoc])) {
            currStr += currLine[lineLoc];
            lineLoc++;
        }
        // ignore separators
        while(lineLoc < currLine.size() && !isalnum(currLine[lineLoc])) lineLoc++;

        // Then output the result as the follows.  Yes or No 
        // depends on whether the card exists in the current list.
        deck.getItem(ItemType(Card(currStr)), found);
        
        std::cout << currStr << " ";
        if(found) std::cout << "YES";
        else std::cout << "NO";
        if(lineLoc < currLine.size()) std::cout << ", ";
    }
    std::cout << "\n";

    fin.close();

    return 0;
}