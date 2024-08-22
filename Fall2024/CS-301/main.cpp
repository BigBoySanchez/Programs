//Name: Jacob Ativo 
//NetID: gd3470
//Email: jativo@horizon.csueastbay.edu
#include <iostream> //cin, cout
#include <fstream> //ifstream
#include <iomanip> //fixed, setprecision

//check if string is a valid int. if it is, its put in result
bool checkStr(const std::string& str, int& result) {
    result = 0;

    for(char c : str) {
        if(!isdigit(c)) return false;

        result *= 10;
        result += (c - '0');
    }

    return true;
}

int main() {
    std::ifstream fin;
    int sum1 = 0, numGood1 = 0, max2 = INT_MIN, numRows = 0;
    std::string invalids = "";
    
    //open file
    while(true) {
        std::string filename = "";
        std::cout << "Enter file name: ";
        std::cin >> filename;

        fin.open(filename);

        if(fin.is_open()) break;
        else std::cout << "ERROR: Could not open file.\n";
    }

    //parse file
    while(!fin.eof()) {
        std::string currStr = "";
        int currNum = 0;
        
        //column 1
        std::getline(fin, currStr, ',');
        if(!checkStr(currStr, currNum)) {
            if(!invalids.empty()) invalids += ", ";
            invalids += currStr;
        } else {
            sum1 += currNum;
            numGood1++;
        }

        //column 2
        std::getline(fin, currStr, '\n');
        if(currStr.back() == '\r') currStr.pop_back(); //grrr...
        if(!checkStr(currStr, currNum)) {
            if(!invalids.empty()) invalids += ", ";
            invalids += currStr;
        } else {
            max2 = std::max(max2, currNum);
        }

        numRows++;
    }

    //print results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "The average value of all numbers in the first column: " << static_cast<double>(sum1) / numGood1 << "\n";

    std::cout << "The largest value of all numbers in the second column: " << max2 << "\n";
    std::cout << "The total number of rows in the file is: " << numRows << "\n";
    std::cout << "The invalid numbers are: " + invalids << "\n";

    fin.close();

    return 0;
}