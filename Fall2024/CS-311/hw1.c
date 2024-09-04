#include <stdlib.h>
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

//vec must be castable into a double*
double getArrayAverage(void *vec, const int32_t size) {
    double sum = 0;
    for(int32_t i = 0; i < size; ++i) {
        sum += *(double *)(vec);
    }
    
    const double avg = sum / size;
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
    //WIP: stack alloc?
    //scanf w/ buf_size?
    char *firstName[BUF_SIZE];
    printf("Please enter your first name: ");
    fgets(firstName, BUF_SIZE, stdin);

    char *lastName[BUF_SIZE];
    printf("Please enter your last name: ");
    fgets(lastName, BUF_SIZE, stdin);

    int32_t numPrevCourses;
    printf("Enter number of previous courses: ");
    scanf("%d", &numPrevCourses);
    //fflush(stdin);

    LetterGrade *prevGrades = malloc(sizeof(LetterGrade) * numPrevCourses);
    for (int32_t courseIx = 0; courseIx < numPrevCourses; ++courseIx) {
        printf("Enter letter grade for course %d: ", courseIx);
        char letterGrade;
        scanf("%c", &letterGrade);
        //fflush(stdin);

        convertCharToLetterGrade(letterGrade);
        prevGrades[courseIx] = (LetterGrade)(letterGrade);
    }
    
    int32_t numExams;
    printf("Enter number of exams this semester: ");
    scanf("%d", &numExams);
    //fflush(stdin);

    int32_t *examGrades = malloc(sizeof(int32_t) * numExams);
    for(int32_t examIx = 0; examIx < numExams; ++examIx) {
        printf("Enter grade for exam %d as an integer: ", examIx);
        scanf("%d", &examGrades[examIx]);
        //fflush(stdin);

        //WIP: make const?
        //const auto fullName = firstName + " " + lastName;
        char *fullName[BUF_SIZE];
        int32_t remaining = BUF_SIZE - 1;

        strncat(fullName, firstName, remaining);
        remaining -= strlen(firstName);
        if(remaining > 0) {
            fullName[BUF_SIZE - 1 - remaining] = ' ';
            remaining--;
            fullName[BUF_SIZE - 1 - remaining] = '\0';
        }
        strncat(fullName, lastName, remaining);

        printf("Grade Report For %s:\n");    //cout << "Grade Report For " << fullName << ":\n";
        const double examAverage = getArrayAverage(examGrades, numExams);
        printf("Your exam average is: %lf\n");    //cout << "Your exam average is: " << examAverage << "\n";
    }

    return 0;
}