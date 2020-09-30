#include "headers.h"
#include "back.h"

void handler(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    struct Node *copy = ll;
    copy = copy->next;
    struct Node *previous = ll;
    while (copy != NULL)
    {
        if (copy->data == pid)
        {
            break;
        }
        previous = copy;
        copy = copy->next;
    }
    if (copy != NULL)
    {
        fprintf(stderr, "%s with pid %d exited with exit code %d\n", copy->name, copy->data, WEXITSTATUS(status));
        previous->next = copy->next;
    }
}

void back(char *inputs[], int args)
{
    int tempss = args;
    char *argv[args];
    for (int i = 0; i < tempss - 1; i++)
    {
        argv[i] = malloc(1000 * sizeof(char));
        for (int k = 0; k <= strlen(inputs[i]); k++)
        {
            argv[i][k] = inputs[i][k];
        }
    }
    argv[tempss - 1] = NULL;
    int forkreturn = fork();
    if (forkreturn == 0)
    {
        setpgid(0, 0);
        if (execvp(argv[0], argv) < 0)
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
        setpgid(forkreturn, 0);
        tcsetpgrp(STDIN_FILENO, getpid());
        struct Node *copy = ll;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        struct Node *temp;
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = forkreturn;
        strcpy(temp->name, inputs[0]);
        temp->next = NULL;
        copy->next = temp;
        signal(SIGCHLD, handler);
        return;
    }
}