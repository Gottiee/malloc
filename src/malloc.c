#include "../include/main.h"

t_group_heap *base = NULL;

// align data on 8bytes
int alignData(int size)
{
    int result;

    if (size % 8 == 0)
        result = size;
    else
        result = ((size - 1) / 8) * 8 + 8;
    return result;
}

// A block is free, but data is too short to fill the entire block, we split it
void splitBlock(t_block *b, size_t size)
{
    t_block *new;
    t_block tmp;

    new = b + size + BLOCK_SIZE;
    tmp.next = b->next;
    tmp.data_size = b->data_size;
    b->next = new;
    new->next = tmp.next;
    new->freed = true;
    new->data_size = tmp.data_size - size - BLOCK_SIZE;
    new->prev = b;
}

// looking for a free block
t_block *findBlock(t_block **last, size_t size)
{
    // t_block *b = base;
    // while (b && !(b->freed && b->data_size >= size))
    // {
    //     *last = b;
    //     b = b->next;
    // }
    // if (b && b->data_size > size + BLOCK_SIZE)
    //     splitBlock(b, size);
    // if (b)
    // {
    //     b->freed = false;
    //     b->data_size = size;
    // }
    // return b;
}

static rlim_t get_system_limit(void)
{
    struct rlimit rpl;

    if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return (-1);
    return (rpl.rlim_max);
}

void *ft_malloc(size_t size)
{
    // t_block *b;
    // t_block *last = NULL;

    // if (size < 1)
    //     return (NULL);
    // size = alignData(size);
    // if (size > get_system_limit())
    //     return NULL;
    // if (base == NULL)
    // {
    //     b = extendHeap(last, size);
    //     b->prev = NULL;
    //     base = b;
    // }
    // else
    // {
    //     b = findBlock(&last, size);
    //     if (!b)
    //         b = extendHeap(last, size);
    // }
    // return BLOCK_SHIFT(b);

    t_heap          *h;
    t_block         *b = NULL;
    t_heap          *last = NULL;
    t_group_heap    *g;
    int             blockType;

    if (size < 1)
        return (NULL);
    size = alignData(size);
    blockType = determineType(size);
    if (getZone(blockType, size) + HEAP_SIZE + GROUP_SIZE > get_system_limit())
        return NULL;
    if (!base) 
    {
       h = extendHeap(blockType, size, last);
       b = extendHeapBlock(size, h);
    }
    return BLOCK_SHIFT(b);
    
}
