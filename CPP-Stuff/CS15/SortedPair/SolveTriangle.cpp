#include "SortedPair.h"

#include <iostream>
#include <cmath>
using namespace std;

SortedPair<double> solveTriangle(const SortedPair<double> &legs)
{
    SortedPair<double> retObj(atan(legs.getB() / legs.getC()) * 180 / M_PI, atan(legs.getC() / legs.getB()) * 180 / M_PI);
    return retObj;
}

int main() 
{
    double l1, l2;

    cout << "Enter the two legs of a right triangle (separated by a space): ";
    cin >> l1 >> l2;

    SortedPair<double> t3(l1, l2);

    cout << "The two acute angles are: " << solveTriangle(t3).getB() << " degrees and " << solveTriangle(t3).getC() << " degrees.\n";
}