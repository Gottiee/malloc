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
#define BLOCK_SIZE sizeof(struct s_block)
#define GROUP_SIZE sizeof(struct s_group_heap)
#define HEAP_SIZE sizeof(struct s_heap)

// a BLOCK of the tinyest malloc malloc(1) = 32 (t_block) + 1;
// TINY can contain 124 BLOCKS of 100 bits
#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
// SMALL can contain 100 BLOCKS of 2000 bits
#define SMALL_HEAP_ALLOCATION_SIZE (50 * getpagesize())
#define TINY 0
#define SMALL 1
#define LARGE 2

extern struct s_group_heap *base;

typedef struct s_heap
{
    struct s_heap *prev;
    struct s_heap *next;
    size_t size;
    size_t free_size;
    size_t malloc_size;
    int type;

} t_heap;

typedef struct s_block
{
    struct s_block *next;
    struct s_block *prev;
    size_t data_size;
    bool freed;
} t_block;

typedef struct s_group_heap
{
    t_heap *zone[3];
} t_group_heap;

t_heap *extendHeap(int blockType, size_t size, t_heap *last);
void *ft_malloc(size_t size);
void printStruct(void);
void ft_free(void *ptr);
int determineType(size_t size);
size_t getZone(int type, size_t size);
t_block *getBlock(void *ptr);

t_block *extendHeapBlock(size_t size, t_heap *h);

#endif