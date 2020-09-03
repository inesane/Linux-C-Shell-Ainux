#include "headers.h"
#include "cd.h"
//implement cd ~/...
void cd(char *inputs[], int args, char home[])
{
    if (args > 2)
    {
        perror("ERROR: Too many inputs\n");
    }
    else if (args == 1)
    {
        chdir(home);
        //printf("henlo");
    }
    else if (args == 2)
    {
        //printf("entered");
        if (strcmp(inputs[1], "~") == 0)
        {
            chdir(home);
            //printf("workffs\n");
        }
        else if (strcmp(inputs[1], ".") == 0)
        {
        }
        else if (strcmp(inputs[1], "..") == 0)
        {
            chdir("..");
        }
        else
        {
            int isdir;
            isdir = chdir(inputs[1]);
            if (isdir != 0)
            {
                perror("ERROR: Directory does not exist or permissions not available\n");
            }
        }
    }
}