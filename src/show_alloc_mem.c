#include "../include/malloc.h"

void printData(t_block *b, size_t *size)
{
	while (b)
	{
		ft_putstr_fd("Ox", 1);
		ft_puthex((unsigned long int)(void *)b);
		ft_putstr_fd(" = 0x", 1);
		ft_puthex((unsigned long int)(void *)BLOCK_SHIFT(b));
		ft_putstr_fd(" : ", 1);
		ft_putlong_fd(b->data_size, 1);
		*size += b->data_size;
		ft_putstr_fd(" bytes\n", 1);
		b = b->next;
	}
}

void show_alloc_mem()
{
	char *phrase[] = {"TINY", "SMALL", "LARGE"};
	t_group_heap *g = NULL;
	size_t size = 0;

	g = base;
	if (!g)
	{
		ft_putstr_fd(ROUGE "Heap unallocated\n" RESET, 1);
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		t_heap *h = g->zone[i];
		t_heap *tmp;
		if (h)
		{
			ft_putstr_fd(phrase[i], 1);
			ft_putstr_fd(" : Ox", 1);
			ft_puthex((unsigned long int)(void *)h);
			ft_putstr_fd("\n", 1);
		}
		if (!h)
			continue;
		while (h)
		{
			printData((t_block *)((char *)h + HEAP_SIZE), &size);
			h = h->next;
		}
	}
	ft_putstr_fd("Total : ", 1);
	ft_putlong_fd(size, 1);
	ft_putstr_fd(" bytes\n\n", 1);
}