#include "../include/main.h"

// ◦ mmap(2)
//  void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
// ◦ munmap(2)
// ◦ getpagesize(2 or 3 depending on OS)
// ◦ getrlimit(2)
//  int getrlimit (int resource, struct rlimit *rlim);

int main(void)
{
    int *test = malloc(sizeof(int) * 3);
    test[0] = 1;
    test[2] = 3;
    printf("test[0] = %d\ntest[2] = %d\n", test[0], test[2]);
    printf("sizeof(t_block) = %ld\n", sizeof(t_block));
}