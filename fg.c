#include "headers.h"
#include "fg.h"

void fg(char *inputs[], int args)
{
    if (args != 2)
    {
        fprintf(stderr, "ERROR: Incorrect number of arguments\n");
    }
    else
    {
        int jobno = atoi(inputs[1]);
        struct Node *copy = ll;
        copy = copy->next;
        struct Node *previous = ll;
        int counter = 0;
        while (copy != NULL)
        {
            counter++;
            previous = copy;
            copy = copy->next;
        }
        if (jobno > counter || jobno <= 0)
        {
            fprintf(stderr, "ERROR: Invalid job number\n");
            return;
        }
        copy = ll->next;
        previous = ll;
        while (copy != NULL)
        {
            if (counter == jobno)
            {
                break;
            }
            counter--;
            previous = copy;
            copy = copy->next;
        }
        int stat;
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, copy->data);
        kill(copy->data, SIGCONT);
        waitpid(copy->data, &stat, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpgrp());
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        if (WIFSTOPPED(stat))
        {
            struct Node *copy2 = ll;
            while (copy2->next != NULL)
            {
                copy2 = copy2->next;
            }
            struct Node *temp2;
            copy2->next = copy;
            copy->next=NULL;
        }
    }
}