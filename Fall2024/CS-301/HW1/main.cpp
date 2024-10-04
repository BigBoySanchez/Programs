// Name: Jacob Ativo
// NetID: gd3470
// Email: jativo@horizon.csueastbay.edu
#include <fstream>   //ifstream
#include <iomanip>   //fixed, setprecision
#include <iostream>  //cin, cout

// check if string is a valid int. if it is, returns the int.
// throw str if invalid
int checkStr(const std::string& str) {
    int result = 0;

    for (char c : str) {
        if (!isdigit(c)) throw str;

        result *= 10;
        result += (c - '0');
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::ifstream fin;
    std::string filename = "";
    int sum1 = 0, numGood1 = 0, max2 = INT_MIN, numRows = 0;
    std::string invalids = "";

    // open file
    if (argc > 1) filename = argv[1];
    else {
        std::cout << "Enter the file to open: ";
        std::cin >> filename;
    }
    fin.open(filename);

    while (!fin.is_open()) {
        std::cout << "ERROR: Could not open \'" << filename
                  << "\'.\nTry again: ";
        std::cin >> filename;

        fin.open(filename);
    }

    // parse file
    while (!fin.eof()) {
        std::string currStr = "";

        // column 1
        std::getline(fin, currStr, ',');
        try {
            sum1 += checkStr(currStr);
            numGood1++;
        } catch (const std::string& evilStr) {
            if (!invalids.empty()) invalids += ", ";
            invalids += evilStr;
        }

        // column 2
        std::getline(fin, currStr, '\n');
        if (currStr.back() == '\r') currStr.pop_back();  // grrr...
        try {
            max2 = std::max(max2, checkStr(currStr));
        } catch (const std::string& evilStr) {
            if (!invalids.empty()) invalids += ", ";
            invalids += evilStr;
        }

        numRows++;
    }

    // print results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "The average value of all numbers in the first column: "
              << static_cast<double>(sum1) / numGood1 << "\n";

    std::cout << "The largest value of all numbers in the second column: "
              << max2 << "\n";
    std::cout << "The total number of rows in the file is: " << numRows << "\n";
    std::cout << "The invalid numbers are: " + invalids << "\n";

    fin.close();
    return 0;
}