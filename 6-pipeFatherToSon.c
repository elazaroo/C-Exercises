#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	pid_t pid;
	char fatherGreeting[] = "Good morning son.\0";
	char buffer[80];
	
	pipe(fd);// create pipe
	pid = fork();// create process
	
	switch(pid)
	{
		case -1:// ERROR
			printf("Error when createng process.\n");
			exit(-1);
		case 0:// Son recieves
			close(fd[1]);// Close input descriptor
			read(fd[0], buffer, sizeof(buffer));// Read the pipe
			printf("\tSON recieves sth from pipe: %s\n", buffer);
			break;
		default:// Father sends
			close(fd[0]);
			write(fd[1], fatherGreeting, strlen(fatherGreeting));// Write in pipe
			printf("FATHER sends message to son\n");
			wait(NULL);
			break;
	}
	return(0);
}
