#ifndef __BACK_H
#define __BACK_H

void handler();
void back();

struct Node
{
    int data;
    struct Node *next;
    char name[30][1024];
};

#endif