#include "headers.h"
#include "cd.h"

void cd(char *inputs[], int args, char home[], char prevdir[])
{
    if (args > 2)
    {
        perror("ERROR: Too many inputs\n");
    }
    else if (args == 1)
    {
        chdir(home);
    }
    else if (args == 2)
    {
        if (strcmp(inputs[1], "~") == 0)
        {
            chdir(home);
        }
        else if (strcmp(inputs[1], ".") == 0)
        {
        }
        else if (strcmp(inputs[1], "..") == 0)
        {
            chdir("..");
        }
        else if (strcmp(inputs[1], "-") == 0)
        {
            char path[PATH_MAX];
            getcwd(path, sizeof(path));
            int count = 0;
            for (int i = 0; i < strlen(home); i++)
            {
                if (home[i] == path[i])
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            if (count == strlen(home))
            {
                int pathlength = strlen(path);
                int homelength = strlen(home);
                int i;
                char temp[pathlength - homelength + 1];
                temp[0] = '~';
                for (i = 1; i < pathlength - homelength + 1; i++)
                {
                    temp[i] = path[homelength + i - 1];
                }
                printf("%s\n", temp);
            }
            else
            {
                printf("%s\n", path);
            }
            if (prevdir[0] == '\0')
            {
            }
            else
            {
                chdir(prevdir);
            }
        }
        else
        {
            int i = 0, isdir;
            if (inputs[1][0] == '~')
            {
                int length = strlen(home) + strlen(inputs[1]);
                char temp[length];
                for (i = 0; i < strlen(home); i++)
                {
                    temp[i] = home[i];
                }
                for (int i = strlen(home); i < length; i++)
                {
                    temp[i] = inputs[1][i - strlen(home) + 1];
                }
                isdir = chdir(temp);
            }
            else
            {
                isdir = chdir(inputs[1]);
            }
            if (isdir != 0)
            {
                perror("ERROR ");
            }
        }
    }
}