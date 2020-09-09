#include "headers.h"

int main()
{
    char home[1000];
    getcwd(home, sizeof(home));
    while (1)
    {
        prompt(home);
        char *buffer = NULL;
        size_t bufsize = 0;
        getline(&buffer, &bufsize, stdin);
        int semis = 0;
        char *token[100];
        token[semis] = strtok(buffer, ";");
        while (token[semis] != NULL)
        {
            semis++;
            token[semis] = strtok(NULL, ";");
        }
        token[semis] = NULL;
        for (int j = 0; j < semis; j++)
        {
            char *inputs[100];
            int args = 0;
            inputs[args] = strtok(token[j], " ");
            while (inputs[args] != NULL)
            {
                args++;
                inputs[args] = strtok(NULL, " ");
            }
            inputs[args] = NULL;
            int length = strlen(inputs[args - 1]);
            char temp[length];
            for (int i = 0; i < length - 1; i++)
            {
                temp[i] = inputs[args - 1][i];
            }
            if (semis == 1)
            {
                inputs[args - 1][length - 1] = '\0';
            }
            if (semis > 1)
            {
                inputs[args - 1][length] = '\0';
            }

            if (strcmp(inputs[0], "pwd") == 0)
            {
                pwd();
            }
            if (strcmp(inputs[0], "cd") == 0)
            {
                cd(inputs, args, home);
            }
            if (strcmp(inputs[0], "echo") == 0)
            {
                echo(inputs, args);
            }
            if (strcmp(inputs[0], "ls") == 0)
            {
                ls(inputs, args, home);
            }
            if (strcmp(inputs[0], "pinfo") == 0)
            {
                pinfo(inputs, args, home);
            }
            if (strcmp(inputs[0], "exit") == 0)
            {
                exit(0);
            }
        }
    }
}