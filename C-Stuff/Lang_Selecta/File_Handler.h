#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 128

enum PROCESS_CODES {
    STRING = 0,
    INT = 1,
    DOUBLE = 2
};

//initialize arrays using data_stream. returns # of lines read or -1 on error
int read(FILE *data_stream, void* arrays[], const int READ_PROCESSES[], const int NUM_ARRAYS) {
    int num_read = 0;
    char line[BUF_SIZE];

    while(fgets(line, sizeof(line), data_stream) != NULL) { //read line of file into line until EOF
        char *token = strtok(line, ",\n");
        const int TOK_LEN = strlen(token);
        int process_num = 0;

        while(process_num < NUM_ARRAYS) { 
            const int CURR_PROCESS = READ_PROCESSES[process_num];
            void *curr_array = arrays[process_num];
            
            //read data into appropriate array based on process
            //returns -1 on invalid process
            switch (CURR_PROCESS) {
                case STRING:
                    //assumes string has quotes
                    //remove quotes around string
                    token[TOK_LEN - 1] = '\0';
                    token++;

                    //alloc space for string
                    ((char **)curr_array)[num_read] = malloc((TOK_LEN - 2) * sizeof(char));
                    if(((char **)curr_array)[num_read] == NULL) return -1;
                    
                    strcpy(((char **)curr_array)[num_read], token);
                    break;
                case INT:
                    sscanf(token, "%d", &((int *)curr_array)[num_read]);
                    break;
                case DOUBLE:
                    sscanf(token, "%lf", &((double *)curr_array)[num_read]);
                    break;
                default:
                    return -1;
                    break;
            }
            //get next token
            token = strtok(NULL, ",\n");
            process_num++;
        }
        num_read++;
    }

    return num_read;
}

//WIP
//Update file weights and streaks
void update_file() {
    return;
}

#endif