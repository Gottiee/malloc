#include "../include/main.h"

int determineType(size_t size)
{
    if (size <= 100)
        return TINY;
    if (size <= 2000)
        return SMALL;
    return LARGE
}