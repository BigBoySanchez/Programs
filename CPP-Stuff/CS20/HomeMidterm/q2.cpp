#include <iostream>

#include <stdexcept>

using namespace std;

template <class T>

class Node
{

public:
    T value;

    Node *prev, *next;

    Node(const T &v, Node *p = nullptr, Node *n = nullptr)
    {

        prev = p;
        next = n;
        value = v;
    }
};

// A doubly linked list in which the values are arranged in ascending order.

template <class T>

class OrderedLinkedList
{

    friend ostream &operator<<(ostream &out, const OrderedLinkedList<T> &l)
    {

        out << "{ ";

        for(Node<T> *curr = l.headPtr; curr != tailPtr; curr = curr->next) out << curr->value << " ";

        out << "}";

        return out;
    }

private:
    Node<T> *headPtr, // a pointer to first node or null if list is empty.

        *tailPtr; // a pointer to last  node or null if list is empty.

    int length; // the list length

    // Return a pointer to first node containing v

    // or return nullptr if v is not found.

    Node<T> *findNodeWithValue(const T &v) const
    {
        for(Node<T> *left = headPtr; curr->value < v; left = left->next) {
            if(left->value == v) return left;
        }

        return nullptr;
    }

public:
    // Set headPtr and nullPtr to null and set length to zero.

    OrderedLinkedList()
    {

        // FILL IN MISSING CODE
    }

    // Copy constructor.

    OrderedLinkedList(const OrderedLinkedList &other)
    {

        // FILL IN MISSING CODE
    }

    // Return value in node at given index

    // or throw logic_error if index < 0 or > length-1

    // Message should be "Index out of bounds"

    T &operator[](int index)
    {

        if (index < 0 || index > length - 1)

            throw logic_error("Index out of bounds");

        // FILL IN MISSING CODE
    }

    // Destructor

    ~OrderedLinkedList()
    {

        // FILL IN MISSING CODE
    }

    // Remove all values from the list.

    void clear()
    {

        // FILL IN MISSING CODE
    }

    // Return the number of occurrences of v in the list

    // or return 0 if v is not found.

    // Your code should call findNodeWithValue.

    int count(const T &v)
    {

        Node<T> *p = findNodeWithValue(v);

        // FILL IN MISSING CODE
    }

    // Print the list values in reverse order,

    // enclosed in angle brackets, e.g. < 4 3 2 1 >

    void printBackwards() const
    {

        cout << "< ";

        // FILL IN MISSING CODE

        cout << ">";

        cout << endl;
    }

    // Insert v in the correct position

    // in the list and update length

    // Update headPtr or tailPtr if necessary.

    // Avoid needless looping

    // when v is the new biggest or the new smallest value.

    void insert(const T &v)
    {

        // FILL IN MISSING CODE
    }

    // Return the list length

    int getLength() const
    {

        // FILL IN MISSING CODE
    }

    // Return true if the list is empty

    bool isEmpty() const
    {

        // FILL IN MISSING CODE
    }

    // Set b to the biggest value or do nothing if the list is empty.

    void getBiggest(T &b) const
    {

        // FILL IN MISSING CODE
    }

    // Set s to the smallest value or do nothing if the list is empty.

    void getSmallest(T &s) const
    {

        // FILL IN MISSING CODE
    }

    // Remove the first occurence of v or do nothing if v isn't found.

    // Your code should call findNodeWithValue.

    void remove(const T &v)
    {

        // FILL IN MISSING CODE
    }
};

template <class T>

void testList(OrderedLinkedList<T> list)
{

    cout << endl
         << "BEGIN TESTLIST" << endl;

    cout << "Length = " << list.getLength() << endl;

    cout << "Forwards: " << list << endl;

    cout << "Backwards: ";

    list.printBackwards();

    if (list.isEmpty())
        cout << "The list is empty." << endl;

    else
    {

        T v;

        cout << "getSmallest returns ";

        list.getSmallest(v);

        cout << v << "." << endl;

        cout << "getBiggest returns ";

        list.getBiggest(v);

        cout << v << "." << endl;
    }

    try
    {

        cout << list[list.getLength()] << endl;
    }

    catch (logic_error e)
    {

        cout << e.what() << endl;
    }

    try
    {

        cout << list[-1] << endl;
    }

    catch (logic_error e)
    {

        cout << e.what() << endl;
    }

    for (int i = 0; i < list.getLength() / 2; i++)

        swap(list[i], list[list.getLength() - i - 1]);

    cout << "After reversing values " << list << endl;

    list.clear();

    cout << "After clear: " << list << endl;

    cout << "END TESTLIST" << endl
         << endl;
}

int main()

{

    OrderedLinkedList<int> list;

    cout << "Initial list = " << list << endl;

    cout << "Initial list length = " << list.getLength() << endl;

    list.insert(11);

    list.insert(3);

    list.insert(5);

    list.insert(7);

    list.insert(6);

    list.insert(4);

    list.insert(2);

    list.insert(8);

    list.insert(5);

    list.insert(1);

    list.insert(0);

    list.insert(11);

    list.insert(10);

    list.insert(5);

    list.insert(11);

    list.insert(0);

    list.insert(8);

    list.insert(4);

    cout << "After insertions, list = " << list << endl;

    testList(list);

    cout << "After testList, list = " << list << endl;

    char response = 'n';

    int v = -1;

    do
    {

        cout << "Enter a value to remove or -1 to quit: ";

        cin >> v;

        if (v != -1)
        {

            cout << "old count: " << list.count(v) << endl;

            list.remove(v);

            cout << "new count: " << list.count(v) << endl;

            testList(list);

            cout << list << endl;
        }

    } while (v != -1);

    do
    {

        cout << "Enter a value to insert or -1 to quit: ";

        cin >> v;

        if (v != -1)
        {

            cout << "old count: " << list.count(v) << endl;

            list.insert(v);

            cout << "new count: " << list.count(v) << endl;

            testList(list);

            cout << list << endl;
        }

    } while (v != -1);

    cout << "Bye" << endl;

    return 0;
}
