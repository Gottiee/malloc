#include "../inc/malloc.h"

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
    ft_putstr_fd("", 1);

    char status[4];
    char *color_tab[] = {ARRIERE_PLAN_JAUNE, ARRIERE_PLAN_BLEU, ARRIERE_PLAN_MAGENTA};
    if (div == 0)
        div = 2;

    ft_putstr_fd(color_tab[*color % 3], 1);
    (*color)++;
    while (b)
    {
        fill(b->freed, status);
        ft_putstr_fd("|size: ", 1);
        ft_putlong_fd(b->data_size, 1);
        ft_putstr_fd(", ", 1);
        if (b->freed)
        {
            ft_putstr_fd(VERT "free: ", 1);
            ft_putstr_fd("status", 1);
            ft_putstr_fd(BLANC "|" VERT, 1);
            for (size_t i = 0; i < b->data_size / div; i++)
                ft_putstr_fd(".", 1);
            ft_putstr_fd(BLANC, 1);
        }
        else
        {
            ft_putstr_fd(ROUGE "free: ", 1);
            ft_putstr_fd("status", 1);
            ft_putstr_fd(BLANC "|" ROUGE, 1);
            for (size_t i = 0; i < b->data_size / div; i++)
                ft_putstr_fd("#", 1);
            ft_putstr_fd(BLANC, 1);
        }
        b = b->next;
    }
    ft_putstr_fd(RESET, 1);
}

void show_alloc_mem_ex()
{
    t_group_heap *g;
    char *phrase[] = {"TINY", "SMALL", "LARGE"};
    static int color = 0;
    size_t size = 0, free_size = 0, malloc_size = 0, chunks = 0;

    g = base;
    ft_putstr_fd(JAUNE "\n---Print Struct:---\n" RESET, 1);
    if (!base)
    {
        ft_putstr_fd(ROUGE "Heap unallocated\n" RESET, 1);
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        t_heap *h = g->zone[i];
        t_heap *tmp;
        if (h)
        {
            ft_putstr_fd(VERT "ZONE : ", 1);
            ft_putstr_fd(phrase[i], 1);
            ft_putstr_fd("\n" RESET, 1);
        }
        if (!h)
            continue;
        tmp = h;
        chunks = 0;
        size = 0;
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
        ft_putstr_fd("\tDATA:\n", 1);
        ft_putstr_fd("\t\tSize : ", 1);
        ft_putlong_fd(size, 1);
        ft_putstr_fd("\n\t\tFree size: ", 1);
        ft_putlong_fd(free_size, 1);
        ft_putstr_fd("\n\t\tMalloc size: ", 1);
        ft_putlong_fd(malloc_size, 1);
        ft_putstr_fd("\n\t\tChunks: ", 1);
        ft_putlong_fd(chunks, 1);
        ft_putstr_fd("\n", 1);
        while (h)
        {
            print((t_block *)((char *)h + HEAP_SIZE), &color, i * 20);
            h = h->next;
        }
        ft_putstr_fd("\n\n", 1);
    }
}