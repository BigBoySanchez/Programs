#include "linked_list.cpp"
#include <iostream>

int main() {
    int test[] = {1,2,3,4,5};
    LinkedList<int> joe(test, 5);
    joe.insertLast(-2);
    joe.rotate(-2);

    joe.print();
}