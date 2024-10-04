#include "SortedPair.h"
#include <iostream>


int main()
{
    SortedPair<int> pair1(9, 10);
    SortedPair<char> pair2('p');
    SortedPair<int> pair3(11, 5);

    //testing constructor + operator<<
    std::cout << "pair1: " << pair1;
    std::cout << "\npair2: " << pair2;
    std::cout << "\npair3: " << pair3;

    //testing accessors
    std::cout << "\npair1 b: " << pair1.getB();
    std::cout << "\npair2 c: " << pair1.getC();
    std::cout << "\npair3 b: " << pair3.getB();

    //testing mutators + swaps
    pair1.setB(69);
    pair2.setB('Q');
    pair3.setC(9);

    std::cout << "\nBEFORE SWAPS:           AFTER:";
    std::cout << "\npair1 (b = 69, c = 10): " << pair1;
    std::cout << "\npair2 (b = null, c = Q): " << pair2;
    std::cout << "\npair3 (b = 11, c = 9): " << pair3;
}