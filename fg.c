#include "headers.h"


int fg(char* buffer_command) {

    strtok(buffer_command, " ");
    int pid = atoi(strtok(NULL, " "));
    printf("%d\n", pid);
    setpgid(pid, getpgid(0));

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    
    tcsetpgrp(0, pid);

    int status = kill(pid, SIGCONT);
    if(status < 0)
        printf("Error\n");

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);

    if (WIFSTOPPED(status))
    {
        return 0;
    }

    if(WIFEXITED(status))
        return pid;
    else
        return -pid;
}