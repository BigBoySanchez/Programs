#include <iostream>
using namespace std;

int GetBiggest(int nums[], int length)
{
    int big;
    for(int i = 0; i < length; i++)
    {
        if(i==0 || nums[i] > big) {big = nums[i];}
    }

    return big;
}

int main()
{
    int boy[] = {3, 4, 5, 11, 0, 9};
    cout << GetBiggest(boy, 6);        
}