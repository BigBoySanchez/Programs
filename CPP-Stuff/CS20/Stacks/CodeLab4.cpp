#include <stack>
#include <iostream>
using namespace std;

int evaluate(char tokens[], int numTokens) {
	stack<int> todo;
	const char UNARY[] = {'!', '~'};
	
	for(int i = 0; i < numTokens; ++i) {
        int num1 = 0, num2 = 0;
		
		if(tokens[i] >= '0' && tokens[i] <= '9') {
			todo.push(tokens[i] - '0');
			continue;
		}
		
		bool isUnary = false;
		for(int j = 0; j < 2; ++j) {
			if(tokens[i] == UNARY[j]) {
				isUnary = true;
				break;
			}
		}
		
		if(isUnary) {
			num1 = todo.top();
			todo.pop();
			
			switch(tokens[i]) {
				case '!':
				num2 = 1;
				for(int i = num1; i > 1; --i)
					num2 *= i;
				todo.push(num2);
				break;
				
				case '~':
				todo.push(-num1);
				break;
			}
			continue;
		}
		
		if(tokens[i] != 'S') {
			num1 = todo.top();
			todo.pop();
			
			num2 = todo.top();
			todo.pop();
			
			switch(tokens[i]) {
				case '+':
				todo.push(num1 + num2);
				break;
				
				case '-':
				todo.push(num2 - num1);
				break;
				
				case '*':
				todo.push(num1 * num2);
				break;
				
				case '/':
				todo.push(num2 / num1);
				break;
				
				case '%':
				todo.push(num2 % num1);
				break;
				
				case '^':
				int powPush = 1;
				for(int i = 0; i < num1; ++i)
					powPush *= num2;
				todo.push(powPush);
				break;
			}
			continue;
		}
		
		int numnums = todo.top();
		todo.pop();
		
		for(int i = 1; i < numnums; ++i) {
			num1 = todo.top();
			todo.pop();
			
			num2 = todo.top();
			todo.pop();
			
			todo.push(num1 + num2);
		}
	}
	int ret = todo.top();
	todo.pop();
	
	return ret;
}


int main() {
   char help[] = "732S";
   int size = sizeof(help) / sizeof(char) - 1;

   cout << evaluate(help, size);
    
    return 0;
}