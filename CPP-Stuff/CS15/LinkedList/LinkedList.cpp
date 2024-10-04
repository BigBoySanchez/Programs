#include "LinkedList.h"

#include <iostream>







LinkedList::LinkedList() {

 length = 0;

 headPtr = nullptr;

}




LinkedList::LinkedList(const LinkedList& other) { //copies the values & their order from another linked list

 length = 0;

 headPtr = nullptr;


 if (other.length == 0) return;

 // Inefficient version: 

 /*

 for (Node* temp = other.headPtr; temp != nullptr; temp = temp->next) {

 int valueToCopy = temp->value;

 insertLast(valueToCopy);

 }

 */

 // Efficient version:




 headPtr = new Node(other.headPtr->value); //allocates a node with head = to other's head

 Node* current = headPtr;

 for (Node* temp = other.headPtr->next; temp != nullptr; temp = temp->next) {   //starts at other's next pointer;
                                                                                //while temp is not null (at the end other);
                                                                                //after body, temp moves to the "next" pointer
 
 current->next = new Node(temp->value); //current node's next value is where temp is

 current = current->next; //current moves to the "next" value

 }

 length = other.length; //shares length with other list after nodes get copied

}




LinkedList::~LinkedList() { //deletes all nodes of the list

 while (headPtr) //while there's a node

 removeFirst();  //remove the head node and decrement length

}







void LinkedList::insertFirst(int v){    //inserts a value into the head of list 
                                        //and pushes the rest down

 Node* toInsert = new Node(v);      //makes a new node containing v

 toInsert->next = headPtr;          //head is now "second"

 headPtr = toInsert;                //head becomes node with v

 length++;

}

/*

myList (a variable in main of type LinkedList)




headPtr: --> | 3 | --> | 4 | --> | 5 | --> | 6 (null) |







In main, call myList.toInsert(2)




toInsert: --> | 2 (null) |




toInsert: -->   | 2 | -->   | 3 | -- > | 4 | -- > | 5 | --> | 6 (null) |

headPtr   --> 




So myList now looks like this




    headPtr-- > | 2 | --> | 3 | --> | 4 | -- > | 5 | --> | 6 (null) |










What if myList were initially empty?




headPtr is null

length is 0




Call myList.insertFirst(2)




toInsert : --> | 2 (null) |

headPtr    -->




So myList is now  headPtr --> |2 (null) |   with length = 1.

*/




void LinkedList::removeFirst() { //removes only the head of the linked list

 if (headPtr == nullptr) {

 return; // do nothing sinced there is no node to remove

 }

 Node* toDelete = headPtr;  //marks the head as deletion target

 headPtr = headPtr->next;   //then moves to next node

 delete toDelete;           //deletes head

 length--;                  //since head is gone, there's one less element




 // What we don't want to do:   delete headPtr;  headPtr = headPtr->next;
 // since headPtr won't exist and doesn't have a next
}




void LinkedList::printList() const {

 std::cout << "< ";

 for (Node* temp = headPtr; temp != nullptr; temp = temp->next) { //iterates thru list till it reaches null (the end)

 std::cout << temp->value << " "; //prints value at node




 }

 std::cout << ">" << std::endl;

}




// If index is bigger than length-1 or less than 0

// then just return 0. 

// (We'll have a better solution to this case later.)

// Otherwise, just return the value in the node 

// at the given index.

int LinkedList::getItem(int index) const {

 // TO DO
 // Check that index is legal, if not just return 0
 if(index < 0 || index >= length)  return 0;

 int i = 0;
 Node * temp = headPtr;
 for (; i < index; i++) 
 {
   // Advance temp to point to the next node.
   temp = temp->next;
 }

 return temp->value;  //what does -> actually mean?
                      // -> dereferences the pointer and is like "."
// Actual return value should be the value in Node at index i, 
// which should be temp->value at this point

}




// Add a new node to the end of the list

// with the given value v.

void LinkedList::insertLast(int v) {

 // If the list is empty then just create a new node with the data
 if(length == 0) 
 {
  Node* toInsert = new Node(v);

  // and set headPtr to the new node. Also, set length to 1.
  headPtr = toInsert;
  length = 1;
  return;
 }

 // Otherwise loop until you get to the last node in the list.
 Node* temp = headPtr;
 for(; temp->next != nullptr; temp = temp->next);

 // Then make that node's next pointer point to a new node with the data.
 temp->next = new Node(v);

 // Increment length.
 length++;
}







// remove the last node in the list

// and update the next pointer for the previous node.

// Special case: If the list is empty then just do nothing.

void LinkedList::removeLast() {

 if (headPtr == nullptr) {

 return; // do nothing sinced there is no node to remove

 }

 if (length == 1) {

 delete headPtr;

 length = 0;

 headPtr = nullptr;

 }

 Node* temp;

 for (temp = headPtr; temp->next->next != nullptr; temp = temp->next); //finds last node (before null)
                                                                       //what happens when u only have one "->"?

 delete temp->next;

 temp->next = nullptr;

 length--;

}




 //headPtr --> | 4 |  --> |5 (null) |