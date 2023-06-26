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

void print(t_block *b, int *color)
{
    char status[4];
    char *color_tab[] = {ARRIERE_PLAN_VERT, ARRIERE_PLAN_JAUNE, ARRIERE_PLAN_BLEU, ARRIERE_PLAN_MAGENTA, ARRIERE_PLAN_CYAN, ARRIERE_PLAN_ROUGE};

    printf("%s", color_tab[*color % 6]);
    (*color)++;
    while (b)
    {
        fill(b->freed, status);
        printf("|size: %ld, free: %s|", b->data_size, status);
        if (b->freed)
            for (int i = 0; i < b->data_size / 10; i++)
                printf(".");
        else
            for (int i = 0; i < b->data_size / 10; i++)
                printf("#");
        b = b->next;
    }
    printf(RESET);
}

void printStruct()
{
    t_group_heap *g;
    char *phrase[] = {"TINY", "SMALL", "LARGE"};
    static int color = 0;
    size_t size = 0, free_size = 0, malloc_size = 0, chunks = 0;

    g = base;
    printf(JAUNE "\n----------Print Struct:----------\n" RESET);
    if (!base)
    {
        printf("Heap unallocated\n");
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        t_heap *h = g->zone[i];
        t_heap *tmp;
        printf(VERT "ZONE : %s\n" RESET, phrase[i]);
        if (!h)
        {
            printf("\tZone unallocated\n\n");
            continue;
        }
        tmp = h;
        while (tmp)
        {
            size += tmp->size;
            free_size += tmp->free_size;
            malloc_size += tmp->malloc_size;
            tmp = tmp->next;
            chunks++;
        }
        printf("\tDATA:\n");
        printf("\t\tSize : %ld\n\t\tFree size: %ld\n\t\tMalloc size: %ld\n\t\tChunks: %ld\n", size, free_size, malloc_size, chunks);
        while (h)
        {
            print((t_block *)h + HEAP_SIZE, &color);
            h = h->next;
        }
        printf("\n\n");
    }
}