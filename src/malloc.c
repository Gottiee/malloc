#include "../include/malloc.h"

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

static rlim_t get_system_limit(void)
{
    struct rlimit rpl;

    if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return (-1);
    return (rpl.rlim_max);
}

void doExtendHeap(t_heap **h, int blockType, size_t size, t_heap **last, t_block **b)
{
    *h = extendHeap(blockType, size, *last);
    *b = extendHeapBlockFirst(size, *h);
}

void *malloc(size_t size)
{
    t_heap *h;
    t_block *b = NULL;
    t_heap *last = NULL;
    int blockType;

    if (size < 1)
        return (NULL);
    size = alignData(size);
    blockType = determineType(size);
    if (getZone(blockType, size) + HEAP_SIZE + GROUP_SIZE > get_system_limit())
        return NULL;
    if (!base)
        doExtendHeap(&h, blockType, size, &last, &b);
    else
    {
        h = findZone(&last, size, blockType);
        if (!h)
            doExtendHeap(&h, blockType, size, &last, &b);
        else
        {
            b = findBlock(h, size);
            if (b)
                return BLOCK_SHIFT(b);
            b = extendHeapBlock(size, h);
            if (b)
                return BLOCK_SHIFT(b);
            doExtendHeap(&h, blockType, size, &last, &b);
        }
    }
    return BLOCK_SHIFT(b);
}
