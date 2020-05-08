#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

const int INVALID_PID = -99999;

void printprocessid(int pid1, int pid2, int pid3)
{
    printf("real pid: %d; real parent pid: %d; pid1: %d; pid2: %d; pid3: %d; (%d means pid not assigned); ",
            getpid(), getppid(), pid1, pid2, pid3, INVALID_PID);
}

int main(int argc, char *argv[])
{
    char command[64];   
    
    int pid1 = INVALID_PID, pid2 = INVALID_PID, pid3 = INVALID_PID;

    pid1=fork();    
    pid2=fork();    

    if (pid1 == 0)
    {
        printf("\t");

        if (pid2 > 0)
        {            
            printprocessid(pid1, pid2, pid3);
            printf(" ");
            printf ("This\n");
        }
        else 
        {
            printf("\t");

            printprocessid(pid1, pid2, pid3);
            printf(" ");
            printf ("class is\n");
        }        
    }
    else 
    {
        if (pid2 == 0)
        {
            printf("\t");

            pid3 = fork();
            if (pid3 == 0) 
            {
                printf("\t");                
            }

            printprocessid(pid1, pid2, pid3);
            printf(" ");
            printf("really\n");
        }
        else
        {
            printprocessid(pid1, pid2, pid3);
            printf(" ");
            printf ("CLASS!\n");
        }
    }

    while(wait(NULL) > 0);

    if (pid1 == 0 && pid2 == 0)
    {
        snprintf(command, sizeof command, "ps -aef --forest | grep %s | grep -v grep", argv[0]);
        system(command);        
    }
    if (pid2 == 0 && pid3 == 0)
    {
        snprintf(command, sizeof command, "ps -aef --forest | grep %s | grep -v grep", argv[0]);
        system(command);        
    }
}