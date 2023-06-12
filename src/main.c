#include "../include/main.h"

// ◦ mmap(2)
//  void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
// ◦ munmap(2)
// ◦ getpagesize(2 or 3 depending on OS)
// ◦ getrlimit(2)
//  int getrlimit (int resource, struct rlimit *rlim);
void *base = NULL;

int main(void)
{
    char *test = ft_malloc(sizeof(char) * 3);
    if (!test)
        return (2);
    test[0] = 'o';
    test[1] = 'k';
    test[2] = '\0';
    printf("chaine de caratere: %s\n", test);
    char *test2 = ft_malloc(sizeof(int) * 10);
    char *test3 = ft_malloc(sizeof(char) * 10);
    printStruct();
    ft_free(test);
    printStruct();
    ft_free(test2);
    printStruct();
    ft_free(test3);
    printStruct();
    test = ft_malloc(sizeof(char) * 10);
    test2 = ft_malloc(sizeof(char) * 10);
    printStruct();
    ft_free(test);
    printStruct();
    test = ft_malloc(sizeof(char) * 17);
    printStruct();
    ft_free(test);
    ft_free(test2);
    ft_free(test3);
    printStruct();
    test = ft_malloc(sizeof(char) * 100);
    test2 = ft_malloc(sizeof(char) * 10);
    ft_free(test);
    printStruct();
    test = ft_malloc(sizeof(char) * 40);
    printStruct();
    ft_free(test);
    printStruct();
    ft_free(test2);
    printStruct();
    printf("\n------Bad adresses for free------\n");
    ft_free((void *)0x56);
    ft_free(NULL);
    printStruct();
    test = ft_malloc(sizeof(char) * 40);
    ft_free(test + 5);
}