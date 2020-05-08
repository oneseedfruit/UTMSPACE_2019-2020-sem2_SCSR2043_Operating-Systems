#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid1, pid2, pid3;

    pid1=fork();
    pid2=fork();

    if (pid1 == 0)
    {
        if (pid2 > 0) 
            printf ("\nThis\n\n");
        else 
            printf ("\nclass is\n\n");
    }
    else 
    {
        if (pid2 == 0)
        {
            pid3 = fork();
            printf("\nreally\n");
        }
        else
            printf ("\nCLASS!\n");
    }
}