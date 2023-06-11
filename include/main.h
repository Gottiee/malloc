#ifndef MAIN_H
#define MAIN_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))
#define NULL ((void *)0)
#define BLOCK_SIZE sizeof (struct s_block)

extern void *base;

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
    struct s_block  *prev;
    size_t          data_size;
    bool            freed;
} t_block;


t_block * extendHeap(t_block * last, size_t size);

void    *ft_malloc(size_t size);
void    printStruct(void);
void    ft_free(void *ptr);

#endif