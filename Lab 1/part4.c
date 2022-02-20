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
    int fd,fdDest,fdDestErr; //creates integrs for file descriptors, file descriptor destination, and file descriptor error
    char buffer[8192]; //creates a big buffer to hold values

    if (argc != 3){ //error if there is more than 2 args
        printf ("Error: There can only be two parameters");
        return 1;
    }

    fd = access(filepath, F_OK); //checks existence of file
    if (fd == -1){ //error checking for access
        printf("\n access() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be accessed\n");
    }
    
    fdDest = open(fileDest, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); //creates file destination with Read write and truncate permissions. Mode is given with RW for user, and R for others.
    if (fdDest == -1){ //error checking for open destination directory
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n Destination file can be accessed\n");
    } 

    fd = open (filepath, S_IRUSR);//checks if the file can be opened and can be read
    if (fd == -1){ //error checking for open source directory
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{ //if there is no error, code will continue
        printf("\n file can be opened\n");

        fd = read (fd,buffer,sizeof(buffer)); //reads all of the source file form the start to the end. 
        if(fd == -1){ //error checking for reading source 
            printf("\n read() failed with error [%s]\n",strerror(errno)); 
            return 1;
        }
        else{
            printf("\n read() source file successful\n");
        }

        for(int i = 0; i < sizeof(buffer); i++) //loops through buffer (where source text is stored) to change all 1 to L
        {
            if(buffer[i] == '1') //checks if the bit is 1, if it is change it to L in buffer
                buffer[i] = 'L';
            if(i % 100 == 99){ // checks if char position is at 100
                for (int j = sizeof(buffer); j > i; j--){  //moves through all buffer from end to current position
                    buffer[j+3] = buffer [j]; // if char is at 100 position, move all the buffer to the right by 3 positions
                }
                buffer[i+1] = 'X'; //write X in the 101 position in buffer
                buffer[i+2] = 'Y'; //write Y in the 102 position in buffer
                buffer[i+3] = 'Z'; //write Z in the 103 position in buffer
                i = i + 3; //skips past the XYZ part in buffer
            }
                
        }

        fdDestErr = write (fdDest,buffer,fd);//writes to file destination starting from buffer (start) to the end of the fd (bytes read)
        if(fdDestErr== -1){//error checking for file destination
            printf("\n write() failed with error [%s]\n",strerror(errno)); 
            return 1;
        }
        else{
            printf("\n write() destination file successful\n");
        }

        printf("\n");
        printf(" File from %s has been successfully copied into %s\n", filepath,fileDest);

        close(fd); //closes both fd and fdDest to free space
        close(fdDest);
        
    }
    //negative means call failed
    //positive is pass
    //
    return 0;
}