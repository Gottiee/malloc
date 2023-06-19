#include "../include/main.h"

char *fill(bool free, char status[4])
{
    if (free)
    {
        status[0] = 'y';
        status[1] = 'e';
        status[2] = 's';
        status[3] = '\0';
    }
    else
    {
        status[0] = 'n';
        status[1] = 'o';
        status[2] = 'n';
        status[3] = '\0';
    }
    return status;
}

void printStruct()
{
    t_block *tmp;
    char status[4];

    tmp = base;
    printf("\nPrint Struct:\n");
    if (!base)
    {
        printf("Heap unallocated\n");
        return;
    }
    while (tmp)
    {
        fill(tmp->freed, status);
        printf("|size: %ld, free: %s|", tmp->data_size, status);
        if (tmp->freed)
            for (int i = 0; i < tmp->data_size / 2; i++)
                printf(".");
        else
            for (int i = 0; i < tmp->data_size / 2; i++)
                printf("#");
        tmp = tmp->next;
    }
    printf("\n");
}