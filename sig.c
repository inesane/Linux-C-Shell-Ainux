#include "headers.h"
#include "sig.h"

void ctrlz(int sig)
{
    if(*currfg!=-1)
    {
        kill(*currfg, SIGTSTP);
    }
}