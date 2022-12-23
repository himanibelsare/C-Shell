#include "headers.h"

char** arguments;
int argCount;

int is_background;

void syscalls(char* buffer_command)
{
    totalTime = 0;
    argCount = 0;
    arguments = (char**)malloc(1024*sizeof(char*));
    char* newtoken = malloc(256*sizeof(char));

    if(strchr(buffer_command,'&'))
        is_background = 1;
    else
        is_background = 0;

    char* actualCommand = malloc(256*sizeof(char));
    char* cmdAfterAmp = malloc(256*sizeof(char));
    strcpy(actualCommand, buffer_command);
    if(is_background)
    {
        cmdAfterAmp = strtok_r(actualCommand, "&", &actualCommand);
    }
    else
    {
        cmdAfterAmp = actualCommand;
    }

    while((newtoken = strtok_r(cmdAfterAmp, " \t\n", &cmdAfterAmp)))
    {
        // printf("%s ", newtoken);
        arguments[argCount] = (char*) malloc(256*sizeof(char));
        arguments[argCount] = newtoken;
        argCount++;

    }
    arguments[argCount] = NULL;
    // execvp(arguments[0], arguments);

    if(is_background)
        background();
    else
        foreground();
}

void foreground()
{
    int starttime = time(NULL);
    int pid = fork();

    if(pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        int flag = execvp(arguments[0], arguments);
        printf("%s", arguments[argCount-1]);
        if(flag < 0)
        {
            write(2, "Command not found\n", 19);
            exit(0);
        }
    }
    else if(pid > 0)
    {
        waitpid(pid, NULL, WUNTRACED);
        int endtime = time(NULL);
        totalTime = endtime - starttime;
    }
    else
    {
        perror("Error");
    }
}

void background()
{
    int pid = fork();
    if(pid == 0)
    {
        setpgid(0, 0);
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        int flag = execvp(arguments[0], arguments);
        if(flag < 0)
        {
            write(2, "Command not found\n", 19);
            exit(0);
        }
    }
    else if(pid > 0)
    {
        //dont wait!!
        LL_add(bgp, 0, pid);
        fflush(stdout);
        printf("[%d]\n", pid);
    }
    else
    {
        perror("Error");
    }
}

void wait_child_proc()
{
    int status;
    int pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) 
    {
        if(LL_search(bgp, pid))
        {
            LL_delete(bgp, pid);
            printf ("\nProcess ended successfully: %d\n", pid);
            prompt();
            fflush(stdout);
        }
	}
}
