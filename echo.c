#include"headers.h"
#include"echo.h"
//remove last space? or lite
void echo(char *inputs[], int args)
{
    for(int i=1;i<args;i++)
    {
        printf("%s ", inputs[i]);
    }
    printf("\n");
}