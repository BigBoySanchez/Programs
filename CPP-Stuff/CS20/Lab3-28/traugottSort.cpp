#include <iostream>
#include <vector>

using namespace std;

void printArray(int arr[], int n) {
    if(n <= 0) return;
    cout << "{" << arr[0];
    
    for(int i = 1; i < n; i++) cout << "," << arr[i];

    cout << "}";
}

void sort(int a[], int n, int &numComp) {
    if(n <= 1) return;

    //exclude first element in array
    sort(a + 1, n - 1, numComp);

    //comparison happening soon...
    numComp++;

    //change first 2 elements and call again if not sorted
    if(a[0] > a[1]) {
        swap(a[0], a[1]);
        sort(a + 1, n - 1, numComp);
    }
}

int main() {
    srand(time(0));

    int n = 0;
    int a[100];
    int compCount = 0;
    int maxCount = 0;
    unsigned long totalCounts = 0;
    const int NUM_TESTS = 100000;

    cout << "arr size: ";
    cin >> n;

    if(n > 100) return 1;

    for(int testNum = 0; testNum < NUM_TESTS; testNum++) {
        for(int i = 0; i < n; i++) {
            a[i] = (rand() % 201) - 100;
        }

        //cout << "array: ";
        //printArray(a, n);

        sort(a, n, compCount);
        //cout << "\n\nsorted array: ";
        //printArray(a, n);
        //cout << "\nnum comparisons: " << compCount << "\n";

        maxCount = max(maxCount, compCount);
        totalCounts += compCount;
        compCount = 0;
    }

    cout << "\nmaxCount: " << maxCount;
    cout << "\navgCount: " << (double)totalCounts / NUM_TESTS;

    return 0;
}

/*
[3,1,2]
[1,2]
[3,2]
*/