#include "ArrayStack.h"
#include <stdexcept>
#include <iostream>
#include <string>

//returns factorial of num1
int fact(int num1) {
    int ret = 1;
    
    for(; num1 > 1; --num1)
        ret *= num1;
    
    return ret;
}

//pops all nums from todo into nums
void get_nums(ArrayStack<int> &todo, int nums[]) {
    int i = 0;
    const int MAX_NUMS = 2;
    
    while(!todo.empty() && i < MAX_NUMS) {        
        nums[i] = todo.top();
        todo.pop();

        ++i;
    }
}

//does operation on num1, num2 based on op
int do_operation(const char op, const int num1, const int num2) {
    switch(op) {
        case '+':
            return num2 + num1;
        case '*':
            return num2 * num1;
        case '-':
            return num2 - num1;
        case '/':
            return num2 / num1;
        case '!':
            return fact(num1);
        case '~':
            return -num1;
        default:
            return -69420; //just in case...
    }
}


int main() {
    ArrayStack<int> todo;
    std::string expression = ""; //WIP: "4 5 + 7 - 3 + !" = 120
    int exp_len = 0;

    
    std::cout << "Input Calculation Ting: ";
    std::getline(std::cin, expression); //assuming the user does proper input w/ period at end
    exp_len = expression.length();


    for(int i = 0; expression[i] != '.' && i < exp_len; ++i) {
        if(expression[i] == ' ') continue; //ignore spaces

        //if char is digit...
        if(expression[i] >= '0' && expression[i] <= '9') {
            todo.push(expression[i] - '0');
        } else { //char is operator...
            int nums[] = {0, 0};
            get_nums(todo, nums);
            todo.push(do_operation(expression[i], nums[0], nums[1]));
        }
    }

    std::cout << "\nResult is: " << todo.top() << std::endl;

    return 0;
}