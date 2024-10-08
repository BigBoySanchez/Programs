#include <iostream>
#include "AnagramSet.h"
#include "Dictionary.h"
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
const int maxWords = 13000000;
string  words[maxWords];

int tfine; // used for timer

void resetTimer() ;  // reset the timer
int getTime();  // get elapsed time

// read file into wordList. Return number of words read in
int readInWords(string wordList[],  int maxSize, string fileName) ;

void countAnagrams( Dictionary & d, int howMany, string wordList[], int length) ;

// count the number of words in wordList that are in d
void countHits (string wordList[], int length,  Dictionary & d);

// write the dictionary to a file
void toFile(const Dictionary & d, const string & fileName) ;



// find words whose letters match a given string
void unScramble(Dictionary & d);

int main() {

	int  tableSize;
	cout << "What is the hash table size? ";
	cin >> tableSize;
	resetTimer();
	string fileName;
	cout << "What is the file name? ";
	cin >> fileName;
	cout << "Starting" << endl;
	int numWords = readInWords(words, maxWords,fileName);
	cout << "Read in " << numWords << " words " << endl;
	cout << "Done reading words, elapsed time = " << getTime() << endl << endl;
	
	resetTimer();
	Dictionary d(words, numWords);
	cout << "Done creating dictionary, elapsed time = " << getTime() << endl;
	countHits(words,numWords,d);

	countAnagrams(d,120, words, numWords);


	unScramble(d);
	resetTimer();
	for (int i = 0, count = 0; count  <= numWords/2; i =  (i+ 30011)% numWords, count++) 
		d.removeWord(words[i]);
	cout << "Done removing half the words, elapsed time = " << getTime() << endl << endl;
	unScramble(d);
	resetTimer();
	toFile(d, "tester2out.txt");
	cout << "Done writing to file, elapsed time = " << getTime() << endl << endl;
	cout << "Bye!" << endl;
	return 0;
}


void resetTimer() {
	tfine = clock();
}

int getTime() {
	return clock() - tfine;
}

int readInWords(string wordList[],  int maxSize, string fileName) {
    int i = 0;
	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile) cout <<"Failed to open file" << endl;
    while (infile && i < maxSize) {
        string s;
        infile >> s;
        if (infile) {
            wordList[i] = s;
            i++;
        }
    }
    return i;  // the number of words read in
}

void countHits (string wordList[], int length,  Dictionary & d) {
	resetTimer();	 
	int count = 0;
	for (int i = 0; i < length; i++) 
		if (d.contains(wordList[i]) )
			count++;
	cout << "Hit count = " << count
		<< ",  elapsed time = " << getTime() << endl << endl;
}


void toFile(const Dictionary & d, const string & fileName) {
	ofstream out;
	out.open(fileName.c_str());
	d.printDictionary(d.tableSize, out);
	out.close();
}

void countAnagrams(Dictionary & d, int howMany, string wordList[], int length) {
    // There's a faster way of counting if we know d contains the same words
    // as wordList, but for the sake of testing we'll ignore that fact.
    resetTimer();
    int sum = 0;
    for (int i = 0; i < length; i++) {
        vector<string> v = d.getWords(wordList[i]);
        if (v.size() == howMany)
            sum++;
    }
    cout << "Found " << setw(5) << sum
        << " words with  " << setw(3) << howMany << " anagramatic forms. Elapsed time = "
        << getTime() << endl;
}



void unScramble(Dictionary & d) {
	string s;
	do {
		cout << "Enter an anagram or . to quit: ";
		cin >> s;
		if (s != ".") {
			vector<string>  v = d.getWords(s);
			if (v.empty())
				cout << "Not found " << endl;
			else {
				cout << "Found it: ";
				for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
				cout << endl;
			}

		}
	} while (s != ".");
}