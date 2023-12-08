#include <iostream>
using namespace std;

bool isMountain(int nums[], int length)
{
    if(length <= 2) //reached the middle OR too short
    {
        return false;
    }

    //recursive call removes an element from each end
    //1. check if each end is ascending
    //2. check if next elements are valid OR next call makes a short array
    
    //return 1 && 2
    return nums[0] < nums[1] && nums[length - 1] < nums[length - 2] && (isMountain(nums + 1, length - 2) || length <= 4);  
}



int main()
{
    int len = 0;
    cout << "len: ";
    cin >> len;

    int* nums = new int[len];

    for(int i = 0; i < len; i++)
    {
        cout << "enter " << i + 1 << ": ";
        cin >> *(nums + i);
    }

    cout << '\n' << endl << isMountain(nums, len);

    delete[] nums;
    return 0;
}