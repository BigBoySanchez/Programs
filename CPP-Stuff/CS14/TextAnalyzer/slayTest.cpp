#include <iostream>

struct item
{
    std::string name;
    double unitPrice;
    int qty;
    double totPrice;
};

int main()
{
    item slays[50];

    for(int i = 0; i < sizeof(slays) / sizeof(item); ++i)
    {
        slays[i].name = "swag";
        slays[i].unitPrice = 6.9;
        slays[i].qty = 69;
        slays[i].totPrice = slays[i].qty * slays[i].unitPrice;
    }

    std::cout << "\nName: " << slays[37].name;
    std::cout << "\nPrice: " << slays[37].totPrice << "\n";
}