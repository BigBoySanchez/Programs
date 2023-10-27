/*
Certainly! Here are some beginner-level C coding challenges:

Print "Hello, world!" to the console.
Write a program that asks the user to input two integers and then prints the sum.
Write a program that calculates and prints the area of a circle, given its radius.
Write a program that reads in a person's age and then prints a message that says whether they are old enough to vote (i.e., 18 or older).
Write a program that reads in a string of text and then prints out the length of the string.
Write a program that reads in a string of text and then prints out the number of vowels in the string.
Write a program that reads in a series of numbers from the user and then prints out the maximum and minimum values.

Write a program that reads in a series of numbers from the user and then calculates and prints the average.
Write a program with proper int input validation (check if its a number, check if its in range)

These challenges should help you get started with C programming. Good luck and have fun!
*/


#include <stdio.h> //printf(), scanf(), fgets()
#include <string.h> //strlen()
#include <ctype.h> //toupper(), tolower()
#include <stdlib.h> //malloc(), calloc(), free()
#include <limits.h> //INT_MAX, INT_MIN

void HelloWorld()
{
    printf("Hello world!\n\n");
}

void Add()
{
    int num1, num2, total;

    printf("Give me 2 numbers to add: ");
    scanf("%d %d", &num1, &num2);
    total = num1 + num2;
    printf("\nThe total of %d and %d is: %d\n\n", num1, num2, total);
}

void GPTAdd()
{
    int num1, num2, total;
    int input_success;

    do {
        printf("Give me 2 numbers to add: ");
        input_success = scanf("%d %d", &num1, &num2); //scanf returns # of successful variable assignments

        // If user input is incorrect, clear the input buffer
        if (input_success != 2) {
            printf("Invalid input. Please enter two integers separated by a space.\n");
            while (getchar() != '\n') {}
        }

    } while (input_success != 2);

    total = num1 + num2;
    printf("\nThe total of %d and %d is: %d\n\n", num1, num2, total);
}

void CircleArea()
{
    const double PI = 3.14159265358979323846;
    double radius, area;   

    printf("Give me a radius: ");
    scanf("%lf", &radius);
    area = PI * radius * radius;
    printf("\nThe area of a circle with raidus %lf is: %lf\n\n", radius, area);
}

void Voting()
{
    int userAge;

    printf("Enter your age in years: ");
    scanf("%d", &userAge);
    
    if(userAge >= 18) {printf("You may vote.\n\n");}
    else {printf("You may not vote.\n\n");}
}

void Reader()
{
    char userStr[100];
    int c;
    
    while (c != '\n' && c != EOF) {c = getchar();}
    
    printf("Enter a string: ");
    fgets(userStr, sizeof(userStr), stdin);
    
    userStr[strlen(userStr) - 1] = '\0';
    //userStr[strscpn(userStr, "\n")]; //alternative

    printf("The size of \"%s\" is: %zu\n\n", userStr, strlen(userStr));
}

void EasyReader() //simple but leaves \n in buffer after
{
    char userStr[100];

    printf("Enter a string: ");
    scanf(" %[^\n]s", userStr);
    printf("The size of \"%s\" is: %zu\n\n", userStr, strlen(userStr));

    while(getchar() != '\n'); //to get rid of \n
}

void VowelCounter()
{
    char userStr[100];
    int vowelCount = 0;

    printf("Enter a string: ");
    fgets(userStr, sizeof(userStr), stdin);
    userStr[strlen(userStr) - 1] = '\0';

    for(int i = 0; i < strlen(userStr); i++)
    {
        char temp = tolower(userStr[i]);
        
        if(temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u') vowelCount++;
    }

    printf("# of vowels in \"%s\" is: %d\n\n", userStr, vowelCount);
}

void MaxNMin()
{
    int* userNums = NULL;
    int inputCheck, min, max;
    size_t numsSize;

    while(1)
    {
        printf("Enter amount of nums: ");
        inputCheck = scanf("%zu", &numsSize);
        while(getchar() != '\n');
        
        if(inputCheck == 1 && numsSize > 0) break;
        else printf("Error: Invalid input.\n\n");
    }

    userNums = calloc(numsSize, sizeof(int));
    if(userNums == NULL)
    {
        printf("Error: Can't allocate memory.\n\n");
        exit(1);
    }

    for (size_t i = 0; i < numsSize; i++)
    {
        while (1)
        {
            printf("Enter num #%zu: ", i + 1);
            inputCheck = scanf("%d", userNums + i);
            while(getchar() != '\n');

            if(inputCheck == 1) break;
            else printf("Error: Invalid input.\n\n");
        }

        if(i == 0)
        {
            min = userNums[0];
            max = userNums[0];
        }
        else
        {
            min = (min > userNums[i])? userNums[i] : min;
            max = (max < userNums[i])? userNums[i] : max;
        }
    }

    printf("\nThe max of the set is: %d\n", max);
    printf("The min of the set is: %d\n\n", min);

    free(userNums);
}

int main(int argc, char* argv[]) //the parameters aren't needed unless ur tryna input smth from command-line
{
    HelloWorld();
    //Add();
    //CircleArea();
    //Voting();
    //Reader();
    //EasyReader();
    //VowelCounter();
    //GPTAdd();
    MaxNMin();


    return 0;
}