#include "../include/main.h"

// A block is free, but data is too short to fill the entire block, we split it
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

t_block *extendHeapBlockFirst(size_t size, t_heap *h)
{
	if (!h)
		return (NULL);
	t_block *b = (t_block *)h + HEAP_SIZE;
	long sizeUse;

	sizeUse = (void *)b - (void *)h;
	// printf("value of sizeUse = %ld\n", sizeUse);
	if (h && h->type != LARGE)
		if (sizeUse + size + BLOCK_SIZE > h->size)
			return NULL;
	b->data_size = size;
	b->freed = false;
	h->malloc_size += size + BLOCK_SIZE;
	h->free_size -= size + BLOCK_SIZE;
	return b;
}

// no block free, new mmap
t_block *extendHeapBlock(size_t size, t_heap *h)
{
	t_block *b = (t_block *)h + HEAP_SIZE;
	t_block *last = NULL;
	char *tmp;
	long sizeUse;

	while (b->next)
		b = b->next;
	last = b;
	tmp = (char *)last + last->data_size + BLOCK_SIZE;
	b = (t_block *)tmp;
	sizeUse = (long)b - (long)h + HEAP_SIZE;
	if (h && h->type != LARGE)
		if (sizeUse + size + BLOCK_SIZE > h->size)
			return NULL;
	b->prev = last;
	b->next = NULL;
	last->next = b;
	b->data_size = size;
	b->freed = false;
	h->malloc_size += size + BLOCK_SIZE;
	h->free_size -= size + BLOCK_SIZE;
	return b;
}

// looking for a free block
t_block *findBlock(t_heap *h, size_t size)
{
	t_block *b = (t_block *)h + HEAP_SIZE;
	while (b && !(b->freed && b->data_size >= size))
		b = b->next;
	if (b && b->data_size > size + BLOCK_SIZE)
		splitBlock(b, size);
	if (b)
	{
		b->freed = false;
		b->data_size = size;
	}
	return b;
}