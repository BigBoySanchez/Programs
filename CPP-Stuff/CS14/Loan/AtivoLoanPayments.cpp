/*
    Author: Jacob Ativo
    Submitted: 02/20
    Assignment: Mortage Payments
    Function: Calculates monthly payments 
              for a loan based on what
              the loan is for.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main() 
{
    char loanType;
    double loanAmount, annualInterest, termLength, //termLength too to prevent decimal terms
           monthlyPayment, monthlyInterest, paymentRounded;
    int lifePayments;
    
    cout << "\nDo you want to borrow to purchase a house or a vehicle? (H/V): ";
    cin >> loanType;

    switch (toupper(loanType)) //using switch to get correct input ranges
    {
        case 'H':
            cout << "Enter amount of the loan in the range 50,000.00 to 5,000,000.00: "; //ask user for correct input
            cin >> loanAmount; //store input
            if (loanAmount < 50000 || loanAmount > 5000000) //sends error message and ends program if outside of range
            {
                cout << "\nError: Loan out of range.\n\n";
                return 0;
            }

            cout << "Enter annual interest rate (from 2% through 10%) as a percent: "; //repeat for each question
            cin >> annualInterest;
            if(annualInterest < 2 || annualInterest > 10)
            {
                cout << "\nError: Percent out of range or input contains a percent sign.\n\n";
                return 0;
            }

            cout << "Enter term. Must be 10, 15 or 30 years: ";
            cin >> termLength;
            if (termLength != 10 && termLength != 15 && termLength != 30)
            {
                cout << "\nError: Invalid term length.\n\n";
                return 0;
            }

            break;

        case 'V':
            cout << "Enter amount of the loan in the range 5,000.00 to 100,000.00: "; //repeat pattern for vehicles
            cin >> loanAmount;
            if (loanAmount < 5000 || loanAmount > 100000)
            {
                cout << "\nError: Loan out of range.\n\n";
                return 0;
            }

            cout << "Enter annual interest rate (from 1% through 15%) as a percent: ";
            cin >> annualInterest;
            if(annualInterest < 1 || annualInterest > 15)
            {
                cout << "\nError: Percent out of range or input contains a percent sign.\n\n";
                return 0;
            }

            cout << "Enter term. Must be 3, 4, 5, or 6 years: ";
            cin >> termLength;
            if (termLength != 3 && termLength != 4 && termLength != 5 && termLength != 6)
            {
                cout << "\nError: Invalid term length.\n\n";
                return 0;
            }
            
            break;

        default:
            cout << "\nError: Not an 'H' or a 'V'\n\n"; //if user doesn't type 'H' or 'V'
            return 0;
    }

    //new variables to simplify calculation
    monthlyInterest = annualInterest / 1200;
    lifePayments = termLength * 12;

    //calculating EVERYTHING
    monthlyPayment = (loanAmount * monthlyInterest * pow(1 + monthlyInterest, lifePayments)) / 
                     (pow(1 + monthlyInterest, lifePayments) - 1);
    paymentRounded = static_cast<int>(100.0 * monthlyPayment + 0.5)/100.0;

    cout << fixed << setprecision(2) 
         << "\nMonthly payment rounded is: $" << paymentRounded;
    cout << "\nTotal paid back including interest if loan runs full term: $" << paymentRounded * lifePayments;
    cout << "\nInterest paid over life of the loan: $" << (paymentRounded * lifePayments) - loanAmount << "\n\n";

    return 0;
}