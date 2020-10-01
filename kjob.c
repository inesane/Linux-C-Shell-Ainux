#include "headers.h"
#include "kjob.h"
#include "back.h"

void kjob(char *inputs[], int args)
{
    if (args != 3)
    {
        fprintf(stderr, "ERROR: Invalid number of arguments");
    }
    else
    {
        int flag = 0;
        int jobno = atoi(inputs[1]);
        int signo = atoi(inputs[2]);
        struct Node *copy = ll;
        copy = copy->next;
        struct Node *previous = ll;
        for (int i = 0; i < jobno; i++)
        {
            if (copy == NULL)
            {
                fprintf(stderr, "ERROR: Job number does not exist\n");
                flag = 1;
                break;
            }
            previous = copy;
            copy = copy->next;
            printf("%d\n", previous->data);
        }
        if (flag == 0)
            kill(previous->data, signo);
    }
}