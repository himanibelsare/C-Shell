#include "headers.h"

void echo(char *buffer_command, char* command)
{
    //printf("%s", buffer_command);
    // char* (1024*sizeof(char));
    char* next = malloc (256*sizeof(char));
    next = strtok(buffer_command, " \t\n");
    // printf("%s hi", next);
    //printf("%s\n\n\n", command);
    while (next != NULL)
    {
        if(!strcmp(command, next))
        {
            next = strtok(NULL, " \t\n");
            continue;
        }
        // for (int i = 0; next[i] != ' ' || next[i] != '\0' || next[i] != '\n'; i++)
        // {
        //     printf("%c", next[i]);
        // }
        // printf(" ");
        printf("%s", next);
        printf(" ");
        next = strtok(NULL, " \t\n");
    }
    //free(toprint);
    printf("\n");
    free(next);
    return;
}