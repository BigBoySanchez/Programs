#include "Fraction.h"
#include <iostream>

int main()
{
    Fraction funny;
    funny.numerator = 3;
    funny.denominator = 5;

    Fraction real;
    real.numerator = 5;
    real.denominator = -25;

    std::cout << "funny = " << funny << '\n';
    std::cout << "real = " << real << "\n\n";

    real += funny;
    std::cout << "+= operator: " << real << "\n";

    return 0; 
}