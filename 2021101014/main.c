#include "headers.h"


// write comments
// error handling
// color
// handling tabs and spaces

// spec 4 
// spec 5
// spec 6
// readme
// previous commands ls discover check once

int executeCommand(char* buffer_command, char* command)
{
    char redirCommand[1024];
    strcpy(redirCommand, buffer_command);
    int indexRedir = 0;
    int leftIndex = -1;
    int rightIndex = -1;
    int rightDobIndex = -1;
    int lenRedir = strlen(redirCommand);
    for(int ind = 0; ind < lenRedir; ind++)
    {
        if(redirCommand[ind] == '<')
            leftIndex = ind;
        else if(redirCommand[ind] == '>')
        {
            if(redirCommand[ind+1] == '>')
                rightDobIndex = ind;
            else
                rightIndex = ind;
            break;
        }
    } 
    char inputFile[256];
    char outputFile[256];
    // printf("%d %d %d\n", leftIndex, rightIndex, rightDobIndex);
    int i;
    int myInd = 0;
    if(leftIndex != -1)
    {
        for(i = leftIndex+2; buffer_command[i] != ' ' && buffer_command[i] != '\n'; i++)
        {
            inputFile[myInd] = buffer_command[i];
            myInd++;
        }
    }
    inputFile[myInd] = '\0';
    myInd = 0;
    if(rightIndex != -1)
    {
        for(i = rightIndex+2; buffer_command[i] != ' ' && buffer_command[i] != '\n'; i++)
        {
            outputFile[myInd] = buffer_command[i];
            myInd++;
        }
    }
    //printf("%s\n", outputFile);
    if(rightDobIndex != -1)
    {
        for(i = rightDobIndex+3; buffer_command[i] != ' ' && buffer_command[i] != '\n'; i++)
        {
            outputFile[myInd] = buffer_command[i];
            myInd++;
        }
    }
    outputFile[myInd] = '\0';

    // printf("out 3: %d\n", STDOUT_FILENO);
    int stdoutFD = dup(STDOUT_FILENO);
    // printf("out 4: %d\n", STDOUT_FILENO);
    // printf("%d\n", stdoutFD);
    
    int stdinFD = dup(STDIN_FILENO);
    

    int inputFileFD = 0;
    int outputFileFD = 0;

    if(inputFile[0] != '\0')
    {
        inputFileFD = open(inputFile, O_RDONLY);
        dup2(inputFileFD, STDIN_FILENO);
    }
    if(outputFile[0] != '\0' && rightIndex != -1)
    {
        // printf("outputfile: %s\n", outputFile);
        outputFileFD = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(outputFileFD, STDOUT_FILENO);
        // printf("hi\n");
    }
    else if(outputFile[0] != '\0' && rightDobIndex != -1)
    {
        outputFileFD = open(outputFile, O_CREAT | O_WRONLY | O_APPEND, 0644);
        dup2(outputFileFD, STDOUT_FILENO);
    }
    addHistory(buffer_command);
    int noArguments = 0;
    strcpy(redirCommand, buffer_command);
    // printf("buff: %s\n", buffer_command);
    // int spaceFlag = 0;
    // if(buffer_command[0] == ' ')
    //     spaceFlag = 1;
    // myInd = 0;
    // for(i = spaceFlag; buffer_command[i] != ' ' && buffer_command[i] != '\n'; i++)
    // {
    //     // printf("%c", buffer_command[i]);
    //     command[myInd] = buffer_command[i];
    //     myInd++;
    // }
    // command[myInd] = '\0';
    // printf("command: %s\n", command);
    // if(inputFileFD || outputFileFD)
    // {
    //     for (i = 0; command[i] != '\0'; i++)
    //     {
    //         buffer_command[i] = command[i];
    //     }
    //     buffer_command[i] = '\0';
    // }
    //printf("buff: %s\n", buffer_command);

    if(inputFileFD || outputFileFD)
        command = strtok(buffer_command, "<>");
    else
        command = strtok(redirCommand, " ");
    // printf("comm: %s\n", command);
    //printf("buff: %s\n", buffer_command);
    if(!strcmp(command, "pwd"))
        pwd();
    else if (!strcmp(command, "cd"))
    {
        char* npath = malloc(256*sizeof(char));
        npath = strtok(buffer_command, " \t\n");
        // int i = 0;
        npath = strtok(NULL, " \t\n");
        cd(npath);
    }
    else if(!strcmp(command, "echo"))
    {
        echo(buffer_command, command);
    }
    else if(!strcmp(command, "q") || !strcmp(command, "quit") || !strcmp(command, "exit"))
    {
        // printf("not here\n");
        return 275;
    }
    else if(!strcmp(command, "ls"))
    {
        char* rest = buffer_command;
        ls(noArguments - 1, buffer_command);
    }
    else if(!strcmp(command, "history"))
    {
        history();
    }
    else if(!strcmp(command, "discover"))
    {
        discover(buffer_command);
        if(!dfs_flag)
            printf("Not Found\n");
    }
    else if(!strcmp(command, "pinfo"))
    {
        pinfo(buffer_command);
    }
    else if(!strcmp(command, "sig"))
    {
        printf("%s\n", buffer_command);
        sig(buffer_command);
    }
    else if(!strcmp(command, "jobs"))
    {
        jobs(buffer_command);
    }
    else if(!strcmp(command, "bg"))
    {
        bg(buffer_command);
    }
    else if(!strcmp(command, "fg"))
    {
        fg(buffer_command);
    }
    else
    {
        syscalls(buffer_command);
    }
        

    // if(inputFileFD != -1)
    //     printf("\n");
    dup2(stdinFD, STDIN_FILENO);
    dup2(stdoutFD, STDOUT_FILENO);
}

