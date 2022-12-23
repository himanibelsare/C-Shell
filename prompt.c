#include "headers.h"

void prompt()
{
    printf("\e[0m");
    struct passwd * username;
    char *hostname = malloc(256* sizeof(char));;
    hostname[255] = '\0';
    gethostname(hostname, 256);
    username = getpwuid(getuid());
    char cur_dir[256];
    getcwd(cur_dir, sizeof(cur_dir));
    char *display_name = malloc(1024*sizeof(char));

    if(!strcmp(cur_dir, home_dir))
    {
        if(totalTime>0)
            sprintf(display_name,"<%s@%s:~took %ds>", username->pw_name, hostname, totalTime);
        else
            sprintf(display_name,"<%s@%s:~>", username->pw_name, hostname);
    }
    else
    {
        if(strlen(cur_dir) > strlen(home_dir))
        {
            int length = strlen(home_dir);
            int flag = 0;
            for(int i = 0; i < length; i++)
            {
                if(cur_dir[i] != home_dir[i])
                    flag = 1;
            }
            if(!flag) //is a subdirectory
            {
                int lenght2 = strlen(cur_dir);
                char newpath[256];
                int j = length;
                for (int i = 0; i < lenght2; i++)
                {
                    newpath[i] = cur_dir[j];
                    j++;
                }
                if(totalTime>0)
                    sprintf(display_name,"<%s@%s:~%stook %ds>", username->pw_name, hostname, newpath, totalTime);
                else
                    sprintf(display_name,"<%s@%s:~%s>", username->pw_name, hostname, newpath);
            }
        }
        else
        {
            if(totalTime>0)
                sprintf(display_name,"<%s@%s:%stook %ds>", username->pw_name, hostname, cur_dir, totalTime);
            else
                sprintf(display_name,"<%s@%s:%s>", username->pw_name, hostname, cur_dir);
        }
    }
    printf("%s", display_name);
    free(hostname);
    free(display_name);
}