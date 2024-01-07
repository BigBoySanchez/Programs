#include "File_Handler.h"
#include <time.h>       //seeding rng
#include <stdlib.h>     //malloc, rand
#include <stdio.h>      //fprintf, sscanf, FILE
#include <string.h>     //strlen, strtok

#define MAX_LANGUAGES 32

//prints an array as a list from 1 to sizeof(array)
void print_arr(FILE *ostream, char *WORDS[], const int SIZE) {
    for(int i = 1; i <= SIZE; i++) {
        fprintf(ostream, "%d. %s\n", i, WORDS[i - 1]);
    }

    return;
}

int main() {
    FILE *user_stream = stdout;
    FILE *data_stream = fopen("Langs.csv", "r+"); //r+ = read & write
    char *langs[MAX_LANGUAGES];
    double weights[MAX_LANGUAGES];
    int streaks[MAX_LANGUAGES];
    void *arrays[] = {langs, weights, streaks};
    const int READ_PROCESSES[] = {STRING, DOUBLE, INT};
    int num_langs = read(data_stream, arrays, READ_PROCESSES, sizeof(arrays));
    
    //check if Langs was opened
    if(data_stream == NULL) {
        printf("Could not open file \"Langs.csv\".");
        return 1;
    }

    //seeding random number generator
    struct timespec seed;
    timespec_get(&seed, TIME_UTC);
    srand(seed.tv_nsec);
    
    int rand_choice = (rand() % num_langs);

    
    //print langs with intro
    fprintf(user_stream, "\nLanguages:\n----------\n");
    print_arr(user_stream, langs, num_langs);


    //print the chosen language
    fprintf(user_stream, "----------\n\nUse %d: %s\n\n", rand_choice + 1, langs[rand_choice]);

    //release allocated data
    fclose(data_stream);
    for(int i = 0; i < num_langs; i++) free(langs[i]);

    return 0;
}