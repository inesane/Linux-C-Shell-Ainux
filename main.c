#include "headers.h"

int main()
{
    char home[1000];
    getcwd(home, sizeof(home));
    while (1)
    {
        prompt();
        char *buffer = NULL;
        size_t bufsize = 0;
        getline(&buffer, &bufsize, stdin);
        char *inputs[100];
        int args = 0;
        inputs[args] = strtok(buffer, " ");
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
        for (int i = 0; i < length - 1; i++)
        {
            inputs[args - 1][i] = temp[i];
        }
        inputs[args - 1][length - 1] = '\0';
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
        if(strcmp(inputs[0], "pinfo")==0)
        {
            pinfo();
        }
    }
}