int main( void )
{
    dfs_flag = 0;
    getcwd(home_dir, sizeof(home_dir));
    bgp = LL_init();
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    while(1)
    {
        signal(SIGCHLD, wait_child_proc);
        prompt();
        totalTime = 0;
        size_t len = 0;
        char *line;
        fflush(0);
        char orignal_command[1024];
        char* buffer_command = malloc(1024*sizeof(char));
        char command[256];
        buffer_command[0] = '\0';
        command[0] = '\0';

        line = fgets(orignal_command, sizeof(orignal_command), stdin);
        if(!line) return 0; //handling ctrl+D;
        if(!strcmp(line, "\n")) continue;
        char *saveptr = malloc(1024*sizeof(char));
        char* pipe_command = malloc(1024*sizeof(char));
        buffer_command = strtok_r(orignal_command, ";\n", &saveptr);
        while((buffer_command))
        {   
            // printf("%s\n", buffer_command);
            int pipeCount = 0;
            int lenPipe = strlen(buffer_command);
            for(int myLen = 0; myLen < lenPipe; myLen++)
            {
                if(buffer_command[myLen] == '|') pipeCount++;
            }
            if(!pipeCount)
            {
                // printf("shash\n");
                // printf("%s\n",buffer_command);
                int res = executeCommand(buffer_command, command);
                if(res == 275) return 0;
                buffer_command= strtok_r(NULL, ";\n", &saveptr);
                continue;
            }
            if(pipeCount != 0)
            {
                char* pipeArray[pipeCount];
                int mainCount = 0;
                char* pipePtr = malloc(1024*sizeof(char));
                pipe_command = strtok_r(buffer_command, "|\n", &pipePtr);
                for(int i = 0; i <= pipeCount; i++)
                {
                    pipeArray[mainCount] = pipe_command;
                    // printf("%s\n", pipeArray[mainCount]);
                    mainCount++;
                    pipe_command = strtok_r(NULL, "|\n", &pipePtr);
                }
                pipeArray[mainCount] = NULL;
                // printf("pipeCount: %d\n", pipeCount);
                // printf("mainCount: %d\n", mainCount);
                int pid = 0;
                int orgIn = dup(STDIN_FILENO);
                int orgOut = dup(STDOUT_FILENO);
                for(int i = 0; i <= pipeCount; i++)
                {
                    int fd[2];
                    pipe(fd);
                    int tempIn = dup(STDIN_FILENO);
                    int tempOut = dup(STDOUT_FILENO);
                    // printf("%d\n", fd[0]);
                    pid = fork();
                    // printf("pid: %d %d\n",i, pid);
                    if(!pid) // child process
                    {
                        // printf("%s, %d\n", pipeArray[i], i);
                        if(i!= 0)dup2(orgIn, STDIN_FILENO);
                        // printf("in child mc: %d 0: %d\n", mainCount, orgIn);
                        // printf("out 1: %d\n", STDOUT_FILENO);
                        if(i != pipeCount) 
                        {
                            // all inputs except last get written to fd[1] of respective input
                            dup2(fd[1], STDOUT_FILENO);
                        }
                        if( i == pipeCount)
                        {
                            dup2(orgOut, 1);
                        }
                        // printf("out 2: %d\n", STDOUT_FILENO);
                        close(fd[0]);
                        // char* stringArr[3];
                        // stringArr[0] = malloc(100*sizeof(char));
                        // stringArr[0] = strtok(pipeArray[i], " ");
                        // // printf("PLS WORK\n");     
                        // // printf("stringArr[0] %s\n", stringArr[0]);
                        // stringArr[1] = malloc(100*sizeof(char));
                        // stringArr[1] = strtok(NULL, " ");
                        // // printf("stringArr[1] %s\n", stringArr[1]);
                        // stringArr[2] = NULL;
                        // execvp(stringArr[0], stringArr);
                        int res = executeCommand(pipeArray[i], command);
                        dup2(tempIn, 0);
                        dup2(tempOut, 1);
                        if(res == 275) return 0;                        
                        exit(0);
                    } 
                    else
                    {
                        wait(NULL);
                        // printf("in parent mc: %d 0: %d\n", mainCount, fd[0]);
                        orgIn = fd[0];
                        close(fd[1]);
                    }
                    mainCount++;
                    // printf("-------- %d is over\n", i);
                }
                buffer_command= strtok_r(NULL, ";\n", &saveptr);
            }
        }

    }
}