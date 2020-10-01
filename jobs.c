#include "headers.h"
#include "jobs.h"

void jobs(int args, char home[])
{
    if (args > 1)
    {
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
    }
    else
    {
        struct Node *copy = ll;
        copy = copy->next;
        struct Node *previous = ll;
        int i = 1;
        while (copy != NULL)
        {
            int j = 0;
            int pid = copy->data;
            int pidtemp = pid;
            char procloc[1000] = "/proc/";
            int counter = 0;
            char temp[100];
            while (pid > 0)
            {
                temp[counter] = (pid % 10) + '0';
                pid = pid / 10;
                counter++;
            }
            for (int i = counter - 1; i >= 0; i--)
            {
                procloc[6 + i] = temp[counter - i - 1];
            }
            char open[1000];
            strcpy(open, "");
            strcat(open, procloc);
            char exe[10] = "/exe";
            strcat(procloc, exe);
            char stat[10] = "/stat";
            strcat(open, stat);
            char proc[52][1000];
            char runstatus[1000];
            FILE *fp = fopen(open, "r");
            if (fp == NULL)
            {
                perror("ERROR ");
            }
            else
            {
                printf("[%d] ", i);
                fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", proc[0], proc[1], proc[2], proc[3], proc[4], proc[5], proc[6], proc[7], proc[8], proc[9], proc[10], proc[11], proc[12], proc[13], proc[14], proc[15], proc[16], proc[17], proc[18], proc[19], proc[20], proc[21], proc[22], proc[23], proc[24], proc[25], proc[26], proc[27], proc[28], proc[29], proc[30], proc[31], proc[32], proc[33], proc[34], proc[35], proc[36], proc[37], proc[38], proc[39], proc[40], proc[41], proc[42], proc[43], proc[44], proc[45], proc[46], proc[47], proc[48], proc[49], proc[50], proc[51]);
                fclose(fp);
                strcpy(runstatus, proc[2]);
                if (strcmp(runstatus, "T") == 0)
                {
                    printf("Stopped ");
                }
                else
                {
                    printf("Running ");
                }
            }
            while (copy->name[j + 1][0] != '\0')
            {
                printf("%s ", copy->name[j]);
                j++;
            }
            printf("[%d]\n", copy->data);
            previous = copy;
            copy = copy->next;
            i++;
        }
    }
}