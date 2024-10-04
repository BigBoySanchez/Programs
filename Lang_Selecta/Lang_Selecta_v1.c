#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//prints an array as a list from 1 to sizeof(array)
void print_arr(FILE *ostream, const char *WORDS[], const int SIZE) {
    for(int i = 1; i <= SIZE; i++) {
        fprintf(ostream, "%d. %s\n", i, WORDS[i - 1]);
    }

    return;
}

int main() {
    int num_langs = 4; 
    const char *LANGS[4] = { "Java",
                            "Python3",
                            "C",
                            "C++"};
    FILE *user_stream = stdout;
    
    //seeding random number generator
    struct timespec seed;
    timespec_get(&seed, TIME_UTC);
    srand(seed.tv_nsec);
    
    int rand_choice = (rand() % num_langs);

    
    //print langs with intro
    fprintf(user_stream, "\nLanguages:\n----------\n");
    print_arr(user_stream, LANGS, num_langs);


    //print the chosen language
    fprintf(user_stream, "----------\n\nUse %d: %s\n\n", rand_choice + 1, LANGS[rand_choice]);

    return 0;
}