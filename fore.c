#include "headers.h"
#include "fore.h"

void fore(char *inputs[], int args)
{
    int forkreturn = fork();
    if (forkreturn == 0)
    {
        setpgid(0, 0);
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
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, forkreturn);
        int stat;
        waitpid(forkreturn, &stat, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpgrp());
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        if (WIFSTOPPED(stat))
        {
            *currfg = forkreturn;
            *elements = args;
            for (int k = 0; k < args; k++)
            {
                strcpy(commfg[k], inputs[k]);
            }
            struct Node *copy2 = ll;
            while (copy2->next != NULL)
            {
                copy2 = copy2->next;
            }
            struct Node *temp2;
            temp2 = (struct Node *)malloc(sizeof(struct Node));
            temp2->data = forkreturn;
            for (int k = 0; k < args; k++)
            {
                strcpy(temp2->name[k], inputs[k]);
            }
            temp2->next = NULL;
            copy2->next = temp2;
        }
        *currfg = -1;
        return;
    }
}