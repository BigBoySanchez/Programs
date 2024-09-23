//hw1.c

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

typedef enum LetterGrade {
    A  = 4,
    B = 3,
    C = 2,
    D = 1,
    F = 0
} LetterGrade;

void stdinIgnore() {
    while(getchar() != '\n');
}

double getArrayAverage(int32_t *vec, const int32_t size) {
    double sum = 0;
    for(int32_t i = 0; i < size; ++i) {
        sum += vec[i];
    }

    double avg = sum / size;
    return avg;
}

void convertCharToLetterGrade(char *grade) {
    switch (*grade) {
    case 'A': case 'a':
        *grade = 4;
        return;
    case 'B': case 'b':
        *grade = 3;
        return;
    case 'C': case 'c':
        *grade = 2;
        return;
    case 'D': case 'd':
        *grade = 1;
        return;
    case 'F': case 'f':
        *grade = 0;
        return;
    default:
        printf("Warning... Invalid Character... Recording an F.\n");
        return;
    }
}

LetterGrade getLetterGradeFromAverage(const double avg) {
    if (avg >= 90)
        return A;
    else if (avg >= 80)
        return B;
    else if (avg >= 70)
        return C;
    else if (avg >= 60)
        return D;
    else
        return F;
}

int main() {
    char firstName[BUF_SIZE];
    printf("Please enter your first name: ");
    fgets(firstName, BUF_SIZE, stdin);
    sscanf(firstName, "%s", firstName);

    char lastName[BUF_SIZE];
    printf("Please enter your last name: ");
    fgets(lastName, BUF_SIZE, stdin);
    sscanf(lastName, "%s", lastName);

    int32_t numPrevCourses;
    printf("Enter number of previous courses: ");
    scanf("%d", &numPrevCourses);
    stdinIgnore();

    LetterGrade *prevGrades = malloc(sizeof(LetterGrade) * numPrevCourses);
    for (int32_t courseIx = 0; courseIx < numPrevCourses; ++courseIx) {
        printf("Enter letter grade for course %d: ", courseIx);
        char letterGrade;
        scanf("%c", &letterGrade);
        stdinIgnore();

        convertCharToLetterGrade(&letterGrade);
        prevGrades[courseIx] = (LetterGrade)(letterGrade);
    }
    
    int32_t numExams;
    printf("Enter number of exams this semester: ");
    scanf("%d", &numExams);
    stdinIgnore();

    int32_t *examGrades = malloc(sizeof(int32_t) * numExams);
    for(int32_t examIx = 0; examIx < numExams; ++examIx) {
        printf("Enter grade for exam %d as an integer: ", examIx);
        scanf("%d", &examGrades[examIx]);
        stdinIgnore();
    }

    //const auto fullName = firstName + " " + lastName;
    char fullName[BUF_SIZE];
    int32_t remaining = BUF_SIZE - 1;

    strncat(fullName, firstName, remaining);
    remaining -= strlen(firstName);
    if(remaining > 0) {
        fullName[BUF_SIZE - 1 - remaining] = ' ';
        remaining--;
        fullName[BUF_SIZE - 1 - remaining] = '\0';
    }
    strncat(fullName, lastName, remaining);

    printf("Grade Report For %s:\n", fullName);
    double examAverage = getArrayAverage(examGrades, numExams);
    printf("Your exam average is: %lf\n", examAverage);

    // get GPA with newest course added:
    LetterGrade newLetterGrade = getLetterGradeFromAverage(examAverage);
    prevGrades = realloc(prevGrades, sizeof(LetterGrade) * (++numPrevCourses));
    prevGrades[numPrevCourses - 1] = newLetterGrade;
    double gpa = getArrayAverage(prevGrades, numPrevCourses);
    printf("Your latest GPA is: %lf\n", gpa);

    free(prevGrades);
    free(examGrades);

    return 0;
}

/*
REPORT:

    The main advantage C++ has over C in this case is its templates. For the getArrayAverage 
    function in C++, it takes a vector of either int32_t's or doubles. C doesn't have vectors,
    so I used a pointer. The pointer was originally void, but converting it to a double from there
    doesn't work since the bit patterns are meant to represent integers. Knowing this, I make the vector
    a int32_t* since enums are interpreted as integers. I'm not too sure if this goes against the 
    assignment rules, but it works.

    C++ also has more safety features than C. In C++, strings operate more like vectors, which
    are safer than a standard array or char*. For this assignment, I wanted to retain some of
    that safety, which is why I used fgets, sscanf and strncat as to avoid a buffer overflow.
    Due to my use of pointers over C++ vectors, it's easier for my program to have memory leaks
    as well. It's definitely possible since I call malloc and realloc without checking for NULL.
    In C++ it would've all been handled by the compiler(?), which is much safer than trusting
    it to me.
*/