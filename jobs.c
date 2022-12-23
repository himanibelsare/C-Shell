#include "headers.h"

int jobs(char* buffer_command)
{
    char proStatus = '\0';
    char* newStatus = malloc(20*sizeof(char));
    char* name = malloc(1024*sizeof(char));
    char* filename = malloc(1024*sizeof(char));
    char* filetogetname = malloc(1024*sizeof(char));
    int count = 1;
    for(LL_Node* i = bgp->head; i != NULL; i = i->next)
    {
        // printf("%d\n", i->val);
        sprintf(filename, "/proc/%d/stat", i->val);
        //printf("%s\n", filename);

        FILE* file = fopen(filename, "r");
        if(!file)
        {
            printf("ERROR\n");
            return -1;
        }
        else
        {
            fscanf(file, "%*d, %*s, %c", &proStatus);

            if(proStatus == 'T')
                newStatus = "Stopped";
            else
                newStatus = "Running";

            sprintf(filetogetname, "/proc/%d/comm", i->val);
            FILE* file2 = fopen(filetogetname, "r");
            fgets(name, sizeof(name), file2);
            int len = strlen(name);
            name[len - 1] = ' ';
            //printf("%s", name);

            printf("[%d] %s %s [%d]\n", count, newStatus, name, i->val);
            count++;
        }
    }
    
    return 0;
}