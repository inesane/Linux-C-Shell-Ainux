#include "prompt.h"
#include "headers.h"

void prompt(char home[])
{
    struct utsname sysname;
    char *login;
    login = getlogin();
    if (uname(&sysname) != 0)
    {
        perror("ERROR : Getting Path");
    }

    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("ERROR : Path");
    }
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
        printf("<%s@%s:%s>", login, sysname.nodename, temp);
    }
    else
    {
        printf("<%s@%s:%s>", login, sysname.nodename, path);
    }
}
