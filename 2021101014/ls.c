#include "headers.h"

void printDeets(int flag_l, struct dirent* data, struct stat *statbuf)
{
    int colors = 2;
    //printf("%d", flag_l);
    char strings[11];
    if (S_ISSOCK(statbuf->st_mode))
        strings[0] = 's';
    else if (S_ISLNK(statbuf->st_mode))
        strings[0] = 'l';
    else if (S_ISREG(statbuf->st_mode))
    {
        strings[0] = '-';
        if(statbuf->st_mode & S_IXUSR || statbuf->st_mode & S_IXGRP || statbuf->st_mode & S_IXOTH)
        {
            colors = 1;
        }
        else
        {
            colors = 0;
        }
        strings[0] = '-';
    }
    else if (S_ISBLK(statbuf->st_mode))
        strings[0] = 'b';
    else if (S_ISDIR(statbuf->st_mode))
    {
        strings[0] = 'd';
        colors = -1;
    }
    else if (S_ISCHR(statbuf->st_mode))
        strings[0] = 'c';
    else if (S_ISFIFO(statbuf->st_mode))
        strings[0] = 'p';
    else 
        strings[0] = '?';
    if(flag_l)
    {
        strings[1] = (statbuf->st_mode & S_IRUSR) ? 'r' : '-';
        strings[2] = (statbuf->st_mode & S_IWUSR) ? 'w' : '-';
        strings[3] = (statbuf->st_mode & S_IXUSR) ? 'x' : '-';
        strings[4] = (statbuf->st_mode & S_IRGRP) ? 'r' : '-';
        strings[5] = (statbuf->st_mode& S_IWGRP) ? 'w' : '-';
        strings[6] = (statbuf->st_mode & S_IXGRP) ? 'x' : '-';
        strings[7] = (statbuf->st_mode & S_IROTH) ? 'r' : '-';
        strings[8] = (statbuf->st_mode & S_IWOTH) ? 'w' : '-';
        strings[9] = (statbuf->st_mode & S_IXOTH) ? 'x' : '-';
        strings[10] = '\0';
        printf("%s ", strings);
        printf("%3.lu ", statbuf->st_nlink);
        printf("%s ", getpwuid(statbuf->st_uid)->pw_name);
        printf("%s ", getgrgid(statbuf->st_gid)->gr_name);
        printf("%10.ld ", statbuf->st_size);

        char date[21];
        struct tm *time = localtime(&(statbuf->st_mtime));
        strftime(date, 20, "%b %d %H:%M", time);
        printf("%s ", date);
        if(colors == 1)
        {
            printf("\033[1;31m");
            printf("%s\n", data->d_name);
            printf("\e[0m");
        }
        else if(colors == 0)
        {
            printf("\033[1;34m");
            printf("%s\n", data->d_name);
            printf("\e[0m");
        }
        else if(colors == -1)
        {
            printf("\033[1;36m");
            printf("%s\n", data->d_name);
            printf("\e[0m");
        }
        
    }
    else
    {
        if(colors == 1)
        {
            printf("\033[1;31m");
            printf("%s\t", data->d_name);
            printf("\e[0m");
        }
        else if(colors == 0)
        {
            printf("\033[1;34m");
            printf("%s\t", data->d_name);
            printf("\e[0m");
        }
        else if(colors == -1)
        {
            printf("\033[1;36m");
            printf("%s\t", data->d_name);
            printf("\e[0m");
        }
    }
    printf("\e[0m");
}
void printDeetsF(int flag_l, char* data, struct stat *statbuf)
{
    int colors = 2;

    char strings[11];
    char date[21];
    if (S_ISSOCK(statbuf->st_mode))
        strings[0] = 's';
    else if (S_ISLNK(statbuf->st_mode))
        strings[0] = 'l';
    else if (S_ISREG(statbuf->st_mode))
    {
        if(statbuf->st_mode & S_IXUSR || statbuf->st_mode & S_IXGRP || statbuf->st_mode & S_IXOTH)
        {
            colors = 1;
        }
        else
        {
            colors = 0;
        }
        strings[0] = '-';
    }
    else if (S_ISBLK(statbuf->st_mode))
        strings[0] = 'b';
    else if (S_ISDIR(statbuf->st_mode))
    {
        strings[0] = 'd';
        colors = -1;
    }
        
    else if (S_ISCHR(statbuf->st_mode))
        strings[0] = 'c';
    else if (S_ISFIFO(statbuf->st_mode))
        strings[0] = 'p';
    else 
        strings[0] = '?';

    if(flag_l)
    {
        strings[1] = (statbuf->st_mode & S_IRUSR) ? 'r' : '-';
        strings[2] = (statbuf->st_mode & S_IWUSR) ? 'w' : '-';
        strings[3] = (statbuf->st_mode & S_IXUSR) ? 'x' : '-';
        strings[4] = (statbuf->st_mode & S_IRGRP) ? 'r' : '-';
        strings[5] = (statbuf->st_mode& S_IWGRP) ? 'w' : '-';
        strings[6] = (statbuf->st_mode & S_IXGRP) ? 'x' : '-';
        strings[7] = (statbuf->st_mode & S_IROTH) ? 'r' : '-';
        strings[8] = (statbuf->st_mode & S_IWOTH) ? 'w' : '-';
        strings[9] = (statbuf->st_mode & S_IXOTH) ? 'x' : '-';
        strings[10] = '\0';
        printf("%s ", strings);
        printf("%3.lu ", statbuf->st_nlink);
        printf("%s ", getpwuid(statbuf->st_uid)->pw_name);
        printf("%s ", getgrgid(statbuf->st_gid)->gr_name);
        printf("%10.ld ", statbuf->st_size);

        struct tm *time = localtime(&(statbuf->st_mtime));
        strftime(date, 20, "%b %d %H:%M", time);
        printf("%s ", date);
        if(colors == 1)
        {
            printf("\033[1;31m");
            printf("%s\n", data);
            printf("\e[0m");
        }
        else if(colors == 0)
        {
            printf("\033[1;34m");
            printf("%s\n", data);
            printf("\e[0m");
        }
        else if(colors == -1)
        {
            printf("\033[1;36m");
            printf("%s\n", data);
            printf("\e[0m");
        }
    }
    else
    {
        if(colors == 1)
        {
            printf("\033[1;31m");
            printf("%s\t", data);
            printf("\e[0m");
        }
        else if(colors == 0)
        {
            printf("\033[1;34m");
            printf("%s\t", data);
            printf("\e[0m");
        }
        else if(colors == -1)
        {
            printf("\033[1;36m");
            printf("%s\t", data);
            printf("\e[0m");
        }
    }
    printf("\e[0m");
}

