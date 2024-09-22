#include <string>

typedef enum suit {
    NO_SUIT = 0,
    CLUBS = 1,
    DIAMONDS = 2,
    HEARTS = 3,
    SPADES = 4
} suit;

class Card {
public:
    Card();
    Card(const std::string& info);
    std::string getInfo() const;
    int compareTo(const Card& other) const;

private:
    // info = suit + value
    std::string info;

    suit charToSuit(char toConvert) const;
    int faceToValue(char toConvert) const;
};

class ItemType {
public:
    ItemType();
    ItemType(const Card& info);
    Card getInfo() const;

private:
    Card info;
};

class SortedList {
public:
    SortedList(size_t size = 0);
    void putItem(ItemType toPut);

    // does nothing if toDelete isn't in list
    void deleteItem(const ItemType& toDelete);
    ItemType getItem(const ItemType& toGet, bool& found) const;
    void printAll() const;

    // returns int > 0 if this > other,
    // int < 0 if this < other
    // 0 if this == other
    int compareTo(const ItemType& curr, const ItemType& other) const;
    bool isFull() const;
    size_t size() const;

private:
    ItemType *arr;
    size_t capacity;
    size_t length;
};