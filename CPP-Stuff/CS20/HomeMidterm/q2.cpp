#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>

class Node {
 public:
  T value;

  Node *prev, *next;

  Node(const T& v, Node* p = nullptr, Node* n = nullptr) {
    prev = p;
    next = n;
    value = v;
  }
};

// A doubly linked list in which the values are arranged in ascending order.

template <class T>

class OrderedLinkedList {
  friend ostream& operator<<(ostream& out, const OrderedLinkedList<T>& l) {
    out << "{ ";

    for (Node<T>* curr = l.headPtr; curr != nullptr; curr = curr->next)
      out << curr->value << " ";

    out << "}";

    return out;
  }

 private:
  Node<T>*headPtr,  // a pointer to first node or null if list is empty.

      *tailPtr;  // a pointer to last  node or null if list is empty.

  int length;  // the list length

  // Return a pointer to first node containing v

  // or return nullptr if v is not found.

  Node<T>* findNodeWithValue(const T& v) const {
    if (isEmpty()) return nullptr;

    Node<T>*l = headPtr, *r = tailPtr;
    for (int i = 0; i <= length / 2; i++) {
      if (l->value == v) return l;
      if (r->value == v && r->prev->value != v)
        return r;  // if r->prev is null then length = 1

      l = l->next;
      r = r->prev;
    }

    return nullptr;
  }

 public:
  // Set headPtr and nullPtr to null and set length to zero.

  OrderedLinkedList() {
    headPtr = tailPtr = nullptr;
    length = 0;
  }

  // Copy constructor.

  OrderedLinkedList(const OrderedLinkedList& other) {
    if (other.isEmpty()) {
      headPtr = tailPtr = nullptr;
      length = 0;
      return;
    }

    headPtr = new Node<T>(other.headPtr->value);
    Node<T>*thisCurr = headPtr, *otherCurr = other.headPtr->next;
    while (otherCurr != nullptr) {
      thisCurr->next = new Node<T>(otherCurr->value, thisCurr);
      thisCurr = thisCurr->next;
      otherCurr = otherCurr->next;
    }

    tailPtr = thisCurr;
    length = other.length;
  }

  // Return value in node at given index

  // or throw logic_error if index < 0 or > length-1

  // Message should be "Index out of bounds"

  // fix dat
  T& operator[](int index) {
    if (index < 0 || index > length - 1)
      throw logic_error("Index out of bounds");

    Node<T>*l = headPtr, *r = tailPtr;
    for (int i = 0; i < length / 2 || l == r; i++) {
      if (i == index) return l->value;
      if (length - 1 - i == index) return r->value;

      l = l->next;
      r = r->prev;
    }

    return headPtr->value;  // just in case
  }

  // Destructor

  ~OrderedLinkedList() { clear(); }

  // Remove all values from the list.

  void clear() {
    while (headPtr != nullptr) {
      Node<T>* toDelete = headPtr;
      headPtr = headPtr->next;
      delete toDelete;
    }
    tailPtr = nullptr;
    length = 0;
  }

  // Return the number of occurrences of v in the list

  // or return 0 if v is not found.

  // Your code should call findNodeWithValue.

  int count(const T& v) {
    Node<T>* p = findNodeWithValue(v);
    int ret = 0;

    while (p != nullptr && p->value == v) {
      ret++;
      p = p->next;
    }

    return ret;
  }

  // Print the list values in reverse order,

  // enclosed in angle brackets, e.g. < 4 3 2 1 >

  void printBackwards() const {
    cout << "< ";

    for (Node<T>* curr = tailPtr; curr != nullptr; curr = curr->prev)
      cout << curr->value << " ";

    cout << ">";

    cout << endl;
  }

  // Insert v in the correct position

  // in the list and update length

  // Update headPtr or tailPtr if necessary.

  // Avoid needless looping

  // when v is the new biggest or the new smallest value.
  void insert(const T& v) {
    length++;
    if (length == 1) {
      headPtr = tailPtr = new Node<T>(v);
      return;
    }

    Node<T>*l = headPtr, *r = tailPtr;
    for (int i = 0; i <= (length - 1) / 2; i++) {
      if (l->value >= v) {
        l->prev = new Node<T>(v, l->prev, l);

        if (l == headPtr)
          headPtr = headPtr->prev;
        else
          l->prev->prev->next = l->prev;

        break;
      }
      if (r->value <= v) {
        r->next = new Node<T>(v, r, r->next);

        if (r == tailPtr)
          tailPtr = tailPtr->next;
        else
          r->next->next->prev = r->next;

        break;
      }

      l = l->next;
      r = r->prev;
    }
  }

  // Return the list length

  int getLength() const { return length; }

  // Return true if the list is empty

  bool isEmpty() const { return length == 0; }

  // Set b to the biggest value or do nothing if the list is empty.

  void getBiggest(T& b) const {
    if (!isEmpty()) b = tailPtr->value;
  }

  // Set s to the smallest value or do nothing if the list is empty.

  void getSmallest(T& s) const {
    if (!isEmpty()) s = headPtr->value;
  }

  // Remove the first occurence of v or do nothing if v isn't found.

  // Your code should call findNodeWithValue.

  void remove(const T& v) {
    Node<T>* toDelete = findNodeWithValue(v);
    if (toDelete == nullptr) return;
    if(length == 1) {
      clear();
      return;
    }

    if (toDelete == headPtr) {
      headPtr = headPtr->next;
      headPtr->prev = nullptr;
    } else if (toDelete == tailPtr) {
      tailPtr = tailPtr->prev;
      tailPtr->next = nullptr;
    } else {
      toDelete->prev->next = toDelete->next;
      toDelete->next->prev = toDelete->prev;
    }

    delete toDelete;
    length--;
  }
};

template <class T>

void testList(OrderedLinkedList<T> list) {
  cout << endl << "BEGIN TESTLIST" << endl;

  cout << "Length = " << list.getLength() << endl;

  cout << "Forwards: " << list << endl;

  cout << "Backwards: ";

  list.printBackwards();

  if (list.isEmpty())
    cout << "The list is empty." << endl;

  else {
    T v;

    cout << "getSmallest returns ";

    list.getSmallest(v);

    cout << v << "." << endl;

    cout << "getBiggest returns ";

    list.getBiggest(v);

    cout << v << "." << endl;
  }

  try {
    cout << list[list.getLength()] << endl;
  }

  catch (logic_error e) {
    cout << e.what() << endl;
  }

  try {
    cout << list[-1] << endl;
  }

  catch (logic_error e) {
    cout << e.what() << endl;
  }

  for (int i = 0; i < list.getLength() / 2; i++)

    swap(list[i], list[list.getLength() - i - 1]);

  cout << "After reversing values " << list << endl;

  list.clear();

  cout << "After clear: " << list << endl;

  cout << "END TESTLIST" << endl << endl;
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

  do {
    cout << "Enter a value to remove or -1 to quit: ";

    cin >> v;

    if (v != -1) {
      cout << "old count: " << list.count(v) << endl;

      list.remove(v);

      cout << "new count: " << list.count(v) << endl;

      testList(list);

      cout << list << endl;
    }
  } while (v != -1);

  do {
    cout << "Enter a value to insert or -1 to quit: ";

    cin >> v;

    if (v != -1) {
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
