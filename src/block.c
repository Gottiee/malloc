#include "../include/main.h"

// no block free, new mmap
t_block *extendHeapBlock(size_t size, t_heap *h)
{
	// b->data_size = size;
	// b->freed = false;
	// b->next = NULL;
	// if (last)
	// {
	//     last->next = b;
	//     b->prev = last;
	// }

	t_block *b = (t_block *)h + HEAP_SIZE;
	t_block *last = NULL;
	long sizeUse;

	while (b->next)
	{
		last = b;
		b = b->next;
	}
	sizeUse = (void *)b - (void *)h;
	// printf("value of sizeUse = %ld\n", sizeUse);
	if (sizeUse + size + BLOCK_SIZE > h->size)
		return NULL;
	if (last)
		b->prev = last;
	b->data_size = size;
	b->freed = false;
	h->malloc_size += size + BLOCK_SIZE;
	h->free_size -= size + BLOCK_SIZE;
	return b;
}