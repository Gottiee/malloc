#include "../include/main.h"

void blockTest(void)
{
    printf("------Malloc BLOCK TEST------\n");
    printf("\n------Simple Malloc------\n");
    char *test = ft_malloc(sizeof(char) * 3);
    test[0] = 'o';
    test[1] = 'k';
    test[2] = '\0';
    printf("Malloc(sizeof(char) * 3 & write ok inside : chaine de caratere: %s\n", test);

    char *test2 = ft_malloc(sizeof(int) * 10);
    char *test3 = ft_malloc(sizeof(char) * 10);
    printf("\n------Malloc 2 other Chunks------");
    printStruct();
    printf("\n------Free First------");
    ft_free(test);
    printStruct();
    printf("\n------Free Second------");
    ft_free(test2);
    printStruct();
    ft_free(test3);
    printf("\n------Free Third------");
    printStruct();

    printf("\n------Malloc in Free chunks------\n");
    printf("------Malloc two chunks------");
    test = ft_malloc(sizeof(char) * 10);
    test2 = ft_malloc(sizeof(char) * 10);
    printStruct();
    printf("\n------Free first------");
    ft_free(test);
    printStruct();
    printf("\n------Malloc a chunks bigger than the free space available------");
    test = ft_malloc(sizeof(char) * 17);
    printStruct();
    printf("\n------Malloc a chunks equal to the free space------");
    test3 = ft_malloc(sizeof(char) * 16);
    printStruct();
    ft_free(test);
    ft_free(test2);
    ft_free(test3);
    printf("\n------Free space------");
    printStruct();

    printf("\n------Malloc in Free space to split block------\n");
    printf("------Malloc two chunks and free First------");
    test = ft_malloc(sizeof(char) * 96);
    test2 = ft_malloc(sizeof(char) * 10);
    ft_free(test);
    printStruct();
    printf("\n------Malloc chunks smaller than the space free------");
    test = ft_malloc(sizeof(char) * 40);
    printStruct();
    printf("\n------Free space------");
    ft_free(test);
    printStruct();
    ft_free(test2);
    printStruct();
}

void mallocThings(size_t size, char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        tab[i] = ft_malloc(size);
    printStruct();
}

void freeThings(char **tab, int howMany)
{
    for (int i = 0; i < howMany; i++)
        ft_free(tab[i]);
}

void freeTest()
{

    char *test;

    printf("\n------Bad adresses for free------\n");
    printf("nothing malloc\n");
    ft_free((void *)0x56);
    test = ft_malloc(sizeof(char) * 40);
    printf("free(0x56)\n");
    ft_free((void *)0x56);
    printf("free(NULL)\n");
    ft_free(NULL);
    printf("free(test + 5)\n");
    ft_free(test + 5);
    ft_free(test);
}

void zoneTest()
{
    char *test, *test2, *test3;
    char **tab;

    printf("\n\n------Malloc Zone TEST------\n");
    printf("------Malloc one of each zone------\n");
    test = ft_malloc(sizeof(char) * 50);
    test2 = ft_malloc(sizeof(char) * 500);
    test3 = ft_malloc(sizeof(char) * 5000);
    printStruct();
    printf("\n------Free them------\n");
    ft_free(test);
    ft_free(test2);
    ft_free(test3);
    printStruct();
    printf("\n------Malloc at least 100 in one chunks------\n");
    printf("\n------120 Tiny of size 100 (heap align 104)------\n");
    tab = ft_malloc(sizeof(char *) * 1000);
    mallocThings(100, tab, 120);
    printf("\n------malloc one more------\n");
    test = ft_malloc(100);
    printStruct();
    printf("\n------Free them (only large should remain (tab ptr))------\n");
    freeThings(tab, 120);
    ft_free(test);
    printStruct();
    printf("\n------100 SMALL of size 2000------\n");
    mallocThings(2000, tab, 100);
    printf("\n------malloc one more------\n");
    test = ft_malloc(2000);
    printStruct();
    printf("\n------Free all------\n");
    freeThings(tab, 100);
    ft_free(test);
    printStruct();
    printf("\n------100 LARGE of size 5000------\n");
    mallocThings(5000, tab, 100);
    printf("\n------Free all------\n");
    freeThings(tab, 100);
    ft_free(tab);
    printStruct();
}

void reallocTest(void)
{
    char *test;
    char *non = "cool ! everything has been well copyed !";

    printf("\n\n------Realloc TEST------\n");
    printf("------cmd: realloc(NULL, 10) | malloc 10------\n");
    test = ft_realloc(NULL, 10);
    printStruct();
    printf("------cmd: realloc((char *ptr), 0) | free ptr------\n");
    ft_realloc(test, 0);
    printStruct();
    printf("------realloc same size------\n");
    printf("------cmd: realloc((char *ptr), 100)------\n");
    test = ft_realloc(NULL, 100);
    printStruct();
    test = ft_realloc(test, 100);
    printStruct();
    printf("------realloc smaller size------\n");
    printf("------cmd: realloc((char *ptr), 40)------\n");
    test = ft_realloc(test, 40);
    printStruct();
    printf("------realloc bigger size------\n");
    printf("------cmd: realloc((char *ptr), 60)------\n");
    test = ft_realloc(test, 60);
    printStruct();
    printf("------realloc bigger size other configuration------\n");
    printf("------Free first------\n");
    ft_free((test));
    printStruct();
    printf("------malloc(40)------\n");
    test = ft_malloc(40);
    printStruct();
    printf("------cmd: realloc((char *ptr), 60)------\n");
    test = ft_realloc(test, 60);
    printStruct();
    printf("------Free all------\n");
    ft_free(test);
    printStruct();
    printf("------Persistant data transfer------\n");
    printf("------malloc 40 and write text inside------\n");
    test = ft_malloc(sizeof(char) * 40);
    for (int i = 0; non[i]; i++)
        test[i] = non[i];
    printf("string = \"%s\"\n", test);
    printStruct();
    printf("------cmd: realloc((char *ptr), 60)------\n");
    test = ft_realloc(test, 60);
    printStruct();
    printf("string after realloc(test, 60)= \"%s\"\n", test);
    printf("------Free all------\n");
    ft_free(test);
    printStruct();
}

int main(void)
{
    blockTest();
    zoneTest();
    freeTest();
    reallocTest();
}