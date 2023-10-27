/*
Author: Jacob Ativo
Submitted: TBA
Assignment: Text Analyzer - IDE Assignment 5
Function: Goes through an input file and finds each unique word, 
          sorts the words, and displays some statictics.
*/

#include <iostream> //cin cout
#include <fstream> //file handling
#include <string> //getline
#include <cctype> //tolower
#include <iomanip> //setw
using namespace std;

const int MAX_SIZE = 256; //maximum storage for all arrays

struct wordInfo
{
    string word;
    int wordLength;
    int wordCount;
};

string FileSelect(); //asks user for the file they want to look at
void CheckLine(string line, wordInfo words[], int &endSearch); //checks a string for unique words
void StoreText(ifstream &fin, string lines[], wordInfo words[], int &endSearch, int &linesSize); //stores lines in an array
void SelectionSort(wordInfo words[], const int wordsSize); //sorts the unique word array
void FindStats(wordInfo words[], const int wordsSize, int &numWords, int &numShort, int &locLongest); //finds word counts and longest word
void DisplayEverything(ostream &out, string lines[], wordInfo words[], const int linesSize, const int wordsSize); //outputs everything to a stream

int main()
{
    ifstream fin;
    ofstream fout;
    string file = FileSelect();
    string lines[MAX_SIZE];
    wordInfo words[MAX_SIZE];
    int wordsSize = 0, linesSize = 0;

    fin.open(file);
    if(!fin.is_open())
    {
        cout << "Error: Could not open \"" << file << "\".\n";
        return 1;
    }

    fout.open("AtivoTextAnalyzerResults.txt");
    if(!fout.is_open())
    {
        cout << "Error: Could not open \"AtivoTextAnalyzerResults.txt\"/\n";
        return 1;
    }

    StoreText(fin, lines, words, wordsSize, linesSize);
    SelectionSort(words, wordsSize);
    DisplayEverything(cout, lines, words, linesSize, wordsSize);
    //DisplayEverything(fout, lines, words, linesSize, wordsSize);

    return 0;
}

string FileSelect()
{
    string retVal;

    cout << "Input Filename (with .txt): ";
    cin >> retVal;
    cout << "\n";

    return retVal;
}

void StoreText(ifstream &fin, string lines[], wordInfo words[], int &endSearch, int &linesSize)
{
    string tempLine;
    int i;

    for(i = 0; !fin.eof() && i < MAX_SIZE; i++)
    {
        getline(fin, tempLine);
        lines[i] = tempLine;

        CheckLine(lines[i], words, endSearch);
    }
    linesSize = i + 1;
}

void CheckLine(string line, wordInfo words[], int &endSearch)
{
    int charIndex, wordIndex, tempChar;
    string tempWord = "";

    line += " "; //to prevent bug where last char is valid and word is ignored

    for(charIndex = 0; charIndex < line.size(); charIndex++)
    {
        tempChar = tolower(line.at(charIndex));

        if(isalpha(tempChar) || tempChar == 39 || tempChar == 45) {tempWord += tempChar;} //comparing to 39 and 45 allows apostrophes and hyphens
        else if(tempWord.size() > 0)
        {
            //finds location of a known word or finds a spot for a new one
            for(wordIndex = 0; wordIndex < endSearch && words[wordIndex].word != tempWord; wordIndex++);

            if(wordIndex == endSearch)
            {
                words[wordIndex].word = tempWord;
                words[wordIndex].wordLength = tempWord.length();
                words[wordIndex].wordCount = 1;

                endSearch++;
            }
            else {words[wordIndex].wordCount++;}

            tempWord = "";
        }
    }
}

void SelectionSort(wordInfo words[], const int wordsSize)
{
    int i, j, indexSmallest;
    wordInfo temp;

    for(i = 0; i < wordsSize - 1; ++i) //stolen fron zybook (sorry)
    {
        // Find index of smallest remaining element
        indexSmallest = i;
        
        for (j = i + 1; j < wordsSize; ++j) 
        {
            if (words[j].word < words[indexSmallest].word) {indexSmallest = j;}
        }

        // Swap words[i] and words[indexSmallest]
        temp = words[i];
        words[i] = words[indexSmallest];
        words[indexSmallest] = temp;
    }
}

void DisplayEverything(ostream &out, string lines[], wordInfo words[], const int linesSize, const int wordsSize)
{
    int i, numWords = 0, numShort = 0, locLongest = 0;

    for(i = 0; i < linesSize; ++i)
    {
        out << lines[i] << "\n";
    }

    out << "Word" << setw(20) << "Word Count" << setw(20) << "Word Length\n";
    out << "-------------------------------------------\n";
    for(i = 0; i < wordsSize; ++i)
    {  
        out << words[i].word << setw(20 - words[i].wordLength) << words[i].wordCount << setw(18) << words[i].wordLength << "\n";
    }

    FindStats(words, wordsSize, numWords, numShort, locLongest);
    out << "\nWord Count: " << numWords;
    out << "\n# of Unique Words: " << wordsSize;
    out << "\n# of Short Words: " << numShort;
    out << "\nLongest Word: " << words[locLongest].word;
    out << "\n";
}

void FindStats(wordInfo words[], const int wordsSize, int &numWords, int &numShort, int &locLongest)
{
    int i;

    for(i = 0; i < wordsSize; i++)
    {
        numWords += words[i].wordCount;
        numShort += (words[i].wordLength <= 3);
        
        if(words[i].wordLength > words[locLongest].wordLength) {locLongest = i;}
    }
}