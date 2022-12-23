#include "headers.h"

void dfs(char* curr_dir, char* target_dir, int flag_d, int flag_f, char* file_name)
{
    // printf("%s\n", file_name);
    struct dirent** data;
    struct stat dir_stat;
    // printf("target: %s\n", target_dir);
    DIR* dir = opendir(target_dir);
    //printf("hi\n");
    int n;
    if ((n = scandir(target_dir, &data, NULL, alphasort)) < 0) 
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        stat(data[i]->d_name, &dir_stat);
        if(data[i]->d_name[0] == '.')
            continue;
        // printf("name: %s\n", data[i]->d_name);
        // printf("mode: %hu\n\n", dir_stat.st_mode);
        if(data[i]->d_type == DT_DIR)
        {
            char* newdir = (char *)malloc(256*sizeof(char));
            sprintf(newdir, "%s/%s", target_dir, data[i]->d_name);
            // printf("%s\n\n\n", data[i]->d_name);
            if((flag_d) && !file_name)
            {
                printf("%s\n", newdir);
                dfs_flag = 1;
            }
            else if((flag_d && file_name))
            {
                if(!strcmp(data[i]->d_name, file_name))
                {
                    printf("%s\n", newdir);
                    dfs_flag = 1;
                }
            }
            else if((!flag_d && !flag_f && !file_name))
            {
                printf("%s\n", newdir);
                dfs_flag = 1;
            }
            else if((!flag_d && !flag_f && file_name))
            {
                if(!strcmp(data[i]->d_name, file_name))
                {
                    printf("%s\n", newdir);
                    dfs_flag = 1;
                }
            }
            dfs(curr_dir, newdir, flag_d, flag_f, file_name);
            free(newdir);
        }
        else
        {
            // printf("else\n");
            char* newdir = (char *)malloc(256*sizeof(char));
            sprintf(newdir, "%s/%s", target_dir, data[i]->d_name);
            if((flag_f) && !file_name)
            {
                printf("%s\n", newdir);
                dfs_flag = 1;
            }
            else if((flag_f && file_name))
            {
                if(!strcmp(data[i]->d_name, file_name))
                {
                    printf("%s\n", newdir);
                    dfs_flag = 1;
                }
            }
            else if((!flag_d && !flag_f && !file_name))
            {
                printf("%s\n", newdir);
                dfs_flag = 1;
            }
            else if((!flag_d && !flag_f && file_name))
            {
                if(!strcmp(data[i]->d_name, file_name))
                {
                    printf("%s\n", newdir);
                    dfs_flag = 1;
                }
            }
            free(newdir);
        }
    }
    closedir(dir);
}
void discover(char* buffer_command)
{
    dfs_flag = 0;
    // printf("%s\n", buffer_command);
    char* target_dir = (char *)malloc(256*sizeof(char));
    target_dir = NULL;
    int flag_d = 0, flag_f = 0;
    char* file_name = (char *)malloc(256*sizeof(char));
    file_name = NULL;
    char* newtoken = malloc(256*sizeof(char));
    char* rest = malloc(256*sizeof(char));
    rest = buffer_command;
    int flag = 0;
    while((newtoken = (strtok_r(rest, " \n", &rest))) != NULL)
    {
        if (flag == 0)
        {
            flag = 1;
            continue;
        }
        if(!target_dir && newtoken[0] != '-')
        {
            target_dir = newtoken;
        }
        else if(newtoken[0] != '-')
        {
            file_name = newtoken;
        }
        else if(newtoken[0] == '-')
        {
            if(newtoken[1] == 'd')
                flag_d = 1;
            else if (newtoken[1] == 'f')
                flag_f = 1;
        }
    }
    char cur_dir[256];
    cur_dir[0] = '0';
    cur_dir[1] = '\0';

    struct dirent** data;
    struct stat dir_stat;
    int n;
    char *hello2 = (char*)malloc(256*sizeof(char));
    if(target_dir && target_dir[0] != '.')
        sprintf(hello2, "./%s", target_dir);
    else
        sprintf(hello2, "%s", target_dir);
    if(!target_dir)
    {
        hello2[0] = '.';
        hello2[1] = '\0';
    }
    else if(target_dir[0] == '~')
    {
        hello2[0] = '.';
        hello2[1] = '\0';
    }
    else if(!strcmp(target_dir, ".."))
        hello2 = target_dir;

    if(!target_dir && !file_name)
        printf(".\n");

    dfs(cur_dir, hello2, flag_d, flag_f, file_name);
    
}