#include <iostream>
#include <string>
#include "LetterBag1.cpp"
#include "LetterBag2.cpp"
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
void getInfo2(const LetterBag2 &b, const LetterBag2 &c)
{
    cout << endl
         << "____________LetterBag2 Results_____________" << endl
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
void stressTest2(int iterations)
{
    cout << "STRESS TEST 2\t";
    cout << "Press Enter to start.";
    cin.get();
    time_t t0 = time(0);
    LetterBag2 b, c;
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
int main()
{
    cout << boolalpha;
    srand((unsigned int)(time(0)));
    cout << "Enter a string to initialize b: ";
    string s;
    getline(cin, s);
    LetterBag1 b1(s);
    LetterBag2 b2(s);
    cout << "Enter a string to initialize c: ";
    getline(cin, s);
    LetterBag1 c1(s);
    LetterBag2 c2(s);
    char ch;
    int choice;
    getInfo1(b1, c1);
    getInfo2(b2, c2);
    bool quit = false;
    do
    {
        cout << "Select an option below. " << endl
             << endl;
        cout << "1) insert to b " << endl;
        cout << "2) remove from b " << endl;
        cout << "3) insert to c" << endl;
        cout << "4) remove from c" << endl;
        cout << "5) clear b " << endl;
        cout << "6) clear c " << endl;
        cout << "7) QUIT " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter char: ";
            std::cin >> ch;
            b1.insertOne(ch);
            b2.insertOne(ch);
            break;
        case 2:
            cout << "Enter char: ";
            std::cin >> ch;
            b1.removeOne(ch);
            b2.removeOne(ch);
            break;
        case 3:
            cout << "Enter char: ";
            std::cin >> ch;
            c1.insertOne(ch);
            c2.insertOne(ch);
            break;
        case 4:
            cout << "Enter char: ";
            std::cin >> ch;
            c1.removeOne(ch);
            c2.removeOne(ch);
            break;
        case 5:
            b1.clear();
            b2.clear();
            break;
        case 6:
            c1.clear();
            c2.clear();
            break;
        default:
            quit = true;
        }
        if (!quit)
        {
            getInfo1(b1, c1);
            getInfo2(b2, c2);
        }
    } while (!quit);
    int iterations;
    cout << "Enter number of iterations for stress tests: ";
    cin >> iterations;
    cin.ignore(80, '\n');
    stressTest1(iterations);
    stressTest2(iterations);
    return 0;
}
