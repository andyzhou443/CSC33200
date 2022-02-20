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

int main (int argc, char* argv[]){//takes in number of input and put it in the first array in memory
    //pointer to array of character
    int fd; //integer to hold file descriptor
    char* filepath = argv[1]; //takes file path from input
    //points to character array that is referenced to the first element of argv array
    if (argc != 2){ //error if there is mulitple arguments
        printf ("\n usage: \n");
        return 1;
    }

    fd = open(filepath, O_CREAT | 777);//creates and open file with all the permission

    if(-1 == fd) //error checking and prints out the error if fails
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