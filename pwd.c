#include "headers.h"

void pwd()
{
    char cur_dir[256];
    getcwd(cur_dir, sizeof(cur_dir));
    write(1, cur_dir, strlen(cur_dir));
    write(1, "\n", 1);
    return;
}