#include <stdio.h>
#include <unistd.h>

void main(void)
{
	pid_t actual_id, parent_id;
	actual_id = getpid();
	parent_id = getppid();
	
	printf("ACTUAL ID %d ", actual_id);
	printf("\nPARENT ID %d\n", parent_id);
}
