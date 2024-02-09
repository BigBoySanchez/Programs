#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

template <class T>
class Node
{
public:
    T value;
    Node<T> *next;

    Node(const T &v = T(), Node<T> *n = nullptr)
    {
        value = v;
        next = n;
    }
};

template <class T>
class LinkedList
{
private:
    Node<T> *headPtr;
    int length;

public:
    LinkedList()
    {
        length = 0;
        headPtr = nullptr;
    }

    LinkedList(const LinkedList<T> &other)
    {
        headPtr = nullptr;
        length = 0;
        if (other.length == 0)
            return;
        headPtr = new Node<T>(other.headPtr->value);
        Node<T> *otherCur = other.headPtr->next;
        Node<T> *thisPre = headPtr;
        while (otherCur != nullptr)
        {
            thisPre->next = new Node<T>(otherCur->value);
            otherCur = otherCur->next;
            thisPre = thisPre->next;
        }
        length = other.length;
    }

    LinkedList(const T values[], int numValues)
    {
        headPtr = nullptr;
        length = 0;

        for (int i = numValues - 1; i >= 0; --i)
            insertFirst(values[i]);
    }

    ~LinkedList()
    {
        while (headPtr != nullptr)
        {
            Node<T> *temp = headPtr;
            headPtr = headPtr->next;
            delete temp;
        }
    }

    void insertFirst(const T &v)
    {
        Node<T> *toInsert = new Node<T>(v, headPtr);
        headPtr = toInsert;
        length++;
    }
    void removeFirst(const T &v)
    {
        if (headPtr == nullptr)
            return;
        Node<T> *temp = headPtr;
        headPtr = headPtr->next;
        delete temp;
        length--;
    }
    void print() const
    {
        std::cout << "{";
        Node<T> *p = headPtr;
        while (p != nullptr)
        {
            std::cout << p->value << " ";
            p = p->next;
        }
        std::cout << "}" << std::endl;
    }

    LinkedList<T> getReverse() const
    {
        LinkedList<T> temp;
        Node<T> *curr = headPtr;

        while (curr)
        {
            temp.insertFirst(curr->value);
            curr = curr->next;
        }

        return temp;
    }

    void insertLast(const T & v)
    {
        if(length == 0) 
        {
            headPtr = new Node<T>(v);
            return;
        }
        Node<T> *parse = headPtr;

        //find node before null
        for(int i = 0; i < length - 1; ++i, parse = parse->next);

        parse->next = new Node<T>(v);
        ++length;
    }

    void rotate(int n)
    {
        if(length <= 1) return; //cant rotate smth empty or just 1 element
        int real_rotation = ((n % length) + length) % length;

        for(int i = 0; i < real_rotation; ++i)
        {
            //get second to last node
            Node<T> *last_node = headPtr;
            while(last_node->next->next)
                last_node = last_node->next;
            
            //make last node go to head
            last_node->next->next = headPtr;
            
            //make head last node
            headPtr = last_node->next;
            //make second to last node the end
            last_node->next = nullptr;
        }
    }
};

#endif