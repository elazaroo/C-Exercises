#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void main()
{
    pid_t pid, son_pid;
    pid = fork();

    if (pid == -1) // Error creating son proccess
    {
        printf("Couldn't create son process...\n");
        exit(-1);
    } 
    else if (pid == 0) // In son proccess
    {
        printf("I'm the son process\n\tMy PID is %d, my Parent's PID is %d\n", getpid(), getppid());
    } 
    else // In parent proccess
    {
        son_pid = wait(NULL); // Wait son to finish
        printf("I'm the parent process\n\tMy PID is %d, my Parent's PID is %d\n\tMy son %d has finished.\n", getpid(), getppid(), pid);
    }
    exit(0);
}

