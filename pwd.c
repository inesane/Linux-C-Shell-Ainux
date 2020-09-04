#include "pwd.h"
#include "headers.h"

void pwd()
{
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("ERROR : Path");
    }
    printf("%s\n", path);
}