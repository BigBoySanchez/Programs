#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 128

enum PROCESS_CODES{
    STRING = 0,
    INT = 1,
    DOUBLE = 2
};


//initialize arrays using data_stream. returns # of lines read or -1 on error
int read(FILE *data_stream, void *arrays[], const int READ_PROCESSES[], const int NUM_ARRAYS) {
    int num_read = 0;
    char line[BUF_SIZE];

    while(fgets(line, sizeof(line), data_stream) != NULL) { //read line of file into line until EOF
        char *format[BUF_SIZE];
        char *token = strtoken(line, "'\n");

        switch (READ_PROCESSES[num_read])
        {
            case STRING:
                format = "%s";
                break;
            case INT:
                format = "%d";
                break;
            case DOUBLE:
                format = "%lf";
                break;
            default:
                return -1;
                break;
        }
        
        //remove quotes around string
        lang_to_add[lang_len - 1] = '\0';
        lang_to_add++;

        //alloc space for string
        langs[num_read] = malloc((lang_len - 2) * sizeof(char));
        if(langs[num_read] == NULL) {
            printf("Can't allocate curr_string.\n");
            return 1;
        } 
        
        strcpy(langs[num_read], lang_to_add);
        num_read++;
    }

    return num_read;
}