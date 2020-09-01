#include "pwd.h"
#include "headers.h"

void pwd()
{
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("getcwd() error");
    }
    printf("%s\n", path);
}