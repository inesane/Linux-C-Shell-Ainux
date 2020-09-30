#include "headers.h"
#include "redirection.h"

int redir(char *inputs[], int args)
{
    int fd;
    for (int i = 0; i < args; i++)
    {
        if (strcmp(inputs[i], ">") == 0)
        {
            i++;
            int fd = open(inputs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("ERROR");
                return 1;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Could not duplicate file descriptor");
                return 1;
            }
            close(fd);
        }
        else if (strcmp(inputs[i], "<") == 0)
        {
            i++;
            int fd = open(inputs[i], O_RDONLY);
            if (fd < 0)
            {
                perror("ERROR");
                return 1;
            }
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("Could not duplicate file descriptor");
                return 1;
            }
            close(fd);
        }
        else if (strcmp(inputs[i], ">>") == 0)
        {
            i++;
            int fd = open(inputs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("ERROR");
                return 1;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Could not duplicate file descriptor");
                return 1;
            }
            close(fd);
        }
    }
}

int redirection(char *inputs[], int args)
{
    for (int i = 0; i < args; i++)
    {
        if (strcmp(inputs[i], ">") == 0 || strcmp(inputs[i], ">>") == 0 || strcmp(inputs[i], "<") == 0)
        {
            if (redir(inputs, args) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}