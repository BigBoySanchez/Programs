#ifndef SORTED_PAIR_H
#define SORTED_PAIR_H
#include <iostream>

template <class T>
class SortedPair
{
    friend 
    std::ostream& operator<<(std::ostream& out, SortedPair<T>& p)
    {
        out << "(" << p.b << ", " << p.c << ")";

        return out;
    }

private:
    T b;
    T c;
    void swap();
public:
    SortedPair<T>(T b = T(), T c = T());
    T getB() const;
    T getC() const;
    void setB(T b = T());
    void setC(T c = T());
};

template <class T>
SortedPair<T>::SortedPair(T b, T c)
{
    this->b = b;
    this->c = c;

    swap();
}

template <class T>
void SortedPair<T>::swap()
{
    if(b >c)
    {
        T temp = b;
        b = c;
        c = temp;
    }
}

template <class T>
T SortedPair<T>::getB() const
{
    return b;
}

template <class T>
T SortedPair<T>::getC() const
{
    return c;
}

template <class T>
void SortedPair<T>::setB(T b)
{
    this->b = b;
    swap();
}

template <class T>
void SortedPair<T>::setC(T c)
{
    this->c = c;
    swap();
}

#endif