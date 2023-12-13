#include <iostream>
#include "SmallBoard.h"
using namespace std;

//returns best move
int compMove(SmallBoard board)
{
	int lastSpace = 0; //last valid space
	bool winner = false; //if winning move was made before unmoving

	for(int i = 0; i < board.NUM_SQUARES; i++)
	{
		if(board.move(i))
		{
			winner = board.getBoardValue(); //since 0 is a draw
			board.unMove(i); //always want to unmove
			if(winner) return i;

			lastSpace = i;
		}
	}
	board.move(lastSpace);

	for(int i = 0; i < lastSpace; i++)
	{
		if(board.move(i))
		{
			winner = board.getBoardValue();
			board.unMove(i);

			if(winner && board.unMove(lastSpace)) return i; //only want to undo compMove if winner was found
		}
	}
	board.unMove(lastSpace);

	return lastSpace;
}

void enterMove(SmallBoard& board, bool playFirst)
{
	char temp;
	int bestMove;
	
	if(playFirst && board.isXTurn() || !playFirst && board.isOTurn()) 
    {
        cout << "Enter your move: ";

        //get player input until it's valid
        int move;
        cin >> move;
        while(!board.move(move))
        {
            cout << "Improper value. Please try again: ";
            cin.get(temp);
        }
    }

    else
    {
		cin.ignore();
		bestMove = compMove(board);
		board.move(bestMove);

		cout << "Computer picked: " << bestMove << '\n';
		cout << "Press enter to continue.";
		cin.get();
    }
}

int main()
{
    bool playFirst;
    SmallBoard board;

    //prompt for turn order
    cout << "Who's first? (1 = you, 0 = ai): ";
    cin >> playFirst;


	board.printBoard();
    while(board.getNumFilled() < 9 && board.getBoardValue() == 0) //keep playing while slots are available and nobody's winning
    {
        enterMove(board, playFirst);
		board.printBoard();
    }

    //print result of the game
    if(board.getBoardValue() > 0) cout << "X wins!";
    else if (board.getBoardValue() < 0) cout << "O wins!";
    else cout << "Tie. 0.o";

    return 0;
}