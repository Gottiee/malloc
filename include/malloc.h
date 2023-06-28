#ifndef MAIN_H
#define MAIN_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <unistd.h>

#define GROUP_SHIFT(start) ((void *)start + sizeof(t_group_heap))
#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))
#define NULL ((void *)0)
#define BLOCK_SIZE sizeof(struct s_block)
#define GROUP_SIZE sizeof(struct s_group_heap)
#define HEAP_SIZE sizeof(struct s_heap)
#define NOIR "\033[30m"
#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BLANC "\033[37m"
#define ARRIERE_PLAN_ROUGE "\033[41m"
#define ARRIERE_PLAN_VERT "\033[42m"
#define ARRIERE_PLAN_JAUNE "\033[43m"
#define ARRIERE_PLAN_BLEU "\033[44m"
#define ARRIERE_PLAN_MAGENTA "\033[45m"
#define ARRIERE_PLAN_CYAN "\033[46m"
#define RESET "\033[0m"

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

/*--- malloc.c ---*/
void *malloc(size_t size);
int alignData(int size);

/*--- utils.c ---*/
void printStruct(void);
void ft_putnbr_fd(int n, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putlong_fd(long int n, int fd);

/*--- free.c ---*/
void free(void *ptr);
t_block *getBlock(void *ptr);
t_heap *findHeapChunks(t_block *b);
bool verifyAddress(t_block *b);
t_block *fusion(t_block **b);
void updateHeap(t_block *beforeFusion, t_block *b);

/*--- zones.c ---*/
int determineType(size_t size);
size_t getZone(int type, size_t size);
t_heap *findZone(t_heap **last, size_t size, int type);
t_heap *extendHeap(int blockType, size_t size, t_heap *last);
t_block *extendHeapBlockFirst(size_t size, t_heap *h);

/*--- block.c ---*/
t_block *extendHeapBlock(size_t size, t_heap *h);
t_block *findBlock(t_heap *h, size_t size);
void splitBlock(t_block *b, size_t size);

/*--- realloc.c ---*/
void *realloc(void *ptr, size_t size);

#endif