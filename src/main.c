#include "../include/malloc.h"

void blockTest(void)
{
    ft_putstr_fd("------Malloc BLOCK TEST------\n", 1);
    ft_putstr_fd("\n------Simple Malloc------\n", 1);
    char *test = malloc(sizeof(char) * 3);
    test[0] = 'o';
    test[1] = 'k';
    test[2] = '\0';
    printStruct();
    ft_putstr_fd("Malloc(sizeof(char) * 3 & write ok inside : chaine de caratere: ", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\n", 1);

    char *test2 = malloc(sizeof(char) * 10);
    char *test3 = malloc(sizeof(char) * 10);
    ft_putstr_fd("\n------Malloc 2 other Chunks------", 1);
    printStruct();
    ft_putstr_fd("\n------Free First------", 1);
    free(test);
    printStruct();
    ft_putstr_fd("\n------Free Second------", 1);
    free(test2);
    printStruct();
    free(test3);
    ft_putstr_fd("\n------Free Third------", 1);
    printStruct();

    ft_putstr_fd("\n------Malloc in Free chunks------\n", 1);
    ft_putstr_fd("------Malloc two chunks------", 1);
    test = malloc(sizeof(char) * 10);
    test2 = malloc(sizeof(char) * 10);
    printStruct();
    ft_putstr_fd("\n------Free first------", 1);
    free(test);
    printStruct();
    ft_putstr_fd("\n------Malloc a chunks bigger than the free space available------", 1);
    test = malloc(sizeof(char) * 17);
    printStruct();
    ft_putstr_fd("\n------Malloc a chunks equal to the free space------", 1);
    test3 = malloc(sizeof(char) * 16);
    printStruct();
    free(test);
    free(test2);
    free(test3);
    ft_putstr_fd("\n------Free space------", 1);
    printStruct();

    ft_putstr_fd("\n------Malloc in Free space to split block------\n", 1);
    ft_putstr_fd("------Malloc two chunks and free First------", 1);
    test = malloc(sizeof(char) * 96);
    test2 = malloc(sizeof(char) * 10);
    free(test);
    printStruct();
    ft_putstr_fd("\n------Malloc chunks smaller than the space free------", 1);
    test = malloc(sizeof(char) * 40);
    printStruct();
    ft_putstr_fd("\n------Free space------", 1);
    free(test);
    printStruct();
    free(test2);
    printStruct();
}

void mallocThings(size_t size, char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        tab[i] = malloc(size);
    printStruct();
}

void freeThings(char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        free(tab[i]);
}

void freeTest()
{

    char *test;

    ft_putstr_fd("\n------Bad adresses for free------\n", 1);
    ft_putstr_fd("nothing malloc\n", 1);
    free((void *)0x56);
    test = malloc(sizeof(char) * 40);
    ft_putstr_fd("free(0x56)\n", 1);
    free((void *)0x56);
    ft_putstr_fd("free(NULL)\n", 1);
    free(NULL);
    ft_putstr_fd("free(test + 5)\n", 1);
    free(test + 5);
    free(test);
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
    printStruct();
    ft_putstr_fd("\n------Free them------\n", 1);
    free(test);
    free(test2);
    free(test3);
    printStruct();
    ft_putstr_fd("\n------Malloc at least 100 in one chunks------\n", 1);
    ft_putstr_fd("\n------120 Tiny of size 100 (heap align 104)------\n", 1);
    tab = malloc(sizeof(char *) * 1000);
    mallocThings(100, tab, 120);
    ft_putstr_fd("\n------malloc one more------\n", 1);
    test = malloc(100);
    printStruct();
    ft_putstr_fd("\n------Free them (only large should remain (tab ptr))------\n", 1);
    freeThings(tab, 120);
    free(test);
    printStruct();
    ft_putstr_fd("\n------100 SMALL of size 2000------\n", 1);
    mallocThings(2000, tab, 100);
    ft_putstr_fd("\n------malloc one more------\n", 1);
    test = malloc(2000);
    printStruct();
    ft_putstr_fd("\n------Free all------\n", 1);
    freeThings(tab, 100);
    free(test);
    printStruct();
    ft_putstr_fd("\n------100 LARGE of size 5000------\n", 1);
    mallocThings(5000, tab, 100);
    ft_putstr_fd("\n------Free all------\n", 1);
    freeThings(tab, 100);
    free(tab);
    printStruct();
}

void reallocTest(void)
{
    char *test;
    char *non = "cool ! everything has been well copyed !";

    ft_putstr_fd("\n\n------Realloc TEST------\n", 1);
    ft_putstr_fd("------cmd: realloc(NULL, 10) | malloc 10------\n", 1);
    test = realloc(NULL, 10);
    printStruct();
    ft_putstr_fd("------cmd: realloc((char *ptr), 0) | free ptr------\n", 1);
    test = realloc(test, 0);
    printStruct();
    ft_putstr_fd("------realloc same size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 100)------\n", 1);
    test = realloc(NULL, 100);
    printStruct();
    test = realloc(test, 100);
    printStruct();
    ft_putstr_fd("------realloc smaller size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 40)------\n", 1);
    test = realloc(test, 40);
    printStruct();
    ft_putstr_fd("------realloc bigger size------\n", 1);
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    printStruct();
    ft_putstr_fd("------realloc bigger size other configuration------\n", 1);
    ft_putstr_fd("------Free first------\n", 1);
    free((test));
    printStruct();
    ft_putstr_fd("------malloc(40)------\n", 1);
    test = malloc(40);
    printStruct();
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    printStruct();
    ft_putstr_fd("------Free all------\n", 1);
    free(test);
    printStruct();
    ft_putstr_fd("------Persistant data transfer------\n", 1);
    ft_putstr_fd("------malloc 40 and write text inside------\n", 1);
    test = malloc(sizeof(char) * 40);
    for (int i = 0; non[i]; i++)
        test[i] = non[i];
    ft_putstr_fd("string =\"", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\"\n", 1);
    printStruct();
    ft_putstr_fd("------cmd: realloc((char *ptr), 60)------\n", 1);
    test = realloc(test, 60);
    printStruct();
    ft_putstr_fd("string after realloc(test, 60)= \"", 1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\"\n", 1);
    ft_putstr_fd("------Free all------\n", 1);
    free(test);
    printStruct();
}

int main(void)
{
    blockTest();
    zoneTest();
    freeTest();
    reallocTest();
}