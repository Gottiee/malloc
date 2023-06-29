#include "../inc/malloc.h"

// Look for prev and next block, if their are free, merge them to be anunique block
t_block *fusion(t_block **b)
{
    t_block tmp;
    if ((*b) && (*b)->prev && (*b)->prev->freed)
    {
        (*b)->prev->next = (*b)->next;
        if ((*b)->next)
            (*b)->next->prev = (*b)->prev;
        (*b)->prev->data_size += BLOCK_SIZE + (*b)->data_size;
        if ((*b) && (*b)->next && (*b)->next->freed)
        {
            (*b)->prev->next = (*b)->next->next;
            if ((*b)->next->next)
                (*b)->next->next->prev = (*b)->prev;
            (*b)->prev->data_size += (*b)->next->data_size + BLOCK_SIZE;
        }
        return (*b)->prev;
    }
    else if ((*b) && (*b)->next && (*b)->next->freed)
    {
        tmp.next = (*b)->next;
        (*b)->next = (*b)->next->next;
        if ((*b)->next)
            (*b)->next->prev = (*b);
        (*b)->data_size += BLOCK_SIZE + tmp.next->data_size;
    }
    return (*b);
}

// return the block
t_block *getBlock(void *ptr)
{
    return ptr - BLOCK_SIZE;
}

// verify addrs to free
bool verifyAddress(t_block *b)
{
    t_group_heap *g = base;
    t_block *tmp;
    t_heap *h;

    if (!b)
        return false;
    for (int i = 0; i < 3; i++)
    {
        h = g->zone[i];
        while (h)
        {
            tmp = (t_block *)((char *)h + HEAP_SIZE);
            while (tmp)
            {
                if (tmp == b)
                    return true;
                tmp = tmp->next;
            }
            h = h->next;
        }
    }
    return false;
}

void verifBase(void)
{
    t_group_heap *g = base;
    int i = -1;

    while (++i < 3)
    {
        if (!g->zone[i])
            continue;
        break;
    }
    if (i == 3)
    {
        munmap(base, GROUP_SIZE);
        base = NULL;
    }
}

void deleteChunks(t_heap *h)
{
    if (!h->prev && !h->next)
        base->zone[h->type] = NULL;
    else if (!h->prev)
        base->zone[h->type] = h->next;
    if (h->prev)
        h->prev->next = h->next;
    if (h->next)
        h->next->prev = h->prev;
    munmap(h, h->size);
    verifBase();
}

t_heap *findHeapChunks(t_block *b)
{
    t_heap *h;

    while (b->prev)
        b = b->prev;
    h = (t_heap *)((char *)b - HEAP_SIZE);
    return h;
}

void verifFree(t_block *b)
{
    t_heap *h;

    h = findHeapChunks(b);
    if (h->malloc_size == 0)
        deleteChunks(h);
}

void updateHeap(t_block *beforeFusion, t_block *b)
{
    t_heap *h;

    b->freed = true;
    h = findHeapChunks(b);
    h->free_size += beforeFusion->data_size + BLOCK_SIZE;
    h->malloc_size -= beforeFusion->data_size + BLOCK_SIZE;
}

void free(void *ptr)
{
    t_block *b;
    t_block beforeFusion;

    if (!base)
    {
        ft_putstr_fd("FREE: No Malloc\n", 2);
        return;
    }
    if (!ptr)
    {
        ft_putstr_fd("FREE: NULL ptr\n", 2);
        return;
    }
    b = getBlock(ptr);
    if (!verifyAddress(b))
    {
        ft_putstr_fd("FREE: invalid address\n", 2);
        return;
    }
    if (b->freed == true)
        return;
    beforeFusion = *b;
    b = fusion(&b);
    updateHeap(&beforeFusion, b);
    verifFree(b);
}