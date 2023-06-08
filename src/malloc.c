#include "../include/main.h"

void *malloc(size_t size)
{
    t_block *b;
    b = mmap(NULL, sizeof(t_block) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (b == MAP_FAILED)
        return (NULL);
    b->data_size = size;
    return b;
}