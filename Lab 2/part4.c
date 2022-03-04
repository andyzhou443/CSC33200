#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char* argv){
    char* filepath = "readme.txt"; //directs the code to the readme.txt file
    int fd, pipefd[2], fq = 0, wait, fdErr, fdErrTwo; 
    int returnvalue;
    struct stat OGfileCharacteristics; //used for fstat
    //pipefd [0] is read while pipefd [1] is write
    char parentBuffer[20] = {"Parent is writing: "};

    if (pipe(pipefd) == -1){//checks if there is error with pipe
        printf("An error has occurred with the pipe\n");
        return 1;
    }

    fq = fork();//forks child
    if (fq == -1){ //error checking in forking child
        printf("error fork was unsuccessful\n");
        return 1;
    }

    if(fq == 0){//checks if we are in the child 
        fd = open (filepath, O_RDONLY|S_IRUSR);//checks if the file can be opened and can be read
        if (fd == -1){ //error checking
            printf("\n open() failed with error [%s]\n",strerror(errno)); 
            return 1; 
        }
        else{ //continue if no error
            printf("\n file can be opened\n");
            fstat(fd,&OGfileCharacteristics); //takes info form file descriptor and write it to OGfilecharacteristics
            char* buffer = malloc(OGfileCharacteristics.st_size);//allocate proper size in buffer
            returnvalue = read (fd,buffer,OGfileCharacteristics.st_size); //reads all of the source file form the start to the end. 
            
            if(returnvalue == -1){ //error checking for reading source 
                printf("\n read() failed with error [%s]\n",strerror(errno)); //outputs error 
                return 1;
            }
            else{
                printf("\n read() source file successful\n");
                write(pipefd[1], buffer,OGfileCharacteristics.st_size);// write to pipe so that it can pass to parent
                close(pipefd[1]); //closes pipe since we wont be using it anymore
            }
        }
    }

    if(fq > 0){//checks if we are in the parent
        wait = waitpid(fq, NULL, 0); 
        fd = open (filepath, O_WRONLY);//checks if the file can be opened and can be read
        
        if (fd == -1){ //error checking
            printf("\n open() failed with error [%s]\n",strerror(errno)); 
            return 1; 
        }
        else{ //continue if no error
            fstat(fd,&OGfileCharacteristics); //takes info form file descriptor and write it to OGfilecharacteristics
            char* buffer = malloc(OGfileCharacteristics.st_size); //creates buffer of proper size
            returnvalue = read(pipefd[0],buffer,OGfileCharacteristics.st_size); //reads the text file
            
            fdErr = write(fd,parentBuffer,strlen(parentBuffer));//writes to file destination starting from buffer (start) to the end of the fd (bytes read)
            if(fdErr== -1){//error checking for file destination
                printf("\n write() failed with error [%s]\n",strerror(errno)); //error message
                return 1;
            }
            else{
                printf("\n write() destination file successful\n");
            }

            fdErrTwo = write(fd,buffer,OGfileCharacteristics.st_size);//writes to file destination starting from buffer (start) to the end of the fd (bytes read)

            if(fdErrTwo== -1){//error checking for file destination
                printf("\n write() failed with error [%s]\n",strerror(errno)); //error message
                return 1;
            }
            else{
                printf("\n write() destination file successful\n");
            }

            printf("\n File from %s has been successfully processed \n", filepath);
        }
    }
    return 0;
}