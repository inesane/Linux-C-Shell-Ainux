#include "headers.h"
#include "sig.h"

void ctrlz(int sig)
{
    if (*currfg != -1)
    {
        kill(*currfg, SIGTSTP);
        struct Node *copy = ll;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        struct Node *temp;
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = *currfg;
        for (int k = 0; k < *elements; k++)
        {
            strcpy(temp->name[k], commfg[k]);
        }
        temp->next = NULL;
        copy->next = temp;
        setpgid(*currfg, 0);
        kill(*currfg, sig);
        *currfg = -1;
    }
}

void ctrlc(int sig)
{
    if (*currfg != -1)
    {
        kill(*currfg, sig);
        *currfg = -1;
    }
    else
    {
        return;
    }
}