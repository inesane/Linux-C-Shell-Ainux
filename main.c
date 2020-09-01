#include "prompt.h"
#include "pwd.h"
#include "headers.h"

int main()
{
    while (1)
    {
        prompt();
        char *buffer;
        size_t bufsize = 32;
        size_t characters;
        characters = getline(&buffer, &bufsize, stdin);
        if (strcmp(buffer, "pwd\n")==0)
        {
            pwd();
        }
    }
}
