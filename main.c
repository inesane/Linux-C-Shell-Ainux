#include "headers.h"

void commandrun(char *inputs[], int args, char home[])
{
    if (inputs[0] == NULL)
    {
    }
    else if (strcmp(inputs[0], "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(inputs[0], "cd") == 0)
    {
        cd(inputs, args, home);
    }
    else if (strcmp(inputs[0], "echo") == 0)
    {
        echo(inputs, args);
    }
    else if (strcmp(inputs[0], "ls") == 0)
    {
        ls(inputs, args, home);
    }
    else if (strcmp(inputs[0], "pinfo") == 0)
    {
        pinfo(inputs, args, home);
    }
    else if (strcmp(inputs[0], "quit") == 0)
    {
        exit(0);
    }
    else if (strcmp(inputs[0], "history") == 0)
    {
        historyprint(inputs, args, home);
    }
    else
    {
        if (strcmp(inputs[args - 1], "&") == 0)
        {
            back(inputs, args);
        }
        else
        {
            fore(inputs, args);
        }
    }
}

int main()
{
    ll = (struct Node *)malloc(sizeof(struct Node));
    ll->data = -1;
    ll->next = NULL;
    char home[1000];
    getcwd(home, sizeof(home));
    while (1)
    {
        prompt(home);
        char *buffer = malloc(sizeof(char) * 4096);
        size_t bufsize = 0;
        getline(&buffer, &bufsize, stdin);
        char fullline[strlen(buffer)];
        strcpy(fullline, buffer);
        buffer[strlen(buffer) - 1] = '\0';
        char *token[100];
        int args;
        token[0] = strtok(buffer, ";");
        int ii = 0;
        while (token[ii] != NULL)
        {
            ii++;
            token[ii] = strtok(NULL, ";");
        }
        for (int j = 0; j < ii; j++)
        {
            int l, argstemp2;
            char *inputstemp2[100];
            int loops = 1;
            for (l = 0; l < strlen(token[j]); l++)
            {
                if (token[j][l] == '|')
                    loops++;
            }
            int pipedargs = 0;
            char *pipedinputs[100];
            pipedinputs[pipedargs] = strtok(token[j], "|");
            while (pipedinputs[pipedargs] != NULL)
            {
                pipedargs++;
                pipedinputs[pipedargs] = strtok(NULL, "|");
            }
            if ((pipedinputs[0] != NULL) && (j == 0))
            {
                history(fullline, args, home);
            }
            for (int k = 0; k < loops; k++)
            {
                char *inputs[100];
                args = 0;
                inputs[args] = strtok(pipedinputs[k], " \n\t\r");
                while (inputs[args] != NULL)
                {
                    args++;
                    inputs[args] = strtok(NULL, " \n\t\r");
                }
                int stdinCopy = dup(STDIN_FILENO);
                int stdoutCopy = dup(STDOUT_FILENO);
                if (redirection(inputs, args) == 0)
                {
                    int argstemp = args;
                    int w, argsactual = 0;
                    char *inputstemp[100];
                    for (w = 0; w < argstemp; w++)
                    {
                        if (strcmp(inputs[w], ">") == 0 || strcmp(inputs[w], ">>") == 0 || strcmp(inputs[w], "<") == 0)
                        {
                            args = args - 2;
                            w++;
                        }
                        else
                        {
                            inputstemp[argsactual] = inputs[w];
                            argsactual++;
                        }
                    }
                    for (w = 0; w < args; w++)
                    {
                        inputs[w] = inputstemp[w];
                    }
                    commandrun(inputs, args, home);
                }
                dup2(stdinCopy, STDIN_FILENO);
                dup2(stdoutCopy, STDOUT_FILENO);
            }
        }
    }
}