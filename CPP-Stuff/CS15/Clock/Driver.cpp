#include <iostream>
#include "Clock.cpp"
using namespace std;

int main()
{
    Clock chabotRN('p', true);
    Clock iHateDST('p', false);
    Clock pilipinas('i', true);
    Clock newZealand('z', true);
    Clock hawaii('h', false);
    Clock uk('u', false);

    cout << "Time at Chabot: ";
    chabotRN.printTime();

    cout << "\nTime without daylight savings: ";
    iHateDST.printTime();

    cout << "\nTime in the Philippines: ";
    pilipinas.printTime();

    cout << "\nChecking max value for zoneOffset (+12): ";
    newZealand.printTime();

    cout << "\nChecking min value for zoneOffset (-10): ";
    hawaii.printTime();

    cout << "\nChecking time without offset or dst: ";
    uk.printTime();
    
    cout << "\n";
    return 0;
}