//#include "AnagramSet.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>
using namespace std;
void printWords(vector<string> v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}
//string words[200000];
//int numWords = 0;
int main() {
    char response;
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    Dictionary d(fileName);
    cout << "Here is the dictionary..." << endl;
    d.printDictionary(500);
    bool done = false;
    while (!done) {
        string s;
        cout << "Enter an anagram: ";
        cin >> s;

        vector<string> v = d.getWords(s);
        if (v.empty()) 
            cout << "No matches..." << endl;
        else {
            cout << "Matching words are: ";
            printWords(v);
        }
        cout << "Enter a list of words to insert followed by 'q': ";
        do {
            cin >> s;
            if (s != "q") d.insertWord(s);
        } while (s != "q");
        cout << "The words were inserted. " << endl;
        cout << "Enter a list of words to remove followed by 'q': ";
        int removeCount = 0;
        do {
            cin >> s;
            if (s != "q") {
                if (d.removeWord(s)) {
                    cout << "\"" <<s << "\" was removed. " << endl;
                    removeCount++;
                }
            }
        } while (s != "q");
        cout << removeCount <<  (removeCount == 1 ? " word was" : " words were") << " removed. " << endl;
        cout << "The new dictionary is..." << endl;
        d.printDictionary(500);
        cout << "Continue? ";
        cin >> response;
        if (response != 'y') done = true;
    }
    cout << "Bye!" << endl;
    return 0;
}
/*
const int wordListSize = 80001;
AnagramSet *dictionary2[wordListSize];

int main() {
    ifstream  infile;
    infile.open("words.txt");
    if (!infile) {
        cout << "File not found. Exiting." << endl;
        return 1;
    }
    int anagramCount = 0;
    while (infile) {
        string s;
        infile >> s;

        if (infile) {
            LetterBag b(s);
            int i = 0;
            for (; i < anagramCount; i++) {
                if (dictionary2[i]->key == b) {
                    dictionary2[i]->insert(s);
                    break;
                }
            }
            if (i == anagramCount) {
                dictionary2[anagramCount] = new AnagramSet(b);
                dictionary2[anagramCount++]->insert(s);
                if (anagramCount % 10000 == 0) cout << anagramCount << endl;
                if (anagramCount >= wordListSize) break;
            }
        }
    }
    cout << anagramCount << endl;
    bool playAgain = true;
    while (playAgain) {
        cout << "Enter anagram & minimum result size: ";
        string s;
        int minSize;
        cin >> s >> minSize;
        LetterBag letters(s);
        bool foundOne = false;
        for (int i = 0; i < anagramCount; i++)
            if (dictionary2[i]->key.getCurrentSize() >= minSize && letters.isSubbag(dictionary2[i]->key)) {
                foundOne = true;
                AnagramSet set = *dictionary2[i];
                cout << set << endl;
                cout << "Enter a word: ";
                string wd;
                cin >> wd;
                set.insert(wd);
                cout << set << endl;
                cout << set.contains(wd) << endl;
                set.remove(wd);
                cout << set << endl;
                cout << set.contains(wd) << endl;
                //cout << (*dictionary2[i]) << endl;
            }
        if (!foundOne) cout << "No matches found." << endl;
        cout << endl << "Play again (y/n) ? ";
        char response;
        cin >> response;
        playAgain = response == 'y';
    }

  
    cout << "Bye" << endl;
    
    return 0;
}
*/