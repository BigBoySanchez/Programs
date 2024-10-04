#include <iostream>
#include "SmallBoard.h"
using namespace std;

int main()
{
    SmallBoard boar;

    while(boar.getNumFilled() < 9 && boar.getBoardValue() == 0) //keep playing while slots are available and nobody's winning
    {
        boar.printBoard();

        //print prompt depending on who's playing
        if(boar.isXTurn()) cout << "Enter a move for X: "; 
        if(boar.isOTurn()) cout << "Enter a move for O: ";

        //get player input until it's valid
        int move;
        cin >> move;
        while(!boar.move(move))
        {
            cout << "Improper value. Please try again: ";
            cin >> move;
        }
    }
    boar.printBoard(); //to print final board

    //print result of the game
    if(boar.getBoardValue() > 0) cout << "X wins!";
    else if (boar.getBoardValue() < 0) cout << "O wins!";
    else cout << "Tie. 0.o";
}