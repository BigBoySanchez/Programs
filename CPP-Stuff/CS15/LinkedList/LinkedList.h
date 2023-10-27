#ifndef LINKEDLIST_H

#define LINKEDLIST_H




class Node {

public:

 int value;

 Node* next; 




 Node(int v = 0, Node* n = nullptr) {

 value = v;

 next = n;

 }

};




class LinkedList

{

private:

 Node* headPtr;  // --->__4__--->__7__--->__3__(nullptr)

 int length;




public:

 LinkedList();




 LinkedList(const LinkedList& other);




 ~LinkedList();




 void insertFirst(int v);




 void insertLast(int v); //NEED TO IMPLEMENT




 void removeFirst();




 void removeLast();




 int getItem(int index) const; //NEED TO IMPLEMENT




 void printList() const;




 /*

 * Some other methods for later:

 * 

 * void removeAtIndex(int index);

 * void insertAtIndex(int index);

 * bool contains(int target) const;

 * int getIndexOf(int target) const;

 * void printBackwards() const;

 * void copyList(LinkedList & other);

 * void appendList(LinkedList & other);

 * 

 */
};







#endif