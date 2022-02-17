/*(b) Write a C program where open system call creates a 
new file (say, destination.txt) and then opens it. 
(Hint: use the bitwise OR flag)*/
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 
#include <errno.h>
#include <unistd.h>

int main (int argc, char* argv[]){

    int fd;
    char* filepath = argv[1];

    if (argc != 2){
        printf ("\n usage: \n");
        return 1;
    }

    fd = open(filepath, O_CREAT | 777);

    if(-1 == fd) 
    { 
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n program successful \n");
        close(fd);
    }

    return 0;
}