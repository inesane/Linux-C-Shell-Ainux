#include "headers.h"

void prompt()
{
    struct utsname sysname;
    char *login;
    login = getlogin();
    errno = 0;
    if (uname(&sysname) != 0)
    {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("getcwd() error");
    }
    printf("<%s@%s:~%s>", login, sysname.nodename, path);
}
