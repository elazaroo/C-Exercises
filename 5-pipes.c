#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	char buffer[30];
	pid_t pid;
	
	pipe(fd);// Create the pipe
	
	pid = fork();// Create son process
	
	switch(pid) {
		case -1:// ERROR
			printf("An error ocurred when creating son procces");
			exit(-1);
			break;
		case 0:// SON
			printf("SON writes in pipe...\n");
			write(fd[1], "Hello father", 13);
			break;
		default:// FATHER
			wait(NULL);
			printf("FATHER reads pipe...\n");
			read(fd[0], buffer, 13);
			printf("\tReaded message: %s\n", buffer);
			break;
	}	
}
