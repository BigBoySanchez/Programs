#include <iostream>
#include <string>
using namespace std;

int myHash(string s, int tableSize) {
    int computedVal = 0;

    for(int i = 0; i < s.length(); i++) {
        computedVal *= 52;
        
        if(s[i] >= 'a' && s[i] <= 'z') computedVal += s[i] - 'a';
        else computedVal += s[i] - 'A' + 26;

        computedVal %= tableSize;
    }

    return computedVal;
}

//hashFunc for tic-tac-toe board using base 3
//assumes board has '-', 'O', 'X' only
int hasher(char board[][3]) {
    int base3 = 0;

    for(int r = 0; r < 3; r++) {
        for(int c = 0; c < 3; c++) {
            base3 *= 3;
            
            int digit;
            switch(board[r][c]) {
                case '-':
                digit = 0;
                break;

                case 'O':
                digit = 1;
                break;

                case 'X':
                digit = 2;
                break;
            }

            base3 += digit;
        }
    }

    return base3;
}

int main() {
   /* string part;

    cout << "Enter part number: ";
    cin >> part;

    cout << myHash(part, 10000000) << "\n"; */

    char board[][3] = {{'-','-','-'},
                      {'-','-','-'},
                      {'X','-','O'}};

    cout << hasher(board);

    return 0;
}