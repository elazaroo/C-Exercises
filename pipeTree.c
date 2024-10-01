#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void main(void) {
    pid_t pid1, pid2, pid3, pid4, pid5, Child_pid1, Child_pid2, Child_pid3, Child_pid4, Child_pid5;

    pid1 = fork();
    if (pid1 == -1) {
        printf("Failed to create the child process...\n");
        exit(-1);
    }
    if (pid1 == 0) {
        pid3 = fork();
        switch (pid3) {
            case -1:
                printf("Failed to create the child process in the CHILD\n");
                exit(-1);
                break;
            case 0:
                printf("\t\tI am the process PA11 (%d)\n", getpid());
                break;
            default:
                Child_pid3 = wait(NULL);
                pid4 = fork();
                if (pid4 == -1) {
                    printf("Failed to create the child process...\n");
                    exit(-1);
                }
                if (pid4 == 0) {
                    pid5 = fork();
                    if (pid5 == -1) {
                        printf("Failed to create the child process...\n");
                        exit(-1);
                    }
                    if (pid5 == 0) {
                        printf("\t\t\tI am the process PA121 (%d)\n", getpid());
                    } else {
                        Child_pid5 = wait(NULL);
                        printf("\t\tI am the process PA12 (%d), my child is: %d\n", getpid(), Child_pid5);
                    }
                } else {
                    Child_pid4 = wait(NULL);
                    printf("\tI am the process PA1 (%d), my children are: %d %d\n", getpid(), Child_pid3, Child_pid4);
                }
        }
    } else {
        Child_pid1 = wait(NULL);
        pid2 = fork();
        if (pid2 == -1) {
            printf("Failed to create the child process...\n");
            exit(-1);
        }
        if (pid2 == 0) {
            printf("\tI am the process PA2 (%d)\n", getpid());
        } else {
            Child_pid2 = wait(NULL);
            printf("I am the PARENT process, my children are: %d %d \n", Child_pid1, Child_pid2);
        }
    }
}
