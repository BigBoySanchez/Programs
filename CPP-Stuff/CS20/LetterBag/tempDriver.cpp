#include <iostream>
#include <string>
#include "LetterBag1.cpp"
#include <cstdlib>
#include <ctime>
using namespace std;
void getInfo1(const LetterBag1& b, const LetterBag1& c) {
cout << endl << "____________LetterBag1 Results_____________" << endl << endl;
cout << "b = " << b << " or \"" << b.toString() << "\", size=" << b.getSize();
if (b.isEmpty()) cout << " (b is empty)";
else
{
cout << ", letter counts: ";
for (char ch = 'a'; ch <= 'z'; ch++) {
if (b.contains(ch)) {
cout << "(" << ch << "," << b.getCount(ch) << ")";
}
}
}
cout << "." << endl;
cout << "c = " << c << " or \"" << c.toString() << "\", size=" << c.getSize();
if (c.isEmpty()) cout << " (c is empty)";
else
{
cout << ", letter counts: ";
for (char ch = 'a'; ch <= 'z'; ch++) {
if (c.contains(ch)) {
cout << "(" << ch << "," << c.getCount(ch) << ")";
}
}
}
cout << "." << endl;
cout << "b == c: " << (b == c) << endl;
cout << "b != c: " << (b != c) << endl;
cout << "b < c: " << (b < c) << endl;
cout << "b <= c: " << (b <= c) << endl;
cout << "b > c: " << (b > c) << endl;
cout << "b >= c: " << (b >= c) << endl;
cout << "b subbag c: " << b.isSubbagOf(c) << endl;
cout << "c subbag b: " << c.isSubbagOf(b) << endl;
cout << "b union c = " << b.getUnion(c) << endl;
cout << "c union b = " << c.getUnion(b) << endl;
cout << "___________________________________________ " << endl << endl;
}

int main() {
    LetterBag1 b("acehpp");
    LetterBag1 c("acehp");

    getInfo1(b, c);
    
    return 0;
}