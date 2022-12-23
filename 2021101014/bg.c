#include "headers.h"

int bg(char* buffer_command) 
{
    printf("%s\n", buffer_command);
    char* token = malloc(256*sizeof(char));
    strtok(buffer_command, " ");
    token = strtok(NULL, " ");
    int pid = atoi(token);
    if (kill(pid, SIGCONT) < 0) 
    {
        perror("Error");
        return -1;
    }
}