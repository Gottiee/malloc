#ifndef MAIN_H
#define MAIN_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <stdio.h>

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))
#define NULL ((void *)0)

typedef struct s_heap
{
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t          total_size;
    size_t          free_size;
    size_t          block_count;
    
} t_heap;

typedef struct s_block
{
    struct s_block  *next;
    size_t          data_size;
    bool            freed;
} t_block;


void *malloc(size_t size);

#endif