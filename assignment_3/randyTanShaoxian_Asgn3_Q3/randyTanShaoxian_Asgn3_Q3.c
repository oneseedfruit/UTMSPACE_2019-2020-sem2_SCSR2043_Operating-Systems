#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int c = fork();

    if (c == 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            printf("Hello World\n");
            sleep(1);
        }
    }

    wait(NULL);

    if (c > 0)
    {
        printf("Bye Bye\n");
    }
}