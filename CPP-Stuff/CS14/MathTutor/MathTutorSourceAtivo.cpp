#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void DisplayProgramInfo(string& userName);
void Menu(char& choice);
void Addition(string userName);
void Subtraction(string userName);
void Multiplication(string userName);
void Division(string userName);
void InputValidation();


int main()
{
    srand(time(0));
    string userName;
    char choice;

    DisplayProgramInfo(userName);

    do
    {
        Menu(choice);

        switch(toupper(choice))
        {
            case 'A':
                Addition(userName);
                break;
            case 'S':
                Subtraction(userName);
                break;
            case 'M':
                Multiplication(userName);
                break;
            case 'D':
                Division(userName);
                break;
            case 'Q':
                cout << "See ya later!\n";
                break;
            default:
                cout << "Improper input. A, S, M, D, and Q only.\n";
                break;
        }
    } while (toupper(choice) != 'Q');
    
    return 0;
}

void DisplayProgramInfo(string& userName)
{
    cout << "WARNING: This program will make you a math wizard.\n";
    cout << "Before we begin, enter your username: ";

    getline(cin, userName);
}

void Menu(char& choice)
{
    cout << "\n    Now pick a problem type.    \n";
    cout << "********************************\n";
    cout << "(A) Addition\n";
    cout << "(S) Subtraction\n";
    cout << "(M) Multiplication\n";
    cout << "(D) Division\n";
    cout << "(Q) Quit\n";

    cout << "\nYour choice: ";
    cin >> choice;
}

void Addition(string userName)
{
    int num1, num2, userAnswer, answerKey;

    num1 = rand() % 999 + 1; //generates int from 1-999
    num2 = rand() % 999 + 1;
    answerKey = num1 + num2;

    cout << num1 << " + " << num2 << " = ?\n";
    cout << "Enter the sum: ";
    cin >> userAnswer;

    if(userAnswer == answerKey) {cout << "Great job " << userName << "!\n";}
    else {cout << "Sorry " << userName << ". The correct solution was: " << answerKey << "\n";}
}
void Subtraction(string userName)
{
    int num1, num2, userAnswer, answerKey, temp;

    num1 = rand() % 999 + 1;
    num2 = rand() % 999 + 1;
    if(num2 > num1) 
    {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    answerKey = num1 - num2;

    cout << num1 << " - " << num2 << " = ?\n";
    cout << "Enter the difference: ";
    cin >> userAnswer;

    if(userAnswer == answerKey) {cout << "Great job " << userName << "!\n";}
    else {cout << "Sorry " << userName << ". The correct solution was: " << answerKey << "\n";}
}
void Multiplication(string userName)
{
    int num1, num2, userAnswer, answerKey;

    num1 = rand() % 99 + 1; //generates int from 1-99
    num2 = rand() % 9 + 1; //generates int from 1-9
    answerKey = num1 * num2;

    cout << num1 << " × " << num2 << " = ?\n";
    cout << "Enter the product: ";
    cin >> userAnswer;

    if(userAnswer == answerKey) {cout << "Great job " << userName << "!\n";}
    else {cout << "Sorry " << userName << ". The correct solution was: " << answerKey << "\n";}
}
void Division(string userName)
{
    int num1, num2, userQuotient, answerQuotient, userRemainder, answerRemainder, temp;

    num1 = rand() % 999 + 1;
    num2 = rand() % 9 + 1;
    if(num2 > num1)
    {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    answerQuotient = num1 / num2;
    answerRemainder = num1 % num2;

    cout << num1 << " ÷ " << num2 << " = ?\n";
    
    cout << "Enter the quotient: ";
    cin >> userQuotient;

    cout << "Enter the remainder: ";
    cin >> userRemainder;

    if(userQuotient == answerQuotient && userRemainder == answerRemainder) {cout << "Great job " << userName << "!\n";}
    else {cout << "Sorry " << userName << ", the correct solution was: " << answerQuotient << " R" << answerRemainder << "\n";}
}

void InputValidation()
{
    cout << "FIXME: InputValidation\n";
}
