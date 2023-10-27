#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction
{
    friend 
    std::ostream& operator<<(std::ostream& out, Fraction& f)
    {
        out << f.numerator << "/" << f.denominator;
        return out;
    }

private:
    int absolute(int a) const
    {
        if(a < 0) a *= -1;
        return a;
    }
    
    void swap(int& a, int& b) const
    {
            int temp = a;
            a = b;
            b = temp;
    }

    int gcd(int a, int b) const
    {
        a = absolute(a);
        b = absolute(b);

        bool isOrdered = a >= b;

        if(!isOrdered) swap(a, b);

        int r = a%b;
        if(r != 0) 
        {
            gcd(b, r);
        }
        else 
        {
            return b;
        }
    }
    

public:
    int numerator;
    int denominator;

    Fraction& operator+=(const Fraction& q)
    {
        numerator = numerator * q.denominator + denominator * q.numerator;
	    denominator = denominator * q.denominator;
	
	    int commonD = gcd(numerator, denominator);
	    int isNeg = (denominator < 0)? -1 : 1;
	
	
	    numerator /= (isNeg * commonD);
	    denominator /= (isNeg * commonD);
	
	    return *this;
    }
};

#endif