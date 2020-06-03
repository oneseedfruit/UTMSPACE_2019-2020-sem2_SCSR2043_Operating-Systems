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
    pid_t   pidA, pidB, pidC;
    pidA =0; pidB = 0; pidC = 0;
 
    pidB = fork();
    if (pidB == 0) {
       pidA = fork();
       pidC = fork();
      } 
    else {
       pidC = fork();
       if (pidC == 0) 
         pidA = fork();
    }

    while(wait(NULL) > 0);

    // snprintf(command, sizeof command, "ps -aef --forest | grep %s | grep -v grep", argv[0]);
    // system(command);   

    if (pidA == 0 && pidB == 0)
    {
        snprintf(command, sizeof command, "ps -aef --forest | grep %s | grep -v grep", argv[0]);
        system(command);        
    }
    if (pidB == 0 && pidC == 0)
    {
        snprintf(command, sizeof command, "ps -aef --forest | grep %s | grep -v grep", argv[0]);
        system(command);        
    }
}