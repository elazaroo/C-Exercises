#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	char buffer[80];
	char sonGreeting[] = "Good morning father\0";
	int fd[2];
	
	pipe(fd);
	pid = fork();
	
	switch(pid) {
		case -1:// ERROR
			printf("Error when creating process\n");
			exit(-1);
		case 0:// SON
			close(fd[0]);
			write(fd[1], sonGreeting, sizeof(sonGreeting));
			printf("Son sends to father\n");
			break;
		default:// FATHER
			close(fd[1]);
			read(fd[0], buffer, sizeof(buffer));
			wait(NULL);
			printf("Parent receives from pipe: %s\n", buffer);
	}
}
