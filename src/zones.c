#include "../include/main.h"

void initGroup(t_group_heap *g)
{
    g->tiny = NULL;
    g->small = NULL;
    g->large = NULL;
}

size_t getZone(int type, size_t size)
{
    if (type == TINY)
        return TINY_HEAP_ALLOCATION_SIZE;
    if (type == SMALL)
        return SMALL_HEAP_ALLOCATION_SIZE;
    return size; 
}


t_heap *firstMmap(size_t size)
{
    t_group_heap    *g;

    size += GROUP_SIZE;
    g = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (g == MAP_FAILED)
        return NULL;
    initGroup(g);
    base = g;
    return (t_heap *)(g + HEAP_SIZE);
}

void   initHeapData(t_heap *h, int blockType, size_t size, t_heap *last)
{
    h->next = NULL;
    h->type = blockType;
    h->malloc_size = size + BLOCK_SIZE;
    h->free_size = getZone(blockType, size) - h->malloc_size;
    if (last)
    {
        last->next = h;
        h->prev = last;
    }
    else
    {
        base->zone[blockType] = h;
        h->prev = NULL;
    }
}

//mmap a new zone
t_heap *extendHeap(int blockType, size_t size, t_heap *last)
{
    t_heap          *h;
    size_t          sizeMmap;

    sizeMmap = getZone(blockType, size) + HEAP_SIZE;
    if (!base)
        h = firstMmap(sizeMmap);
    else
    {
        h = mmap(NULL, sizeMmap, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (h == MAP_FAILED)
            return NULL;
    }
    initHeapData(h, blockType, size, last);
    return h;
}

int determineType(size_t size)
{
    if (size <= 100)
        return TINY;
    if (size <= 2000)
        return SMALL;
    return LARGE;
}