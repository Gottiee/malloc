#include "inc/malloc.h"

void blockTest(void)
{
    ft_putstr_fd("------Malloc BLOCK TEST------\n", 1);
    ft_putstr_fd("\n------Simple Malloc------\n", 1);
    char *test = malloc(sizeof(char) * 3);
    test[0] = 'o';
    test[1] = 'k';
    test[2] = '\0';
    show_alloc_mem_ex();
    ft_putstr_fd("Malloc(sizeof(char) * 3 & write ok inside : chaine de caratere: ", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\n", 1);

    char *test2 = malloc(sizeof(char) * 10);
    char *test3 = malloc(sizeof(char) * 10);
    ft_putstr_fd("\n------Malloc 2 other Chunks------", 1);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free First------", 1);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free Second------", 1);
    free(test2);
    show_alloc_mem_ex();
    free(test3);
    ft_putstr_fd("\n------Free Third------", 1);
    show_alloc_mem_ex();

    ft_putstr_fd("\n------Malloc in Free chunks------\n", 1);
    ft_putstr_fd("------Malloc two chunks------", 1);
    test = malloc(sizeof(char) * 10);
    test2 = malloc(sizeof(char) * 10);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free first------", 1);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Malloc a chunks bigger than the free space available------", 1);
    test = malloc(sizeof(char) * 17);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Malloc a chunks equal to the free space------", 1);
    test3 = malloc(sizeof(char) * 16);
    show_alloc_mem_ex();
    free(test);
    free(test2);
    free(test3);
    ft_putstr_fd("\n------Free space------", 1);
    show_alloc_mem_ex();

    ft_putstr_fd("\n------Malloc in Free space to split block------\n", 1);
    ft_putstr_fd("------Malloc two chunks and free First------", 1);
    test = malloc(sizeof(char) * 96);
    test2 = malloc(sizeof(char) * 10);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Malloc chunks smaller than the space free------", 1);
    test = malloc(sizeof(char) * 40);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free space------", 1);
    free(test);
    show_alloc_mem_ex();
    free(test2);
    show_alloc_mem_ex();
}

void mallocThings(size_t size, char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        tab[i] = malloc(size);
    show_alloc_mem_ex();
}

void freeThings(char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        free(tab[i]);
}

void zoneTest()
{
    char *test, *test2, *test3;
    char **tab;

    ft_putstr_fd("\n\n------Malloc Zone TEST------\n", 1);
    ft_putstr_fd("------Malloc one of each zone------\n", 1);
    test = malloc(sizeof(char) * 50);
    test2 = malloc(sizeof(char) * 500);
    test3 = malloc(sizeof(char) * 5000);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free them------\n", 1);
    free(test);
    free(test2);
    free(test3);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Malloc at least 100 in one chunks------\n", 1);
    ft_putstr_fd("\n------120 Tiny of size 100 (heap align 104)------\n", 1);
    tab = malloc(sizeof(char *) * 1000);
    mallocThings(100, tab, 120);
    ft_putstr_fd("\n------malloc one more------\n", 1);
    test = malloc(100);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free them (only large should remain (tab ptr))------\n", 1);
    freeThings(tab, 120);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------100 SMALL of size 2000------\n", 1);
    mallocThings(2000, tab, 100);
    ft_putstr_fd("\n------malloc one more------\n", 1);
    test = malloc(2000);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------Free all------\n", 1);
    freeThings(tab, 100);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("\n------100 LARGE of size 5000------\n", 1);
    mallocThings(5000, tab, 100);
    ft_putstr_fd("\n------Free all------\n", 1);
    freeThings(tab, 100);
    free(tab);
    show_alloc_mem_ex();
}

void reallocTest(void)
{
    char *test;
    int i = -1;
    char *non = "everything has been well copyed !";

    ft_putstr_fd("\n\n------Realloc TEST------\n", 1);
    ft_putstr_fd("------cmd: realloc(NULL, 10) | malloc 10------\n", 1);
    test = realloc(NULL, 10);
    show_alloc_mem_ex();
    ft_putstr_fd("------cmd: realloc((char *ptr), 0) | free ptr------\n", 1);
    test = realloc(test, 0);
    show_alloc_mem_ex();
    ft_putstr_fd("------realloc same size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 100)------\n", 1);
    test = realloc(NULL, 100);
    show_alloc_mem_ex();
    test = realloc(test, 100);
    show_alloc_mem_ex();
    ft_putstr_fd("------realloc smaller size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 40)------\n", 1);
    test = realloc(test, 40);
    show_alloc_mem_ex();
    ft_putstr_fd("------realloc bigger size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    show_alloc_mem_ex();
    ft_putstr_fd("------realloc bigger size other configuration------\n", 1);
    ft_putstr_fd("------Free first------\n", 1);
    free((test));
    show_alloc_mem_ex();
    ft_putstr_fd("------malloc(40)------\n", 1);
    test = malloc(40);
    show_alloc_mem_ex();
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    show_alloc_mem_ex();
    ft_putstr_fd("------Free all------\n", 1);
    free(test);
    show_alloc_mem_ex();
    ft_putstr_fd("------Persistant data transfer------\n", 1);
    ft_putstr_fd("------malloc 40 and write text inside------\n", 1);
    test = malloc(sizeof(char) * 40);
    while (non[++i])
        test[i] = non[i];
    test[i] = '\0';
    ft_putstr_fd("string =\"", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\"\n", 1);
    show_alloc_mem_ex();
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    show_alloc_mem_ex();
    ft_putstr_fd("string after realloc(test, 60)= \"", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\"\n", 1);
    ft_putstr_fd("------Free all------\n", 1);
    free(test);
    show_alloc_mem_ex();
}

void showAllocTest(void)
{
    ft_putstr_fd("\n\n------Show alloc TEST------\n", 1);
    ft_putstr_fd("------malloc 4 ptr and print them------\n\n", 1);
    char *test = malloc(50);
    char *test2 = malloc(200);
    char *test3 = malloc(2000);
    char *test4 = malloc(2500);
    for (int i = 0; i < 8; i++)
        test4[i] = 'A';
    char *test5 = malloc(5500);
    show_alloc_mem();
    free(test);
    free(test2);
    free(test3);
    free(test4);
    free(test5);
    show_alloc_mem();
}

int main(void)
{
    blockTest();
    zoneTest();
    reallocTest();
    showAllocTest();
}