int ls(int num, char* buffer_command)
{
    //printf("2%s\n", buffer_command);
    int colors = 2;
    char cur_dir[256];
    getcwd(cur_dir, sizeof(cur_dir));
    int flag = 0;
    int flag_a = 0, flag_l = 0;
    char* rest = malloc(1024*sizeof(char));
    strcpy(rest, buffer_command);
    // printf("3%s\n", rest);
    char* newtoken;
    // rest = *argv;
    // printf("%s", argv);
    // printf("\n");
    int directoryCount = 0;
    while ((newtoken = strtok_r(rest, " \n", &rest)))
    {
        // printf("%s\n", newtoken);
        if (flag == 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            if(newtoken[0] == '-')
            {
                if(newtoken[1] == 'a')
                {
                    flag_a = 1;
                    if(newtoken[2] == 'l')
                        flag_l = 1;
                }
                if(newtoken[1] == 'l')
                {
                    flag_l = 1;
                    if(newtoken[2] == 'a')
                        flag_a = 1;
                }
            }
            else
            {
                directoryCount++;
            }
        }
    }
    // printf("4%s\n", buffer_command);
    //strcpy(rest, buffer_command);
    // printf("%d\n", directoryCount);
    rest = buffer_command;
    char* directory = malloc(256*sizeof(char));
    memset(directory, 0, 256);
    // printf("dire after memset: %s", directory);
    flag = 0;
    if(directoryCount == 0)
    {
        flag = 1;
        directory[0] = '.';
        directory[1] = '\0';
    }
    //printf("5%s", rest);
    //printf("%d\n", flag);
    int count = 0;
    while ((newtoken = strtok_r(rest, " \n", &rest))|| !directoryCount)
    {
    //    printf("new: %s\n", newtoken);
        if (flag == 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            if(newtoken[0] != '-' || !directoryCount)
            {
                // printf("%s\n", newtoken);
                // printf("dir1: %s", directory);
                if(directory[0] != '.')
                    directory = newtoken;
                // printf("newtoken: %s", newtoken);
                // printf("dir: %s", directory);
                struct dirent** data;
                struct stat dir_stat;
                int n;
                char *hello2 = (char*)malloc(256*sizeof(char));
                // hello2 = directory;
                sprintf(hello2, "%s/%s", cur_dir, directory);
                if(directory[0] == '~')
                    hello2 = home_dir;
                else if(!strcmp(directory, ".."))
                    hello2 = directory;
                else if (directory[0] == '.')
                    hello2 = cur_dir;
                //hello2 = cur_dir;
                // printf("%s\n", directory);
                // printf("%s\n", hello2);
                stat(hello2, &dir_stat);
                if(S_ISDIR(dir_stat.st_mode))
                {
                    colors = -1;
                    // printf("colors: %d\n", colors);
                    if(count == directoryCount - 1 && directoryCount > 1)
                        printf("\n");
                    if(directoryCount>1)
                        printf("%s:\n", newtoken);
                    DIR* dir = opendir(hello2);
                    if(dir == NULL)
                    {
                        perror("opendir() error");
                        return 1;
                    }
                    if ((n = scandir(hello2, &data, NULL, alphasort)) < 0) 
                    {
                        perror("Error");
                        return -1;
                    }
                    for (int i = 0; i < n; i++)
                    {
                        stat(data[i]->d_name, &dir_stat);
                        // printf("%s\n", data[i]->d_name);
                        if(flag_a == 1)
                        {
                            printDeets(flag_l, data[i], &dir_stat);
                        }
                        else
                        {
                            if(data[i]->d_name[0] == '.')
                                continue;
                            else
                                printDeets(flag_l, data[i], &dir_stat);
                        }
                        // printf("hi");
                    }
                    closedir(dir);
                    directory[0] = '\0';
                }
                else if (S_ISREG(dir_stat.st_mode))
                {
                    if(count == directoryCount - 1  && directoryCount > 1)
                        printf("\n");
                    hello2 = directory;
                    FILE* file = fopen(hello2, "r");
                    if(file == NULL)
                    {
                        perror("fopen() error");
                        return 1;
                    }
                    printDeetsF(flag_l, hello2, &dir_stat);
                    // printf("\n");
                    fclose(file);
                }
                
            }
        }
        if(!flag_l)
            printf("\n");
        if(!directoryCount) directoryCount++;
        // if(directoryCount)
        // {
        //     printf("\n\n");
        // }
        count++;
    }
    free(rest);
    free(directory);
    return 0;
}