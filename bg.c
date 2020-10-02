#include "headers.h"
#include "bg.h"

void bg(char *inputs[], int args)
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
        int checker = 1;
        while (copy != NULL)
        {
            if (checker == jobno)
            {
                break;
            }
            checker++;
            previous = copy;
            copy = copy->next;
        }
        kill(copy->data, SIGCONT);
    }
}