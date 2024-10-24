#include "practiceHeap.h"
#include <iostream>

using namespace std;

int main() {
    std::vector<int> vec = {69, 1000, 12, 10000, 300, 87, 420, 20, 17, 11};
    PracticeHeap<int> ph(vec);

    cout << ph << "\n";

    return 0;
}