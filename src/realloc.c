#include "../include/malloc.h"

void increaseHeap(t_block *b, size_t size)
{
	t_heap *h;

	h = findHeapChunks(b);
	h->free_size -= size + BLOCK_SIZE;
	h->malloc_size += size + BLOCK_SIZE;
	b->data_size = size;
}

void copyBlock(t_block *src, t_block *dst)
{
	char *sData = BLOCK_SHIFT(src);
	char *dData = BLOCK_SHIFT(dst);

	for (size_t i = 0; i < src->data_size; i++)
		dData[i] = sData[i];
}

void reduceHeap(t_block *b, size_t size)
{
	t_heap *h;

	h = findHeapChunks(b);
	h->free_size += b->data_size - size;
	h->malloc_size -= b->data_size - size;
	b->data_size = size;
}

void updateHeapRea(t_block *beforeFusion, t_block *b)
{
	t_heap *h;

	h = findHeapChunks(b);
	h->free_size -= b->data_size - beforeFusion->data_size;
	h->malloc_size += b->data_size - beforeFusion->data_size;
}

void *realloc(void *ptr, size_t size)
{
	t_block *b;
	t_block beforeFusion;
	void *newPtr;
	t_block *new;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	b = getBlock(ptr);
	if (!verifyAddress(b))
		return NULL;
	size = alignData(size);
	if (b->data_size >= size)
	{
		if (b && b->data_size > size + BLOCK_SIZE)
		{
			splitBlock(b, size);
			reduceHeap(b, size);
		}
	}
	else
	{
		beforeFusion = *b;
		fusion(&b);
		updateHeapRea(&beforeFusion, b);
		if (b->data_size >= size)
		{
			if (b && b->data_size > size + BLOCK_SIZE)
			{
				splitBlock(b, size);
				reduceHeap(b, size);
			}
			return BLOCK_SHIFT(b);
		}
		newPtr = malloc(size);
		if (!newPtr)
			return NULL;
		new = getBlock(newPtr);
		copyBlock(b, new);
		free(ptr);
		b = new;
	}
	return BLOCK_SHIFT(b);
}