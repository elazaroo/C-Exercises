#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
	int var = 6;
	pid_t pid, son_pid;
	printf("Initial variable value: %d\n", var);
	pid = fork();
	if (pid == -1) // Error creating son proccess
	{
		printf("Error creating son proccess\n");
		exit(-1);
	}
	if(pid == 0) // son proccess
	{
		printf("Variable in son proccess: %d\n", (var-5));
		exit(0);
	} else // Parent process
	{
		son_pid = wait(NULL);
		printf("Variable in parent proccess: %d\n", (var+5));
		exit(0);
	}
}
