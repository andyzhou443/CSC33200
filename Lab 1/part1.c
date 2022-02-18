/*UNIX cat command has three functions with regard to text files: displaying them, combining copies of them and creating new ones.
Write a C program to implement a command called displaycontent that takes a (text) file name as argument and display its contents. 
Report an appropriate message if the file does not exist or can’t be opened (i.e. the file doesn’t have read permission). 
ou are to use open(), read(), write() and close() system calls.
NOTE: Name your executable file as displaycontent and execute your program as ./displaycontent file_name
*/

#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 
#include <errno.h>
#include <unistd.h>

int main (int argc, char* argv[]){

    char* filepath = argv[1]; 
    int fd;
    char buffer[fd];

    fd = access(filepath, F_OK); //checks existence of file
    if (fd == -1){
        printf("\n access() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be accessed\n");
    }

    fd = open (filepath, S_IRUSR);//checks if the file can be opened and can be read
    if (fd == -1){
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be opened\n");

        fd = read (fd,buffer,sizeof(buffer));
        printf("\n%s", buffer);
        printf("\n");
    
        close(fd);
    }

    
    //negative means call failed
    //positive is pass
    //
    return 0;
}