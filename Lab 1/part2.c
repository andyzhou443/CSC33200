/*
The cp command copies the source file specified by the SourceFile parameter to the destination file specified by the DestinationFile 
parameter.Write a C program that mimics the cp command using open() system call to open source.txt file in read-only mode and 
copy the contents of it to destination.txt using read() and write() system calls.
*/

#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 
#include <errno.h>
#include <unistd.h>

int main (int argc, char* argv[]){

    char* filepath = argv[1]; //pointer for path file
    char* fileDest = argv[2]; //pointer for destination file
    int fd,fdDest,fdDestErr;
    char buffer[8192];

    if (argc != 3){ //error if there is more than 2 args
        printf ("Error: There can only be two parameters");
        return 1;
    }

    fd = access(filepath, F_OK); //checks existence of file
    if (fd == -1){
        printf("\n access() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be accessed\n");
    }
    
    fdDest = open(fileDest, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); //creates file destination with Read write and truncate permissions. Mode is given with RW for user, and R for others.
    if (fdDest == -1){
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n Destination file can be accessed\n");
    } 

    fd = open (filepath, S_IRUSR);//checks if the file can be opened and can be read
    if (fd == -1){
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be opened\n");

        fd = read (fd,buffer,sizeof(buffer));
        if(fd == -1){
            printf("\n read() failed with error [%s]\n",strerror(errno)); 
            return 1;
        }
        else{
            printf("\n read() source file successful\n");
        }

        fdDestErr = write (fdDest,buffer,fd);//writes to file destination starting from buffer (start) to the end of the fd (bytes read)
        if(fdDestErr== -1){
            printf("\n write() failed with error [%s]\n",strerror(errno)); 
            return 1;
        }
        else{
            printf("\n write() destination file successful\n");
        }

        printf("\n");
        printf(" File from %s has been successfully copied into %s\n", filepath,fileDest);

        close(fd);
        close(fdDest);
        
    }

    
    //negative means call failed
    //positive is pass
    //
    return 0;
}