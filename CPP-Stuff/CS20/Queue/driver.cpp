/*
#include "ArrayQueue.h"
#include <iostream>
using namespace std;

template <class T>
void printq(ArrayQueue<T> aq) {
    cout << "{";

    while(!aq.empty()) {
        cout << aq.front() <<  " ";
        aq.dequeue();
    }

    cout << "}" << endl;
}

int main() {
    ArrayQueue<int> aq;
    
    for(int i = 1; i <= 48; i++) {
        aq.enqueue(i);
        printq(aq);
    }
    aq.dequeue();
    aq.dequeue();
    aq.dequeue();
    aq.dequeue();

    for(int i = 1; i <= 10; i++) {
        aq.enqueue(i);
        printq(aq);
    }

    while(!aq.empty()) {
        aq.dequeue();
        printq(aq);
    }

    return 0;
}
*/

#include "ArrayQueue.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// print the digits of n, each on a separate line
// Assume n > 0
void printDigits(int n);


// print the base 16 digits of n
// Assume n > 0
void toBase16(int n);


void printStack(ArrayStack<int> s) {
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}
void printQueue(ArrayQueue<int> s) {
    while (!s.empty()) {
        cout << s.front() << " ";
        s.dequeue();
    }
    cout << endl;
}





int main() {
    cout << "Please enter a sequence of positive integers followed by -1: ";
    int n;
    ArrayStack<int> st;
    ArrayQueue<int> qu;
    do {
        cin >> n;
        if (n > 0) {
            st.push(n);
            qu.enqueue(n);
        }

    } while (n > 0);
    ArrayQueue<int> stqu(st);

    printStack(st);
    cout << endl;
    printQueue(qu);
    cout << endl;
    printQueue(stqu);
    cout << endl;

  

    /*
    toBase16(864);
    cout << endl;
    cin.get();
    ArrayStack<char> myStack;
    myStack.push('x');
    myStack.push('y');
    cout << myStack.top() << endl;
    myStack.top() = 'b';
    cout << myStack.top() << endl;
    
   
    cout << myStack.empty() << endl;
    cout << myStack.getSize() << endl;
    cout << myStack.top() << endl;
    myStack.pop();
    cout << myStack.top() << endl;
    myStack.pop();
    cout << myStack.empty() << endl;
    cout << myStack.getSize() << endl;
    try {
        cout << myStack.top() << endl;
    }
    catch (logic_error e) {
        cout << e.what() << endl;
    }
    cout << "Normal exit " << endl;







    */
    return 0;
}

void printDigits(int n) {
    ArrayStack<int> s;
    while (n > 0) {
        s.push(n % 10); //push 4 onto the stack.
        n /= 10; // 864 --> 86

                       // push 6 onto the stack
                       // 86 -->8

                       // push 8 onto the stack
                       // 8 --> 0
    }
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
}
void toBase16(int n) {
    ArrayStack<int> s;
    while (n > 0) {
        s.push(n % 16);
        n /= 16;
    }
    while (!s.empty()) {
        int digit = s.top();
        if (digit < 10)
            cout << digit;
        else
            cout << char((digit - 10) + 'A');
        s.pop();
    }
}