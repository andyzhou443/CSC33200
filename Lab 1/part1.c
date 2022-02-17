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

int main (int argc, char* argv[]){

    char* filepath = argv[1]; 
    int returnval;
    returnval = access(filepath, F_OK);

    returnval = open (filepath,);

    if (returnval == 0)//condition for file can't be opened
        printf("%s file cannot be opened\n");

    return 0;
}