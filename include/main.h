#ifndef MAIN_H
#define MAIN_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define GROUP_SHIFT(start) ((void *)start + sizeof(t_group_heap))
#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))
#define NULL ((void *)0)
#define BLOCK_SIZE sizeof (struct s_block)

// a BLOCK of the tinyest malloc malloc(1) = 32 (t_block) + 1;
// TINY can contain 124 BLOCKS of 100 bits
#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
// SMALL can contain 100 BLOCKS of 2000 bits
#define SMALL_HEAP_ALLOCATION_SIZE (50 * getpagesize())
#define TINY 0
#define SMALL 1
#define LARGE 2

extern void *base;

typedef struct s_heap
{
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t          free_size;
    int             type;
    
} t_heap;

typedef struct s_block
{
    struct s_block  *next;
    struct s_block  *prev;
    size_t          data_size;
    bool            freed;
} t_block;

typedef struct s_group_heap
{
    t_heap *tiny;
    t_heap *small;
    t_heap *large;
} t_group_heap;

t_block * extendHeap(t_block * last, size_t size);

void    *ft_malloc(size_t size);
void    printStruct(void);
void    ft_free(void *ptr);
int     determineType(size_t size);

#endif