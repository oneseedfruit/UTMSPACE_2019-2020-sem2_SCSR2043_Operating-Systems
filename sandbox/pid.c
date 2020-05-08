#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("My pid=%jd\n", (intmax_t) getpid());
    printf("Parent's pid=%jd\n", (intmax_t) getppid());
    return 0;
}
