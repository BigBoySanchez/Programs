#include "Dictionary.h"

int main() {
    Dictionary d("test.txt");
    vector<string> words = {"goon", "beast", "abest", "breast", "baste", "peter", "pete", "peet", "teep"};
    d.insertWords(words);

    d.printDictionary();

    cout << "done.\n";
    return 0;
}