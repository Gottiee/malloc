#include "../include/main.h"

int alignData(int size)
{
    int result;

    if (size % 8 == 0)
        // printf("size is a modulo of 8\n");
        result = size;
    else
        result = ((size - 1) / 8) * 8 + 8;
        // printf("size %d, isnt a modulo of 8 : so the nearest is : %d\n", size, result);
    return result;
}

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
}

t_block *findBlock(t_block *last, size_t size)
{
    t_block *b = base;
    while (b && !(b->freed && b->data_size >= size))
    {
        *last = *b;
        b = b->next;
    }
    if (b && b->data_size > size + BLOCK_SIZE)
        splitBlock(b, size);
    if (b)
        b->freed = false;
    return b;
}

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
        last->next = b;
    return b;
}

void *malloc(size_t size)
{
    t_block *b;
    t_block *last = NULL;

    if (size < 1)
        return (NULL);
    size = alignData(size);
    if (!base)
    {
        write(1, "Fist time called Malloc\n", 24);
        b = extendHeap(last, size);
        base = b;
    }
    else
    {
        write(1, "Malloc already initialised\n", 27);
        b = findBlock(last, size);
        if (!b)
            b = extendHeap(last, size);
    }
    return BLOCK_SHIFT(b);
}
