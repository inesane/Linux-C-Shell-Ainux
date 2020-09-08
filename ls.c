#include "headers.h"
#include "ls.h"

int fileperms(char *file_name, char *path)
{
    char perms[10];
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        perms[0] = 'd';
    else
        perms[0] = '-';
    if (stats.st_mode & S_IRUSR)
        perms[1] = 'r';
    else
        perms[1] = '-';
    if (stats.st_mode & S_IWUSR)
        perms[2] = 'w';
    else
        perms[2] = '-';
    if (stats.st_mode & S_IXUSR)
        perms[3] = 'x';
    else
        perms[3] = '-';
    if (stats.st_mode & S_IRGRP)
        perms[4] = 'r';
    else
        perms[4] = '-';
    if (stats.st_mode & S_IWGRP)
        perms[5] = 'w';
    else
        perms[5] = '-';
    if (stats.st_mode & S_IXGRP)
        perms[6] = 'x';
    else
        perms[6] = '-';
    if (stats.st_mode & S_IROTH)
        perms[7] = 'r';
    else
        perms[7] = '-';
    if (stats.st_mode & S_IWOTH)
        perms[8] = 'w';
    else
        perms[8] = '-';
    if (stats.st_mode & S_IXOTH)
        perms[9] = 'x';
    else
        perms[9] = '-';
    printf("%s ", perms);
    printf("%ld ", stats.st_nlink);
    /*uid_t uid = stats.st_uid;
    gid_t gid = stats.st_gid;
    struct passwd *pwd;
    pwd = getpwuid(uid);
    printf("%s", pwd->pw_name);
    struct group *grp;
    grp = getgrgid(gid);
    printf("%s", grp->gr_name);*/
    int size = stats.st_size;
    printf("%d\n", size);
}

