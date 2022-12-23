#include "headers.h"

int getHistory(char** commands) {
    // printf("hi");
    size_t size = 1024;
    int noOfCommands = 0;
    char* path = malloc(size*sizeof(char));
    commands[0] = NULL;
    sprintf(path, "%s/history.txt", home_dir);
    // printf("%s", path);

    FILE* file = fopen(path, "r");

    if (file != NULL) 
    {
        for (int i = 0; i < 20; i++) 
        {
            // printf("%d\n", i);
            commands[i] = malloc(100*sizeof(char));
            int n = getline(&commands[i], &size, file);
            // printf("commands[i]: %s\n", commands[i]);
            // printf("what: %d\n", n);
            if(n <= 0) break;
            noOfCommands++;
        }
        // printf("duhgisudeghr\n");
        fclose(file);
    }
    free(path);
    return noOfCommands;
}

void addHistory(char* str)
{
    // char* commands[20];
    // long unsigned size = 1024;
    // char path[1024];
    // printf("hi");
    // int noOfCommands = getHistory(commands);
    // printf("%d", noOfCommands);

    /* i literally dont understand why the above code gives seg fault but the below one doesnt*/
    /* somebody please help*/

    long unsigned size = 1024;
    char path[1024];
    // printf("hi1");
    char* commands[20];
    int noOfCommands = getHistory(commands);
    // printf("comm: %d\n", noOfCommands);
    // printf("%s", commands[noOfCommands-1]);
    // printf("here\n");

    if (noOfCommands > 0 && strcmp(str, commands[noOfCommands - 1]) == 0)
    {
        return;
    }
    else
    {
        sprintf(path, "%s/history.txt", home_dir);
        // printf("comm2: %d", noOfCommands);

        FILE* file = fopen(path, "w");

        if (file) 
        {
            if(noOfCommands < 20)
            {
                for (int i = 0; i < noOfCommands; i++) 
                    fprintf(file, "%s", commands[i]);
                fprintf(file, "%s\n", str);
                // printf("done");
            }
            else if(noOfCommands == 20)
            {
                for (int i = 1; i < noOfCommands; i++) 
                    fprintf(file, "%s", commands[i]);
                fprintf(file, "%s\n", str);
            }
            
            fclose(file);
       }  
    }
}

void history() {
    int max = 10;
    char* commands[20];
    int noOfCommands = getHistory(commands);
    // printf("in history(): %d\n", noOfCommands);
    // printf("hi");
    if (noOfCommands < max)
    {
        for(int i = 0; i < noOfCommands; i++)
        {
            printf("%s", commands[i]);
        }
    }
    else
    {
        for(int i = noOfCommands-10; i < noOfCommands; i++)
        {
            printf("%s", commands[i]);
        }
    }
    return;
}