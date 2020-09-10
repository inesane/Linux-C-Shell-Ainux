#include "headers.h"
#include "historyprint.h"

void historyprint(char *inputs[], int args, char home[])
{
    char file[1000];
    strcpy(file, home);
    strcat(file, "/hist.txt");
    int fd = open(file, O_RDWR | O_CREAT, 0777);
    char buffer[1000];
    int size = read(fd, buffer, 1000);
    buffer[size] = '\0';
    int commands = 0;
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            commands++;
        }
    }
    int lines;
    if (args == 1)
    {
        lines = 10;
    }
    else if (args == 2)
    {
        lines = atoi(inputs[1]);
    }
    else
    {
        printf("ERROR : Invalid Number of Arguments\n");
        return;
    }
    if (lines <= commands)
    {
        int diff = commands - lines;
        int index = 0;
        while (diff > 0)
        {
            if (buffer[index] == '\n')
            {
                diff--;
            }
            index++;
        }
        printf("%s\n", buffer + index);
    }
    else
    {
        printf("%s\n", buffer);
    }
}