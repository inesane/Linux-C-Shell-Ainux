#include "headers.h"
#include "overkill.h"
#include "kjob.h"

void overkill(char *inputs[], int args)
{
    struct Node *copy = ll;
    copy = copy->next;
    struct Node *previous = ll;
    while (copy != NULL)
    {
        kill(copy->data, 9);
        previous = copy;
        copy = copy->next;
    }
}