#include <iostream>
#include "SmallBoard.h"
using namespace std;

int main()
{
    SmallBoard boar;

    while(boar.getNumFilled() < 9 && boar.getBoardValue() == 0)
    {
        boar.printBoard();

        int move;
        cin >> move;
        boar.move(move);
    }
    boar.printBoard();
}