#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret;

    ret = execl("/bin/ls", "ls", "-l", NULL);
    if (ret == -1)
        perror("execl");

    return 0;
}
