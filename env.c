#include "headers.h"
#include "env.h"

void set(char *inputs[], int args)
{
    if (args == 2)
    {
        if (setenv(inputs[1], " ", 1) < 0)
        {
            perror("setenv");
        }
    }
    else if (args == 3)
    {
        if (setenv(inputs[1], inputs[2], 1) < 0)
        {
            perror("setenv");
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Incorrent number of arguments\n");
    }
}

void unset(char *inputs[], int args)
{
    if (args == 2)
    {
        if (unsetenv(inputs[1]) < 0)
        {
            perror("unsetenv");
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Incorrent number of arguments\n");
    }
}