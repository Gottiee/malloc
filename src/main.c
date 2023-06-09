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
    printStruct();
}