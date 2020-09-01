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
    }
}
