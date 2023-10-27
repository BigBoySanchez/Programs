#include <iostream>
#include "LinkedList.cpp"
using namespace std;

int main()
{
    LinkedList myList;
    for (int i = 1; i <= 20; i++) {
        myList.insertFirst(i);
    }
    myList.printList();

    cout << "Value at 7: " << myList.getItem(7) << endl;

    myList.removeFirst();
    myList.removeFirst();
    myList.printList();
    return 0;
}
