#include <iostream>
#include <string>
#include "LetterBag1.cpp"
#include <cstdlib>
#include <ctime>
using namespace std;

void getInfo1(const LetterBag1 &b, const LetterBag1 &c)
{
    cout << endl
         << "____________LetterBag1 Results_____________" << endl
         << endl;
    cout << "b = " << b << " or \"" << b.toString() << "\", size=" << b.getSize();
    if (b.isEmpty())
        cout << " (b is empty)";
    else
    {
        cout << ", letter counts: ";
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            if (b.contains(ch))
            {
                cout << "(" << ch << "," << b.getCount(ch) << ")";
            }
        }
    }
    cout << "." << endl;
    cout << "c = " << c << " or \"" << c.toString() << "\", size=" << c.getSize();
    if (c.isEmpty())
        cout << " (c is empty)";
    else
    {
        cout << ", letter counts: ";
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            if (c.contains(ch))
            {
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
    cout << "___________________________________________ " << endl
         << endl;
}

void stressTest1(int iterations)
{
    cout << "STRESS TEST 1\t";
    cout << "Press Enter to start.";
    cin.get();
    time_t t0 = time(0);
    LetterBag1 b, c;
    int subbagCount = 0, lessThanCount = 0, greaterThanCount = 0, unionCount = 0,
        containsCount = 0, countAll = 0, notEqualCount = 0, lessOrEqualCount = 0,
        greaterOrEqualCount = 0, equalCount = 0, removeCount = 0;
    for (int i = 0; i < iterations; i++)
    {
        b.clear();
        c.clear();
        int offset = i % 10 == 0 ? 100 : 0;
        int range = rand() % 5 + 2;
        for (int j = 0; j < 1000 - offset; j++)
            b.insertOne(rand() % range + 'a');
        for (int j = 0; j < 1000 + offset; j++)
            c.insertOne(rand() % range + 'a');
        
        if (b.isSubbagOf(c))
            subbagCount++;
        if (b < c)
            lessThanCount++;
        if (b > c)
            greaterThanCount++;
        if (b <= c)
            lessOrEqualCount++;
        if (b >= c)
            greaterOrEqualCount++;
        if (b == c)
            equalCount++;
        if (b != c)
            notEqualCount++;
        if (b.getUnion(c) == c.getUnion(b))
            unionCount++;
        if (b.contains('z') || c.contains('f'))
            containsCount++;
        
        
        //getInfo1(b, c);
        
        for (char ch = 'a'; ch <= 'z'; ch++)
            countAll += b.getCount(ch) + c.getCount(ch);
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            while (b.contains(ch))
            {
                b.removeOne(ch);
                removeCount++;
            }
            while (c.contains(ch))
            {
                c.removeOne(ch);
                removeCount++;
            }
        }
    }
    cout << "subbagCount = " << subbagCount << endl;
    
    cout << "lessThanCount = " << lessThanCount << endl;
    cout << "greaterThanCount = " << greaterThanCount << endl;
    cout << "lessOrEqualCount = " << lessOrEqualCount << endl;
    cout << "greaterOrEqualCount = " << greaterOrEqualCount << endl;
    cout << "equalCount = " << equalCount << endl;
    cout << "notEqualCount = " << notEqualCount << endl;
    cout << "unionCount = " << unionCount << endl;
    cout << "containsCount = " << containsCount << endl;
    cout << "countAll = " << countAll << endl;
    cout << "removeCount = " << removeCount << endl;

    cout << "Elapsed time = " << time(0) - t0 << endl
         << endl;
}

int main() {
    LetterBag1 b("hey peter");
    LetterBag1 c("SEnter number of iterations for stress tests: ");

    cout << boolalpha;
    getInfo1(b, c);
    
    int iterations;
    cout << "Enter number of iterations for stress tests: ";
    cin >> iterations;
    cin.ignore(80, '\n');
    stressTest1(iterations);
    //stressTest2(iterations);
    return 0;
}