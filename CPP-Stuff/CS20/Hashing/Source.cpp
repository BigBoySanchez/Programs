#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

//aaaa  aaab aaba   ...  zzzz  --> 26^4

// aaaaaaaaaaaaaaa ... zzzzzzzzzzzzzzz  --> 26^13 possible strings

// So map each string to a number then mod bay the hash table size. 


unsigned int oldHash(const string& s, int size) {
	unsigned int h = s[0];
	for (int i = 1; i < s.length(); i++)
		h = h + s[i];

	return h % size;
	// cares  --> 210  races, acres,  scare --> 210  zero --> 210
}


unsigned int newHash(const string& s, int size) {
	return rand() % size;
}

unsigned int dopeHash(const string& s, unsigned int size) {
	unsigned int hash = 0;
	const unsigned int silly = 31;
	unsigned int currPow = 1;

	for(int i = 0; i < s.length(); i++) {
		hash = (hash + ((s[i] - 'a' + 1) * currPow)) % size;
		currPow = (currPow * silly) % size;
	}

	return hash;
}

void printHistogram(int histogram[], int length) {
	for (int i = 0; i < length; i++) {
		cout << left;
		cout << setw(5) << i;
		cout << setw(5) << histogram[i];
		for (int j = 0; j < histogram[i]; j++)
			if ((j + 1) % 50 == 0)
				cout << "*";
		cout << endl;
	}
}

void printArray(int nums[], int length) {
	for (int i = 0; i < length; i++)
		cout << nums[i] << " ";
	cout << endl;
}

void normalize(string& s) {
	string t = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] <= 'Z' && s[i] >= 'A')     s[i] += ('a' - 'A');
		if (s[i] <= 'z' && s[i] >= 'a')     t += s[i];
	}
	s = t;
}


int main() {
	srand(time(0));
	const int size = 10000, histSize = 10000;
	int collisionCounts1[size] = { 0 };
	int collisionCounts2[size] = { 0 };
	
	ifstream in;
	int histogram1[histSize] = { 0 };
	int histogram2[histSize] = { 0 };

	in.open("words.txt");
	string s;
	int count = 0;
	while (in) {
		in >> s;
		normalize(s);
		if (in) {
			count++;
			collisionCounts1[dopeHash(s, size)]++;
			collisionCounts2[newHash(s, size)]++;
			
		}
	}
	cout << count << " words read in " << endl;
	for (int i = 0; i < size; i++) {
		histogram1[collisionCounts1[i]]++;
		histogram2[collisionCounts2[i]]++;
		
	}

	printHistogram(histogram1, histSize / 20);
	cout << endl << endl;
	printHistogram(histogram2, histSize / 20);
	cout << endl << endl;


	cout << "bye" << endl;


	return 0;
}



