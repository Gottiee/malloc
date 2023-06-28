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

void print(t_block *b, int *color, int div)
{
    char status[4];
    char *color_tab[] = {ARRIERE_PLAN_JAUNE, ARRIERE_PLAN_BLEU, ARRIERE_PLAN_MAGENTA};
    if (div == 0)
        div = 2;

    printf("%s", color_tab[*color % 3]);
    (*color)++;
    while (b)
    {
        fill(b->freed, status);
        printf("|size: %ld, ", b->data_size);

        if (b->freed)
        {
            printf(VERT "free: %s", status);
            printf(BLANC "|" VERT);
            for (int i = 0; i < b->data_size / div; i++)
                printf(".");
            printf(BLANC);
        }
        else
        {
            printf(ROUGE "free: %s", status);
            printf(BLANC "|" ROUGE);
            for (int i = 0; i < b->data_size / div; i++)
                printf("#");
            printf(BLANC);
        }
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
    printf(JAUNE "\n---Print Struct:---\n" RESET);
    if (!base)
    {
        printf(ROUGE "\nHeap unallocated\n" RESET);
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        t_heap *h = g->zone[i];
        t_heap *tmp;
        if (h)
            printf(VERT "ZONE : %s\n" RESET, phrase[i]);
        if (!h)
            continue;
        tmp = h;
        chunks = 0;
        size =0;
        free_size = 0;
        malloc_size = 0;
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
            print((t_block *)((char *)h + HEAP_SIZE), &color, i * 20);
            h = h->next;
        }
        printf("\n\n");
    }
}