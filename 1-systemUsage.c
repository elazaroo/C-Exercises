#include <stdio.h>
#include <stdlib.h>

void main()
{
	printf("Example of usage of system():");
	printf("\nListing of the current directory and sending to a file:");
	printf("%d", system("ls > outputfile"));
	printf("\nWe open with gedit and file...");
	printf("%d",system("gedit outputfile"));
	printf("\n\tThis command is wrong: %d", system("ged"));
	printf("\nEnd of program\n");
}
