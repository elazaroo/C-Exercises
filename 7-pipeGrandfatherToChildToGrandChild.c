#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void main(void) {
    pid_t pid1, pid2, Child_pid, Child2_pid;
    int fd1[2], fd2[2];
    char grandparentGreeting[] = "Greetings from the Grandfather.\0";
    char parentGreeting[] = "Greetings from the Father..\0";
    char childGreeting[] = "Greetings from the Child...\0";
    char grandchildGreeting[] = "Greetings from the Grandchild..\0";
    char buffer[80] = "";

    pipe(fd1);
    pipe(fd2);
    pid1 = fork();
    
    if (pid1 == -1) {
        printf("Failed to create the child process...");
        exit(-1);
    }
    if (pid1 == 0) {
        pid2 = fork();
        switch (pid2) {
            case -1:
                printf("Failed to create the child process in the CHILD");
                exit(-1);
                break;
            case 0:
                // GRANDCHILD RECEIVES FROM PARENT
                close(fd2[1]);
                read(fd2[0], buffer, sizeof(buffer));
                printf("\t\tGRANDCHILD RECEIVES message from the parent: %s \n", buffer);

                // GRANDCHILD SENDS TO PARENT
                printf("\t\tGRANDCHILD SENDING MESSAGE to the parent...\n");
                close(fd1[0]);
                write(fd1[1], grandchildGreeting, strlen(grandchildGreeting));
                break;
            default:
                // CHILD RECEIVES
                close(fd1[1]);
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tCHILD receives message from the GRANDFATHER: %s \n", buffer);

                // CHILD SENDS TO GRANDCHILD
                close(fd2[0]);
                write(fd2[1], parentGreeting, strlen(parentGreeting));
                Child2_pid = wait(NULL);

                // RECEIVES FROM GRANDCHILD
                close(fd1[1]);
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tCHILD RECEIVES message from the GRANDCHILD: %s \n", buffer);

                // CHILD SENDS TO GRANDPARENT
                printf("\tCHILD SENDING MESSAGE to the grandparent...\n");
                close(fd2[0]);
                write(fd2[1], childGreeting, strlen(childGreeting));
        }
    } else {
        // GRANDPARENT SENDS
        printf("GRANDPARENT SENDING MESSAGE TO THE CHILD...\n");
        close(fd1[0]);
        write(fd1[1], grandparentGreeting, strlen(grandparentGreeting));
        Child_pid = wait(NULL);

        // GRANDPARENT RECEIVES
        close(fd2[1]);
        read(fd2[0], buffer, sizeof(buffer));
        printf("THE GRANDPARENT receives message from the CHILD: %s \n", buffer);
    }
    exit(0);
}

