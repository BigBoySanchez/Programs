#include "File_Handler.h"   //read
#include <time.h>           //seeding rng
#include <stdlib.h>         //malloc, rand
#include <stdio.h>          //fprintf, sscanf, FILE
#include <string.h>         //strlen, strtok
#include <conio.h>

#define MAX_LANGUAGES 32
#define MAX_WORD_LENGTH 128

enum CHOICES{
    RUN = 1,
    BLACKLIST = 2,
    NUM_CHOSEN = 3,
    EDIT_FILE = 4,
    QUIT = 5
};

//seeds random number generator using nanoseconds
void seed_rng() {
    struct timespec seed;
    timespec_get(&seed, TIME_UTC);
    srand(seed.tv_nsec);
}

//makes top and bottom of list border. returns top of border as string
char *init_top(const char *WORDS[], const int WORDS_SIZE) {
    char *TOP = malloc(sizeof(char) * MAX_WORD_LENGTH); //dealloc in print_list
    TOP[0] = '+';
    TOP[1] = '\0';
    size_t max_word = 0;

    for(int word_idx = 0; word_idx < WORDS_SIZE; ++word_idx) {
        if(max_word > strnlen(WORDS[word_idx], MAX_WORD_LENGTH)) continue; //skip current word if it's too small

        max_word = strnlen(WORDS[word_idx], MAX_WORD_LENGTH); //otherwise max length is current length
        while(strnlen(TOP, MAX_WORD_LENGTH) < max_word + 4) strncat(TOP, "-", MAX_WORD_LENGTH); 
    }
    strncat(TOP, "+", MAX_WORD_LENGTH); //add right corner

    return TOP;
}


//prints lists with name, border, and number
void print_list(FILE *ostream, const char *WORDS[], const int WORDS_SIZE, const char* LIST_NAME) {
    char *TOP = init_top(WORDS, WORDS_SIZE);
    const int BORDER_WIDTH = strlen(TOP);

    fprintf(ostream, "\n%s:\n%s\n", LIST_NAME, TOP); //print list name and top
    for(int i = 0; i < WORDS_SIZE; ++i) fprintf(ostream, "|%d. %-*s|\n", i + 1, BORDER_WIDTH - 5, WORDS[i]); //print each element bounded by "||"
    fprintf(ostream, "%s\n\n", TOP); //print bottom

    free(TOP); //free allocated string from init_top
}

int main() {
    FILE *user_stream = stdout;
    FILE *user_in = stdin;
    FILE *data_stream = fopen("Langs.csv", "r+"); //r+ = read & write
    char *all_langs[MAX_LANGUAGES];
    double weights[MAX_LANGUAGES];
    int streaks[MAX_LANGUAGES];
    void *arrays[] = {all_langs, weights, streaks};
    const int READ_PROCESSES[] = {STRING, DOUBLE, INT};
    const char *OPTIONS[] = {"Run", "Blacklist(WIP)", "Change Amount Chosen(WIP)", "Edit File(WIP)", "Quit"};
    int num_langs = 0;
    int user_choice = 0;
    seed_rng();
    
    //check if Langs was opened
    if(data_stream == NULL) {
        printf("Could not open file \"Langs.csv\".");
        return 1;
    } else num_langs = read(data_stream, arrays, READ_PROCESSES, 3);

    while(user_choice != QUIT) {
        print_list(user_stream, OPTIONS, 5, "Options"); //print all 5 options

        //prompt user for option choice
        fprintf(user_stream, "Choose: ");
        fscanf(user_in, "%d", &user_choice);
        if(user_stream == stdout) fprintf(user_stream, "\e[1;1H\e[2J"); //clear stream if printing on console

        switch (user_choice) {
            case RUN:
                int rand_choice = (rand() % num_langs); //choose random value
                fprintf(user_stream, "Use: %s\n", all_langs[rand_choice]);
                break;
            
            default:
                return 1; //bad input
                break;
        } 
    }

    //release allocated data
    fclose(data_stream);
    for(int i = 0; i < num_langs; i++) free(all_langs[i]);

    return 0;
}