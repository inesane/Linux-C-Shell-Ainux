#include "prompt.h"
#include "headers.h"

void prompt()
{
    struct utsname sysname;
    char *login;
    login = getlogin();
    //errno = 0;
    if (uname(&sysname) != 0)
    {
        perror("ERROR : Getting Path");
    }

    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("ERROR : Path");
    }
    printf("<%s@%s:~%s>", login, sysname.nodename, path);
}
