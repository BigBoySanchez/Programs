#ifndef SMALL_BOARD
#define SMALL_BOARD

#include <iostream>
#include <iomanip>




class SmallBoard {
public:
      static const char BLANK = '-';
      static const char EX = 'X';
      static const char OH = 'O';
      static const int NUM_SQUARES = 9;

private:
      int numFilled;
      char squares[NUM_SQUARES];
      const int winSets[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };


public:
      int getNumFilled() const {
          return numFilled;
      }
      int getNumBlanks() const {
           return NUM_SQUARES - numFilled;
      }


      SmallBoard()
      {
        //fill the squares with blanks
        for(int i = 0; i < NUM_SQUARES; i++) {squares[i] = BLANK;}
        numFilled = 0; //since board is all blanks
      }

      bool inBounds(int squareNum) const {
        return (squareNum < NUM_SQUARES && squareNum >= 0);
      }


      bool move(int squareNum) {
        if(isBlank(squareNum) && inBounds(squareNum)) //if squareNum is legal and empty
        {
            squares[squareNum] = ((isXTurn())? EX : OH);
            numFilled++;
            return true;    //move is successful
        }

        return false;   //move is not successful
      }

      bool unMove(int squareNum) {
        if(isTaken(squareNum) && inBounds(squareNum)) //if squareNum is legal and filled
        {
            squares[squareNum] = BLANK;
            numFilled--;
            return true; //move successfully removed
        }

        return false; //remove unsuccessful
      }

      bool isBlank(int squareNum) const  {
            return squares[squareNum] == BLANK;
      }

      bool isTaken(int squareNum) const {
        return squares[squareNum] != BLANK;
      }

      bool isX(int squareNum) const  {
        return squares[squareNum] == EX;
      }

      bool isO(int squareNum) const {
        return squares[squareNum] == OH;
      }

      bool isXTurn() const {
            return numFilled % 2 == 0;
      }
      bool isOTurn() const {
            return numFilled % 2 == 1;
      }

      int getBoardValue() const {
        int xWin = 0;
        int oWin = 0;

        
        for(int i = 0; i < 8; i++)
        {
            if(winSets[i][0] == winSets[i][1] == winSets[i][2])
            {
                xWin += (squares[winSets[i][0]] == EX);
                oWin += (squares[winSets[i][0]] == OH);
            }
        }

        return xWin - oWin;
      }

      // specialized for a 3 by 3 board.
      void printBoard(bool includeNumbers = true) const {
            std::cout << std::endl;
            for (int i = 0; i < 3; i++) {
                  for (int j = 0; j < 3; j++) {
                        char ch = squares[i * 3 + j];
                        std::cout << std::setw(7);
                        std::cout << ch;
                  }
                  std::cout << "\t\t";
                  if (includeNumbers)
                        for (int j = 0; j < 3; j++) {
                              std::cout << std::setw(7);
                              std::cout << i * 3 + j;
                        }
                  std::cout << std::endl << std::endl << std::endl;
            }
            std::cout << std::endl << std::endl;
      }

};













#endif