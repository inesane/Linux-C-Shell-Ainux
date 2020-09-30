#include "headers.h"
#include "fore.h"

void fore(char *inputs[], int args)
{
    int forkreturn = fork();
    if (forkreturn == 0)
    {
        char *argv[args + 1];
        for (int i = 0; i < args; i++)
        {
            argv[i] = malloc(1000 * sizeof(char));
            for (int j = 0; j < 1000; j++)
            {
                argv[i][j] = '\0';
            }
            strcpy(argv[i], inputs[i]);
        }
        argv[args] = NULL;
        if (execvp(inputs[0], argv) < 0)
        {
            fprintf(stderr, "ERROR : Execvp Failed\n");
            _exit(EXIT_FAILURE);
        }
        _exit(0);
    }
    else if (forkreturn < 0)
    {
        fprintf(stderr, "ERROR : Fork Failed\n");
        exit(0);
    }
    else
    {
        waitpid(forkreturn, NULL, 0);
        return;
    }
}