void ls(char *inputs[], int args, char home[])
{
    int i, j, invflag, filesanddirs;
    if (args == 1)
    {
        struct dirent **dirlist;
        filesanddirs = scandir(".", &dirlist, NULL, alphasort);
        if (filesanddirs < 0)
            perror("ERROR : ");
        else
        {
            for (i = 0; i < filesanddirs; i++)
            {
                if (dirlist[i]->d_name[0] == '.')
                {
                }
                else
                {
                    printf("%s  ", dirlist[i]->d_name);
                }
            }
            printf("\n");
        }
    }
    else
    {
        int flaga = 0, flagl = 0, flagal = 0, flagla = 0, dirs = 0, isdir = 1;
        char *temps[2000];
        for (i = 1; i < args; i++)
        {
            if (strcmp(inputs[i], "-a") == 0)
            {
                flaga = 1;
            }
            else if (strcmp(inputs[i], "-l") == 0)
            {
                flagl = 1;
            }
            else if (strcmp(inputs[i], "-al") == 0)
            {
                flagal = 1;
            }
            else if (strcmp(inputs[i], "-la") == 0)
            {
                flagla = 1;
            }
            else
            {
                if (inputs[i][0] == '-')
                {
                    printf("ERROR : Invalid Flag\n");
                    invflag = 1;
                }
                struct stat stats;
                stat(inputs[i], &stats);
                if (S_ISDIR(stats.st_mode))
                {
                    temps[dirs] = inputs[i];
                    dirs++;
                }
                else
                {
                    if (inputs[i][0] == '~')
                    {
                        int length = strlen(home) + strlen(inputs[i]);
                        char temp[length];
                        for (j = 0; j < strlen(home); j++)
                        {
                            temp[j] = home[j];
                        }
                        for (int j = strlen(home); j < length; j++)
                        {
                            temp[j] = inputs[i][j - strlen(home) + 1];
                        }
                        isdir = chdir(temp);
                        if (isdir == 0)
                        {
                            temps[dirs] = malloc(4096 * sizeof(char));
                            strcpy(temps[dirs], temp);
                            dirs++;
                        }
                        else
                        {
                            printf("ERROR : Argument is not a directory\n");
                        }
                    }
                    if (isdir != 0)
                    {
                        printf("ERROR : Argument is not a directory");
                    }
                }
            }
        }
        if ((flaga == 1 && flagl == 1) || flagal == 1 || flagla == 1)
        {
            if (dirs == 0)
            {
                struct dirent **dirlist;
                filesanddirs = scandir(".", &dirlist, NULL, alphasort);
                int total = 0;
                if (filesanddirs < 0)
                    perror("ERROR : ");
                else
                {
                    for (j = 0; j < filesanddirs; j++)
                    {

                        char path[2000];
                        sprintf(path, "%s/%s", ".", dirlist[j]->d_name);
                        struct stat stats;
                        stat(path, &stats);
                        total += stats.st_blocks;
                    }
                }
                printf("total %d\n", total / 2);
                total = 0;
                for (j = 0; j < filesanddirs; j++)
                {
                    char path[2000];
                    sprintf(path, "%s/%s", ".", dirlist[j]->d_name);
                    fileperms(".", path);
                }
            }
            else
            {
                for (i = 0; i < dirs; i++)
                {
                    printf("%s:\n", temps[i]);
                    struct dirent **dirlist;
                    filesanddirs = scandir(temps[i], &dirlist, NULL, alphasort);
                    int total = 0;
                    if (filesanddirs < 0)
                        perror("ERROR : ");
                    else
                    {
                        for (j = 0; j < filesanddirs; j++)
                        {

                            char path[2000];
                            sprintf(path, "%s/%s", temps[i], dirlist[j]->d_name);
                            struct stat stats;
                            stat(path, &stats);
                            total += stats.st_blocks;
                        }
                    }
                    printf("total %d\n", total / 2);
                    total = 0;
                    for (j = 0; j < filesanddirs; j++)
                    {
                        char path[2000];
                        sprintf(path, "%s/%s", temps[i], dirlist[j]->d_name);
                        fileperms(temps[i], path);
                    }
                }
            }
        }
        else if (flaga == 1)
        {
            if (dirs == 0)
            {
                struct dirent **dirlist;
                filesanddirs = scandir(".", &dirlist, NULL, alphasort);
                if (filesanddirs < 0)
                    perror("ERROR : ");
                else
                {
                    for (i = 0; i < filesanddirs; i++)
                    {
                        printf("%s  ", dirlist[i]->d_name);
                    }
                    printf("\n");
                }
            }
            else
            {
                for (i = 0; i < dirs; i++)
                {
                    printf("%s:\n", temps[i]);
                    struct dirent **dirlist;
                    filesanddirs = scandir(temps[i], &dirlist, NULL, alphasort);
                    if (filesanddirs < 0)
                        perror("ERROR : ");
                    else
                    {
                        for (j = 0; j < filesanddirs; j++)
                        {
                            printf("%s  ", dirlist[j]->d_name);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
        }
        else if (flagl == 1)
        {
            if (dirs == 0)
            {
                struct dirent **dirlist;
                filesanddirs = scandir(".", &dirlist, NULL, alphasort);
                int total = 0;
                if (filesanddirs < 0)
                    perror("ERROR : ");
                else
                {
                    for (j = 0; j < filesanddirs; j++)
                    {
                        if (dirlist[j]->d_name[0] == '.')
                        {
                        }
                        else
                        {
                            char path[2000];
                            sprintf(path, "%s/%s", ".", dirlist[j]->d_name);
                            struct stat stats;
                            stat(path, &stats);
                            total += stats.st_blocks;
                        }
                    }
                }
                printf("total %d\n", total / 2);
                total = 0;
                for (j = 0; j < filesanddirs; j++)
                {
                    if (dirlist[j]->d_name[0] == '.')
                    {
                    }
                    else
                    {
                        char path[2000];
                        sprintf(path, "%s/%s", ".", dirlist[j]->d_name);
                        fileperms(".", path);
                    }
                }
            }
            else
            {
                for (i = 0; i < dirs; i++)
                {
                    printf("%s:\n", temps[i]);
                    struct dirent **dirlist;
                    filesanddirs = scandir(temps[i], &dirlist, NULL, alphasort);
                    int total = 0;
                    if (filesanddirs < 0)
                        perror("ERROR : ");
                    else
                    {
                        for (j = 0; j < filesanddirs; j++)
                        {
                            if (dirlist[j]->d_name[0] == '.')
                            {
                            }
                            else
                            {
                                char path[2000];
                                sprintf(path, "%s/%s", temps[i], dirlist[j]->d_name);
                                struct stat stats;
                                stat(path, &stats);
                                total += stats.st_blocks;
                            }
                        }
                    }
                    printf("total %d\n", total / 2);
                    total = 0;
                    for (j = 0; j < filesanddirs; j++)
                    {
                        if (dirlist[j]->d_name[0] == '.')
                        {
                        }
                        else
                        {
                            char path[2000];
                            sprintf(path, "%s/%s", temps[i], dirlist[j]->d_name);
                            fileperms(temps[i], path);
                        }
                    }
                }
            }
        }
    }
}