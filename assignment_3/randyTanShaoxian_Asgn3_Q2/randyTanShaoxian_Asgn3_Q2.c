#include <stdio.h>
#include <unistd.h>

const int INVALID_PID = -99999;

int main(int argc, char *argv[])
{
    printf("I am the grandparent, and my ID is %d\n", getpid());

    int p = fork(), gc1 = INVALID_PID, gc2 = INVALID_PID;    

    if (p == 0)
    {
        printf("I am the parent, and my ID is %d\n", getpid());
        
        gc1 = fork();
        
        if (gc1 == 0)
        {
            printf("I am the grandchild1, and my ID is %d\n", getpid());
        }

        if (gc1 > 0)
        {
            gc2 = fork();

            if (gc2 == 0)
            {
                printf("I am the grandchild2, and my ID is %d\n", getpid());
            }
        }
    }
}