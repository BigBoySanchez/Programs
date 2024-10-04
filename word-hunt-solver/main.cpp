#include "wordTree.h"
#include "practiceMap.h"
#include "practiceHeap.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <cstdint>

#define NUM_ROWS 4
#define NUM_COLS 4
#define MAX_LEN 16
#define MIN_LEN 3

void clear_screen(char fill = ' ') { 
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}


//returns key pressed
TCHAR getUserKey() {
    TCHAR ch;
    DWORD mode, numRead;
    HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );

    // Switch to raw mode
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, 0 );

    // Wait for the user's response
    ReadConsole( hstdin, &ch, 1, &numRead, NULL );

    //return console to og mode
    SetConsoleMode(hstdin, mode);

    return ch;
}

typedef std::pair<unsigned int, unsigned int> coords;
typedef std::vector<coords> coordVec;
typedef bool(*CVComp)(const coordVec&, const coordVec&);
typedef practiceHeap<coordVec, CVComp> wordHeap;

bool wordComp(const coordVec& a, const coordVec& b) { return a.size() < b.size(); }

//print solution found in search. takes coords of letters. returns if q was pressed.
void printSoln(std::string **board, const coordVec& toPrint) {
    typedef std::vector<std::string> strVec;
    
    std::string word = "";
    const std::string fillStr = "----";
    std::vector<strVec> printBoard(NUM_ROWS, strVec(NUM_COLS, fillStr));
    
    for(size_t i = 0; i < toPrint.size(); i++) {
        const unsigned int x = toPrint[i].first;
        const unsigned int y = toPrint[i].second;
        std::string toAdd = "";

        word += board[x][y];

        toAdd += ("[" + std::to_string(i + 1) + "]");
        while(toAdd.length() < fillStr.length()) toAdd += "-";
        printBoard[x][y] = toAdd;
    }
    
    std::cout << word << "\n";

    for(unsigned int r = 0; r < NUM_ROWS; r++) {
        for(unsigned int c = 0; c < NUM_COLS; c++) {
            std::cout << printBoard[r][c] << " ";
        }
        std::cout << "\n";
    }
}

//find words beginning at coords (r, c). needs letterNode tree to validate words. inserts solutions into solns
void findWords(letterNode * root, std::string **board, 
               wordHeap *solns, practiceMap<std::string, bool> *seen,
               unsigned int r, unsigned int c) {
    
    std::string currWord = "";
    std::vector<coords> currCoords;

    std::stack<coords> todo;
    std::stack<letterNode *> prevNodes;


    prevNodes.push(root);
    todo.push({r, c});

    while(!todo.empty()) {
        coords curr = todo.top();
        char currChar = board[curr.first][curr.second][0];

        if(isalpha(currChar)) {
            root = root->kids[currChar - 'A'];
            
            currWord.push_back(currChar);
            currCoords.push_back(curr);
            
            prevNodes.push(root);

            board[curr.first][curr.second] = "-";

        } else {
            todo.pop();
            board[curr.first][curr.second] = currWord.back();

            prevNodes.pop();

            currCoords.pop_back();
            currWord.pop_back();

            root = prevNodes.top();
            continue;
        }

        if(root->isWord && !(*seen)[currWord]) {
            (*seen)[currWord] = true;
            solns->insert(currCoords);
        }

        //add cells around curr to stack
        for(int8_t rOff = -1; rOff <= 1; rOff++) {
            for(int8_t cOff = -1; cOff <= 1; cOff++) {
                //skip tile if out of bounds 
                if((curr.first == 0 && rOff == -1) || (curr.first == NUM_ROWS - 1 && rOff == 1) ||
                   (curr.second == 0 && cOff == -1) || (curr.second == NUM_COLS - 1 && cOff == 1))
                    continue;

                //skip tile if it's been seen or it isn't the beginning of any word
                coords nextAdjacent = {curr.first + rOff, curr.second + cOff};
                char adjacentChar = board[nextAdjacent.first][nextAdjacent.second][0];
                if(!isalpha(adjacentChar) || root->kids[adjacentChar - 'A'] == nullptr)
                    continue;

                todo.push(nextAdjacent);
            }
        }
    }
}

//get solutions starting at each tile of board. returns heap of solutions on board
wordHeap *travBoard(letterNode * root, std::string **board) {
    wordHeap *solns = new wordHeap(wordComp);
    if(solns == nullptr) throw std::runtime_error("Couldn't make new wordHeap.\n");
    practiceMap<std::string, bool> seen;

    for(int r = 0; r < NUM_ROWS; r++) {
        for(int c = 0; c < NUM_COLS; c++) {
            findWords(root, board, solns, &seen, r, c);
        }
    }

    return solns;
}

std::string **getBoard() {
    std::string **board = new std::string*[NUM_ROWS];

    for(int i = 0; i < NUM_ROWS; i++) {
        board[i] = new std::string[NUM_COLS];
        std::string row;

        std::cout << "Enter row " << i + 1 << ": ";
        std::cin >> row;
        for(int j = 0; j < NUM_COLS; j++) {
            if(row.length() < NUM_COLS) throw std::runtime_error("ERROR: Input too short.\n");
            if(!isalpha(row.at(j))) throw std::runtime_error("ERROR: Input has non-letter.\n");
            
            board[i][j] = toupper(row.at(j));
        }
    }

    return board;
}

void close(std::string **board, wordHeap *solns, letterNode *root) {
    for(int r = 0; r < NUM_ROWS; r++) delete board[r];
    delete board;
    delete solns;
    clearTree(root);
}

int main() {
    letterNode * root = new letterNode;
    wordHeap *solns = nullptr;
    std::string **board;
    char userK = '\0';

    
    std::cout << "Loading dictionary...\n";
    //skip first 2 lines of dictionary
    insertFromDict(root, 
                   "Collins Scrabble Words (2019).txt",
                   2, MIN_LEN, MAX_LEN);
    
    std::cout << "Dictionary loaded. Press any key to continue.";
    if(getUserKey() == 3) {
        close(board, solns, root);
        return 0;
    }
    clear_screen();

    try { board = getBoard(); }
    catch(std::runtime_error e) { 
        std::cout << e.what();
        close(board, solns, root);    
    }
    
    solns = travBoard(root, board);
    
    while(!solns->empty() && tolower(userK) != 'q') {
        clear_screen();
        userK = '\0';
        
        printSoln(board, solns->top());
        solns->remove();

        std::cout << "Press q to quit or press enter to continue.";
        while(tolower(userK) != 'q' && userK != '\r' && userK != 3) 
            userK = getUserKey();
        
        if(userK == 3) {
            close(board, solns, root);
            return 0;
        }
    }
    if(solns->empty()) {
        clear_screen();
        
        std::cout << "Out of words. Press any key to close.";
        getUserKey();
    }

    //clear_screen();
    std::cout << "\n";
    close(board, solns, root);

    return 0;
}