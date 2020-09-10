#include "headers.h"
#include "history.h"

void history(char *command, int args, char home[])
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
    //printf("%d\n", commands);
    if (commands < 20)
    {
        //printf("%s\n", command);
        write(fd, command, strlen(command) - 1);
        //write(fd, "\n", sizeof("\n"));
    }
    else
    {
        close(fd);
        fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0777);
        lseek(fd, 0, SEEK_SET);
        int remove = 0;
        for (int i = 0; i < size; i++)
        {
            if (buffer[i] != '\n')
            {
                remove++;
            }
            else
            {
                break;
            }
        }
        // lseek(fd, buffer[remove], size - remove);
        lseek(fd, 0, SEEK_SET);
        write(fd, buffer + remove + 1, strlen(buffer) - remove - 1);
        write(fd, command, strlen(command) - 1);
    }
    write(fd, "\n", 1);
}