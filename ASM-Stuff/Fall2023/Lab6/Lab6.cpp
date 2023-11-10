//
// Lab6.cpp
//
// Jacob Ativo, Ganeev Sidhu
// 11/7
// Using the shifting 
// multiply method in C++
//

#include <iostream>
using namespace std;

int main()
{
    unsigned int num1, num2, result = 0, check;

    cout << "\nEnter the first number: ";
    cin >> num1;

    cout << "Enter the second number: ";
    cin >> num2;

    //need to do this before shifting 
    check = num1 * num2;

    while(num1 != 0)
    {
        //adds num2 * 2^n iff num1 / 2^n is odd
        result += num2 * (num1 & 1);

        num1 = num1 >> 1;
        num2 = num2 << 1;
    }

    cout << "\nThe result from shifting: " << result;
    cout << "\nThe real result: " << check << '\n';
    
    return 0;
}