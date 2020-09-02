#include "prompt.h"
#include "pwd.h"
#include "headers.h"

int main()
{
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
        if (strcmp(inputs, "pwd\n") == 0)
        {
            pwd();
        }
    }
}
