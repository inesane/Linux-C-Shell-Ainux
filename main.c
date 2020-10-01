#include "headers.h"

void commandrun(char *inputs[], int args, char home[], char rand[])
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
        char prevdir[1000];
        getcwd(prevdir, sizeof(prevdir));
        cd(inputs, args, home, rand);
        strcpy(rand, prevdir);
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
        if (args == 1)
        {
            exit(0);
        }
        else
        {
            fprintf(stderr, "ERROR: Wrong number of arguments\n");
        }
    }
    else if (strcmp(inputs[0], "history") == 0)
    {
        historyprint(inputs, args, home);
    }
    else if (strcmp(inputs[0], "fg") == 0)
    {
        fg(inputs, args);
    }
    else if (strcmp(inputs[0], "bg") == 0)
    {
        bg(inputs, args);
    }
    else if (strcmp(inputs[0], "setenv") == 0)
    {
        set(inputs, args);
    }
    else if (strcmp(inputs[0], "unsetenv") == 0)
    {
        unset(inputs, args);
    }
    else if (strcmp(inputs[0], "jobs") == 0)
    {
        jobs(args);
    }
    else if (strcmp(inputs[0], "kjob") == 0)
    {
        kjob(inputs, args);
    }
    else if (strcmp(inputs[0], "overkill") == 0)
    {
        overkill(inputs, args);
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
    currfg = (int *)malloc(sizeof(int));
    *currfg=-1;
    for(int h=0;h<1000;h++)
    {
        commfg[h]=(char *)malloc(1000*sizeof(char));
    }
    char rand[1000];
    rand[0] = '\0';
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
        ssize_t ctrd;
        ctrd = getline(&buffer, &bufsize, stdin);
        if (ctrd == (unsigned long)-1)
        {
            printf("\n");
            exit(0);
        }
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
            int stdindup = dup(STDIN_FILENO);
            int stdoutdup = dup(STDOUT_FILENO);
            for (int k = 0; k < loops; k++)
            {
                int pipearr[2];
                pipe(pipearr);
                char *inputs[100];
                args = 0;
                inputs[args] = strtok(pipedinputs[k], " \n\t\r");
                while (inputs[args] != NULL)
                {
                    args++;
                    inputs[args] = strtok(NULL, " \n\t\r");
                }
                if (k != loops - 1)
                {
                    dup2(pipearr[1], STDOUT_FILENO);
                    if (pipearr[1] < 0)
                    {
                        fprintf(stderr, "Could not duplicate file descriptor");
                    }
                    close(pipearr[1]);
                }
                else
                {
                    dup2(stdoutdup, STDOUT_FILENO);
                    if (stdoutdup < 0)
                    {
                        fprintf(stderr, "Could not duplicate file descriptor");
                    }
                }
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
                    commandrun(inputs, args, home, rand);
                }
                dup2(pipearr[0], STDIN_FILENO);
                if (pipearr[0] < 0)
                {
                    fprintf(stderr, "Could not duplicate file descriptor");
                }
                close(pipearr[0]);
            }
            dup2(stdindup, STDIN_FILENO);
            if (stdindup < 0)
            {
                fprintf(stderr, "Could not duplicate file descriptor");
            }
            dup2(stdoutdup, STDOUT_FILENO);
            if (stdoutdup < 0)
            {
                fprintf(stderr, "Could not duplicate file descriptor");
            }
        }
    }
}