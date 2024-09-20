//Name: Jacob Ativo 
//NetID: gd340
//Email: jativo@horizon.csueastbay.edu

#include "hw3.h"
#include <string>

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
    eval *= 13;

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

    length = 0;
}

int main() {


    return 0;
}