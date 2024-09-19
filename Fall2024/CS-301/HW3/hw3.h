#include <string>

typedef enum suit {
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
} suit;

typedef enum face {
    A = 1,
    J = 11,
    Q = 12,
    K = 13
} face;


class Card {
public:
    Card(std::string info);
    std::string getInfo() const;

    // returns int > 0 if this > other,
    // int < 0 if this < other
    // 0 if this == other
    int compareTo(const Card& other) const;

private:
    std::string info;
};