#include "headers.h"

void cd(char* npath)
{
    char cur_dir[256];
    getcwd(cur_dir, 256);
    if(npath == NULL)
    {
        chdir(home_dir);
    }
    else if (!strcmp(npath, ".."))
    {
        chdir("..");
    }
    else if ((!strcmp(npath, "~")))
    {
        chdir(home_dir);
    }
    else if(!strcmp(npath, "-"))
    {
        printf("%s\n", prev_dir);
        chdir(prev_dir);
    }
    else
    {
        chdir(npath);
    }
    strcpy(prev_dir, cur_dir);
}