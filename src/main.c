#include "../include/main.h"

// ◦ mmap(2)
//  void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
// ◦ munmap(2)
// ◦ getpagesize(2 or 3 depending on OS)
// ◦ getrlimit(2)
//  int getrlimit (int resource, struct rlimit *rlim);

void test(void)
{
    printf("------Malloc TEST------\n");
    printf("\n------Simple Malloc------\n");
    char *test = ft_malloc(sizeof(char) * 3);
    if (!test)
        return (2);
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
    test = ft_malloc(sizeof(char) * 100);
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

    printf("\n------Bad adresses for free------\n");
    printf("free(0x56)\n");
    ft_free((void *)0x56);
    printf("free(NULL)\n");
    ft_free(NULL);
    printf("free(test + 5)\n");
    test = ft_malloc(sizeof(char) * 40);
    ft_free(test + 5);
    ft_free(test);
}

int main(void)
{
    // test();
}