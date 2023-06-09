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
    char *test = malloc(sizeof(char) * 4);
    if (!test)
        return (2);
    test[0] = 'o';
    test[1] = 'k';
    test[2] = '\n';
    test[3] = '\0';
    write(1, test, 3);
}