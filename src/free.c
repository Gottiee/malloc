#include "../include/main.h"

// Look for prev and next block, if their are free, merge them to be anunique block
t_block *fusion(t_block **b)
{
    t_block tmp;
    if ((*b) && (*b)->prev && (*b)->prev->freed)
    {
        (*b)->prev->next = (*b)->next;
        (*b)->next->prev = (*b)->prev;
        (*b)->prev->data_size += BLOCK_SIZE + (*b)->data_size;
        if ((*b) && (*b)->next && (*b)->next->freed)
        {
            (*b)->prev->next = (*b)->next->next;
            (*b)->next->next->prev = (*b)->prev;
            (*b)->prev->data_size += (*b)->next->data_size + BLOCK_SIZE;
        }
        return (*b)->prev;
    }
    else if ((*b) && (*b)->next && (*b)->next->freed)
    {
        tmp.next = (*b)->next;
        (*b)->next = (*b)->next->next;
        (*b)->next->prev = (*b);
        (*b)->data_size += BLOCK_SIZE + tmp.next->data_size;
    }
    return (*b);
}

//return the block 
t_block *getBlock(void *ptr)
{
    return ptr - BLOCK_SIZE;
}

//verify addrs to free
bool verifyAddress(void )
{

}

void ft_free(void *ptr)
{ 
}