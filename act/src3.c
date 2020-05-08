#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    printf("Running ps with fork\n");
    pid = fork();

    if ( pid == 0 )
    {
        execlp("ps", "ps", "-ax", 0); // in the child, do exec
    }
    else if (pid < 0) // failed to fork
    {
        printf("fork failed.\n");
        exit(1);
    }
    else // parent
    {
        wait(NULL);
    }

    exit(0);

    return 0;
}
