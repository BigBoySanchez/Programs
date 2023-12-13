/*
PSEUDOCODE:
- function (returns winning move/random one) (needs: board, tryspace, who's turn, last spot?)
    - make a move
    - if moved
        -if getboardvalue != 0
            - unmove
            - unmove again if player turn
            - return tryspace
        - unmove
    
    - if computer turn && max tryspace
        - set to player turn
        - tryspace = -1

    - if player turn && max tryspace
        - undo computer move
        - return 
    
    - return function call (tryspace + 1)
    
    
    
    
    
    - if moved
        - get boardvalue
        - if boardvalue changed OR board is full OR tryspace max
            - return space
        - else if player's turn
            - unmove x 2
            - set to comp turn
            - move tryspace back one
    - call function again w/ trySpace + 1

- main
    - pick who goes first
    - LOOP:
        - print board
        - do move
    - print last move
    - print winnr
*/

#include <iostream>
#include "SmallBoard.h"
using namespace std;

//returns best move
void compMove(SmallBoard board, int trySpace)
{
    if(board.move(trySpace))
}

int enterMove(SmallBoard board, bool playFirst)
{
    if(playFirst && board.isXTurn() || !playFirst && board.isOTurn()) 
    {
        cout << "Enter your move: ";

        //get player input until it's valid
        int move;
        cin >> move;
        while(!board.move(move))
        {
            cout << "Improper value. Please try again: ";
            cin >> move;
        }

        return move;
    }

    else
    {
        board.move(compMove(board, 0));
    }
}

int main()
{
    bool playFirst;
    SmallBoard board;

    //prompt for turn order
    cout << "Who's first? (1 = you, 0 = ai): ";
    cin >> playFirst;



    while(board.getNumFilled() < 9 && board.getBoardValue() == 0) //keep playing while slots are available and nobody's winning
    {
        board.printBoard();

        enterMove(board, playFirst);
    }

    return 0;
}