#include "File_Handler.h"   //read
#include "Options_Funcs.h"        //options functions
#include <time.h>           //seeding rng
#include <stdlib.h>         //malloc, rand
#include <stdio.h>          //fprintf, sscanf, FILE
#include <string.h>         //strlen, strtok
#include <conio.h>

#define MAX_LANGUAGES 32

enum CHOICES{
    RUNW,
    RUNU,
    BLACKLIST,
    NUM_CHOSEN,
    EDIT_FILE,
    QUIT
};

//seeds random number generator using nanoseconds
void seed_rng() {
    struct timespec seed;
    timespec_get(&seed, TIME_UTC);
    srand(seed.tv_nsec);
}

int main() {
    FILE *user_stream = stdout;
    FILE *user_in = stdin;
    FILE *data_stream = fopen("Langs.csv", "r+"); //r+ = read & write
    char *all_langs[MAX_LANGUAGES];
    int weights[MAX_LANGUAGES];
    int temp_weights[MAX_LANGUAGES];
    int streaks[MAX_LANGUAGES];
    void *arrays[] = {all_langs, weights, streaks};
    const int READ_PROCESSES[] = {STRING, INT, INT};
    const char *OPTIONS[] = {"Run Weighted", "Run Unweighted", "Blacklist(WIP)", "Change Amount Chosen(WIP)", "Edit File(WIP)", "Quit"};
    int num_langs = 0;
    int user_choice = 0;
    seed_rng();
    
    //check if Langs was opened
    if(data_stream == NULL) {
        printf("Could not open file \"Langs.csv\".");
        return 1;
    } else num_langs = read(data_stream, arrays, READ_PROCESSES, sizeof(READ_PROCESSES) / sizeof(READ_PROCESSES[0]));

    while(user_choice != QUIT) {
        int rand_choice = 0;
        print_list(user_stream, OPTIONS, sizeof(OPTIONS) / sizeof(OPTIONS[0]), "Options");

        //prompt user for option choice
        fprintf(user_stream, "Choose: ");
        fscanf(user_in, "%d", &user_choice);
        user_choice--;
        if(user_stream == stdout) fprintf(user_stream, "\e[1;1H\e[2J"); //clear stream if printing on console

        switch (user_choice) {
            case RUNW:
                rand_choice = weighted_choice(weights, num_langs, rand());
                if(rand_choice == -1) {
                    fprintf(user_stream, "Nothing was chosen.\n");
                } else {
                    fprintf(user_stream, "Use: %s\n", all_langs[rand_choice]);
                }
                break;
            
            case RUNU:
                rand_choice = (rand() % num_langs);
                fprintf(user_stream, "Use: %s\n", all_langs[rand_choice]);
                break;

            case QUIT:
                break;
            
            default:
                return 1;
                break;
        } 
    }

    //release allocated data
    fclose(data_stream);
    for(int i = 0; i < num_langs; i++) free(all_langs[i]);

    return 0;
}