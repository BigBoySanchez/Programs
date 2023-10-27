#include <iostream>
using namespace std;

int main()
{
    int choice, rows, columns, r, c;
    char userChar;

    do
    {
        cout << "\n  Please pick a shape or exit.  \n";
        cout << "********************************\n";
        cout << "1. Rectangle\n";
        cout << "2. Right Triangle Going Down\n";
        cout << "3. Right Triangle Going Up\n";
        cout << "4. Isosceles Triangle\n";
        cout << "6. Exit\n";
        cout << "\nYour Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:

            cout << "********************************\n";
        
            while(true)
            {
                    cout << "\nHow Many Rows? (Range 3-24): ";
                    cin >> rows;

                    if(rows < 3 || rows > 24) {cout << "\nImproper value. Please try again.\n";}
                    else {break;}
            }

            while(true)
            {   
                cout << "\nHow many columns? (Range 3-80): ";
                cin >> columns;

                if(rows < 3 || rows > 80) {cout << "\nImproper value. Please try again.\n";}
                else {break;}
            }

            cout << "\nGreat! Now pick a character to use: ";
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

            case 2:

            case 3:

            case 4:

            case 5:

            case 6:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Numbers 1-6 only, please.\n";
                break;
        }
    } while(choice != 6);
    
    return 0;
}