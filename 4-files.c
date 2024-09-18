#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void main()
{
    char greeting [] = "Best regards!\n";
    char buffer[10];
    int fd, readedBytes, cont = 0;
    
    fd = open("text.txt", 1); // 1 write mode, 0 read mode
    if (fd == -1)
    {
        printf("AN ERROR OCURRED WHEN OPENING THE FILE.\n");
        exit(-1);
    }
    
    printf("Writing the greeting\n");
    write(fd, greeting, strlen(greeting));
    close(fd);
    
    fd = open("text.txt", 0); // 1 write mode, 0 read mode
    printf("File content:\n");
    
    // Read each byte and save in buffer
    readedBytes = read(fd, buffer, 1);
    while (readedBytes != 0)
    {
    	cont = cont + 1;
        printf("%s", buffer); // print readed byte
        readedBytes = read(fd, buffer, 1); // read another byt
    }
    printf("Final readed bytes cont: %d\n", cont);
    close(fd);
}
