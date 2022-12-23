#include "headers.h"

int pinfo(char* buffer_command)
{
    // printf("here: %s\n", buffer_command);
    char pinfoPath[1024] = "/proc/"; 
    char filePath[1024];
    char exePath[1024];
    if(!strcmp(buffer_command, "pinfo"))
        strcpy(pinfoPath, "/proc/self");
    else
    {
        char* dir = malloc(4*sizeof(char));
        dir = strtok(buffer_command, " ");
        dir = strtok(NULL, " ");
        // printf("%s\n", dir);
        strcat(pinfoPath, dir);
        // printf("now here: %s\n", pinfoPath);
    }

    // printf("now here: %s\n", pinfoPath);
    strcpy(filePath, pinfoPath);
    strcpy(exePath, pinfoPath);
    strcat(filePath, "/stat");
    strcat(exePath, "/exe");
    
    // printf("filePath: %s\n", filePath);
    // printf("exePath: %s\n", exePath);
    FILE* file = fopen(filePath, "r");
    if(!file)
    {
        perror("Error");
        return -1;
    }

    int pid = -1;
    char proStatus = '\0';
    int memory = -1;
    int pg = -1;
    int tp = -1;

    fscanf(file, "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &pid, &proStatus, &pg, &tp, &memory);
    char statType;
    if(pg == tp) statType = '+';
    else statType = ' ';

    printf("pid: %d\n", pid);
    printf("Process status: %c%c\n", proStatus, statType);
    printf("memory: %d\n", memory);
    fclose(file);

    //printf("-----------------\n");

    char* path = malloc(1024*sizeof(char));

    int lenPath = readlink(exePath, path, 1024);

    // printf("%d\n", lenPath);
    // printf("%s\n", path);

    int isRelative = 0;
    path[lenPath] = '\0';
    int i = 0;
    while(1) 
    {
        if (home_dir[i] == '\0')
        {
            isRelative = 1;
            break;
        }
        if (i == lenPath || path[i] != home_dir[i]) 
        {
            break;
        }
        i++;
    }

    if(!isRelative)
    {
        printf("Executable Path -- %s\n", path);
    }
    else
    {
        path += strlen(home_dir) - 1;
        path[0] = '~';
        printf("Executable Path -- %s\n", path);
    }

}