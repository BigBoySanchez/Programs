/*
Author: Jacob Ativo
Submitted: TBA
Assignment: Patterns - IDE Assignment 2
Function: Menu of shapes to draw with a special checker pattern
*/

#include <iostream>
using namespace std;

int main()
{
    int choice, rows, columns, r, c;
    char userChar;
    bool quit, empty;

    do
    {
        cout << "\n  Please pick a shape or exit.  \n";
        cout << "********************************\n";
        cout << "1. Rectangle\n";
        cout << "2. Right Triangle To The Left\n";
        cout << "3. Right Triangle To The Right\n";
        cout << "4. Isosceles Triangle\n";
        cout << "5. Checker\n";
        cout << "6. Exit\n";
        
        cout << "\nYour Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //Rectangle

            cout << "********************************\n";
        
            while(true)
            {
                cout << "\nHow Many Rows? (Range 3-24): ";
                cin >> rows;

                if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.";}
                else {break;}
            }

            while(true)
            {   
                cout << "\nHow many columns? (Range 3-80): ";
                cin >> columns;
                
                if(columns < 3 || columns > 80) {cout << "\nImproper value. Please try again.";}
                else {break;}
            }

            cout << "\nPick a character to use: ";
            cin >> userChar;

            cout << "\nResult:\n";
            cout << "********************************\n\n";
            for(r = 0; r < rows; r++)
            {
                for(c = 0; c < columns; c++) {cout << userChar;}
                cout << '\n';
            }
            cout << "\n********************************";
            break;

            case 2: //Left Triangle

                cout << "********************************\n";

                while(true)
                {
                    cout << "\nHow Many Rows? (Range 3-24): ";
                    cin >> rows;

                    if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.";}
                    else {break;}
                }

                cout << "\nPick a character to use: ";
                cin >> userChar;

                cout << "\nResult:\n";
                cout << "********************************\n\n";
                for(r = 0; r < rows; r++)
                {
                    for(c = 0; c <= r; c++) {cout << userChar;}
                    cout << '\n';
                }
                cout << "\n********************************";
                break;

            case 3: //Right Triangle
                cout << "********************************\n";

                while(true)
                {
                    cout << "\nHow Many Rows? (Range 3-24): ";
                    cin >> rows;

                    if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.";}
                    else {break;}
                }

                cout << "\nPick a character to use: ";
                cin >> userChar;
                
                cout << "\nResult:\n";
                cout << "********************************\n\n";
                for(r = 0; r < rows; r++)
                {
                    for(c = 0; c < rows; c++) 
                    {
                        if(c + r < rows - 1){cout << " ";}
                        else {cout << userChar;}
                    }
                    cout << '\n';
                }
                cout << "\n********************************";
                break;


            case 4: //Isosceles
                cout << "********************************\n";

                while(true)
                {
                    cout << "\nHow Many Rows? (Range 3-24): ";
                    cin >> rows;

                    if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.";}
                    else {break;}
                }

                cout << "\nPick a character to use: ";
                cin >> userChar;
                
                cout << "\nResult:\n";
                cout << "********************************\n\n";
                for(r = 0; r < rows; r++)
                {
                    for(c = 0; c < (2*rows-1); c++)
                    {
                        if((rows-1+r) >= c && (rows-1-r) <= c) {cout << userChar;}
                        else {cout << ' ';}
                    }
                    cout << '\n';
                }
                cout << "\n********************************";
                break;

            case 5: //checker
                cout << "********************************\n";
        
                while(true)
                {
                    cout << "\nHow Many Rows? (Range 3-24): ";
                    cin >> rows;

                    if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.";}
                    else {break;}
                }

                while(true)
                {   
                    cout << "\nHow many columns? (Range 3-80): ";
                    cin >> columns;
                    
                    if(columns < 3 || columns > 80) {cout << "\nImproper value. Please try again.";}
                    else {break;}
                }

                cout << "\nPick a character to use: ";
                cin >> userChar;

                empty = true;
                cout << "\nResult:\n";
                cout << "********************************\n\n";
                for(r = 0; r < rows; r++)
                {
                    for(c = 0; c < columns; c++)
                    {
                        if(empty) {cout << ' ';}
                        else {cout << userChar;}

                        if(((rows%2 != 0) && (columns%2 != 0)) || (c != columns - 1)) {empty = !empty;}
                    }
                    cout << '\n';
                }
                cout << "\n********************************";
                break;

            case 6:
                cout << "Goodbye!\n";
                quit = true;
                break;

            default:
                cout << "Numbers 1-6 only, please.\n";
                break;
        }
    } while(!quit);
    
    return 0;
}
