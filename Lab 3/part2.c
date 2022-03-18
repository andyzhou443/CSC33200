/*
Write a program where a child is created to execute a command that shows all files 
(including hid- den files) in a directory with information such as permissions, owner, size, and when last modified.
Use execvp(...).
For the command to list directory contents with various options, refer the handout on Unix file system sent to you in the first class.
Announce the successful forking of child process by displaying its PID.
*/

#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int child, error, wait;
    char* command = "ls"; //input command
    char* args[3] = {"ls","-la", NULL};//input command as well as its extensions
    child = fork(); //forks the child

    if (child == -1){ //checks for error in forking child
        printf("error fork was unsuccessful\n");//error print message
        return 1;
    }

    if(child == 0){ //shows we are in child
        printf("I am child process my ID is: %d\n", getpid()); //announce the success in forking by displaying its pit
        execvp(command,args); //launch the ls -la comand
        error = errno;
        printf("EXECL Failed: %i\n", error); //if date command fails, this error message will execute
    
        return 0; 
    }

    if(child > 0){ //shows are we in parent
        wait = waitpid(child, NULL, 0); //wait for child to terminate
        return 0;
    }
}