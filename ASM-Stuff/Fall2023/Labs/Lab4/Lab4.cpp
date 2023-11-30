//
// Lab4.cpp
//
// Jacob Ativo
// 10/10
// all of the code fragments in C++
//

#include <iostream>

int main() 
{
    int a, b;
    
    //First fragment
    a = 0;
    b = 0;

    while (a < 10) 
    {
        b += a;
        a++;

        std::cout << "A: " << a << "        B: " << b << std::endl; //checking the values of a and b on each run 
    }
    std::cout << "End of first.\n\n";

    //Second fragment
    a = 0;
    b = 0;

    do
    {
        b += a;
        a++;

        std::cout << "A: " << a << "        B: " << b << std::endl;
    } while (a < 10);
    std::cout << "End of second.\n\n";

    //Third fragment
    b = 0;

    for(a = 0; a < 10; a++)
    {
        b += a;

        std::cout << "A: " << a << "        B: " << b << std::endl;
    }
    std::cout << "End of third.\n\n";

    //Fourth fragment
    a = 0;
    b = 0;

    if(a <= b)
    {
        b = 10;
    }
    std::cout << "A: " << a << "        B: " << b << std::endl;
    std::cout << "End of fourth.\n\n";

    //Fifth fragment
    a = 0;
    b = 0;

    if(a < b)
    {
        b = 10;
    }
    else
    {
        a = 20;
    }
    std::cout << "A: " << a << "        B: " << b << std::endl;
    std::cout << "End of fifth.\n\n";
}