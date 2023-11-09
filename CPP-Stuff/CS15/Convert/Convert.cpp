/*
if div > base, keep going

*/

#include<string>
#include<iostream>
#include <cmath>
using namespace std;

string convert(long long int n, int b);

int main()
{
    cout << convert(0,2);
    cout << '\n' << convert(-630, 5);
    cout << '\n' << convert(1234567890,10);
    cout << '\n' << convert(94122949033327355,36);
    cout << '\n' << convert(9223372036854775807, 2);
    cout << '\n' << convert(9223372036854775807, 8);
    cout << '\n' << convert(-9223372036854775807, 32);

    cout << '\n' << convert(-8196, 16);
    cout << '\n' << convert(256, 3);
    cout << '\n' << convert(69696969, 1);
    cout << '\n' << convert(-69420, 420);
    cout << '\n' << convert(-450, 7);
    cout << '\n' << convert(2000, 2);
    cout << '\n' << convert(-720, 6);
    cout << '\n' << convert (255, 8);

    return 0;
}

string convert(long long int n, int b)
{
    if(b > 36 || b < 2) return "Illegal Base";
    if(n < 0) return "-" + convert(-n, b);
    
    string temp = "";
    if(n % b >= 10) temp = (n % b) + 55; 
    else temp = (n % b) + 48;

    if(n < b) return temp;  
    else return convert(n / b, b) + temp;
    
}