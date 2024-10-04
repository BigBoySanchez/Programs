#ifndef OPTIONS_FUNCS
#define OPTIONS_FUNCS

#include <stdlib.h>         //malloc, rand
#include <stdio.h>          //fprintf, sscanf, FILE
#include <string.h>         //strlen, strtok

#define MAX_WORD_LENGTH 128

//chooses using weights. returns position of choice or -1 if nothing was chosen.
int weighted_choice(int weights[], const int NUM_LANGS, int rand_num) {
    int total = 0;
    
    for(int i = 0; i < NUM_LANGS; i++)
        total += weights[i];
    rand_num = rand_num % total;

    for(int i = 0; i < NUM_LANGS; i++) {
        if(rand_num < weights[i]) return i;
        rand_num -= weights[i];
    }

    return -1;
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

#endif