#include "practiceHeap.cpp"
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main() {
    srand(time(NULL));
    const size_t ADD = 30;
    std::vector<int> vec = {69, 1000, 12, 10000, 300, 87, 420, 20, 17, 11};
    vec.reserve(vec.size() + ADD);

    for(int i = 0; i < ADD; i++) {
        vec.push_back(rand());
    }
    
    PracticeHeap<int> ph(vec);
    
        cout << ph << "\n";
    while(!ph.empty()) {
        cout << ph.top() << "\n";
        ph.pop();
    }

    return 0;
}