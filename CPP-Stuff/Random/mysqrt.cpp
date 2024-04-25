#include <iostream>
#include <iomanip>
using namespace std;


//returns sqrt of x w/ accuracy of 5 digits afer decimal
double mySqrt(double x) {
    const double ACCURACY = 1e-6;
    double minGuess = 0, maxGuess = max(1.0, x), nextNum = 0;

    while(maxGuess - minGuess > ACCURACY) {
        nextNum = (minGuess + maxGuess) / 2;

        if(nextNum * nextNum > x) maxGuess = nextNum;
        else minGuess = nextNum;

        cout << fixed << setprecision(10) << "minGuess = " << minGuess << " | maxGuess = " << maxGuess << endl;
    }

    return nextNum;
}

int main() {
    double userNum = 0, sqrtUserNum = 0;
    cout << "Choose number: ";
    cin >> userNum;

    sqrtUserNum = mySqrt(userNum);

    cout << fixed << setprecision(5) << "Result: " << sqrtUserNum;

    return 0;
}