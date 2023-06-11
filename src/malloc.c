#include "../include/main.h"

//align data on 8bytes
int alignData(int size)
{
    int result;

    if (size % 8 == 0)
        result = size;
    else
        result = ((size - 1) / 8) * 8 + 8;
    return result;
}

//A block is free, but data is too short to fill the entire block, we split it
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

//looking for a free block
t_block *findBlock(t_block **last, size_t size)
{
    t_block *b = base;
    while (b && !(b->freed && b->data_size >= size))
    {
        *last = b;
        b = b->next;
    }
    if (b && b->data_size > size + BLOCK_SIZE)
        splitBlock(b, size);
    if (b)
        b->freed = false;
    return b;
}

//no block free, new mmap
t_block *extendHeap(t_block *last, size_t size)
{
    t_block *b;
    b = mmap(NULL, sizeof(t_block) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (b == MAP_FAILED)
        return (NULL);
    b->data_size = size;
    b->freed = false;
    b->next = NULL;
    if (last)
    {
        last->next = b;
        b->prev = last;
    }
    return b;
}

void *ft_malloc(size_t size)
{
    t_block *b;
    t_block *last = NULL;

    if (size < 1)
        return (NULL);
    size = alignData(size);
    if (base == NULL)
    {
        b = extendHeap(last, size);
        b->prev = NULL;
        base = b;
    }
    else
    {
        b = findBlock(&last, size);
        if (!b)
            b = extendHeap(last, size);
    }
    return BLOCK_SHIFT(b);
}
