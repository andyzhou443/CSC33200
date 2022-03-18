/*
Write a program where a child is created to execute command that tells you the date and time in Unix.
Use execl(...).
Note, you need to specify the full path of the file name that gives you date and time information. 
Announce the successful forking of child process by displaying its PID.
*/

#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int child, error, error2, wait;
    child = fork(); //forks the child
    wait = waitpid(child, NULL, 0); //wait for child to terminate

    if (child == -1){ //checks for error in forking child
        printf("error fork was unsuccessful\n");//error print message
        return 1;
    }

    if(child == 0){ //shows we are in child
        printf("I am child process my ID is: %d\n", getpid()); //announce the success in forking by displaying its pit
        execl("/usr/bin/date","/usr/bin/date", NULL); //launch the date command
        error = errno; //stores error message
        printf("EXECL Failed: %i\n", error); //if date command fails, this error message will execute
    
        return 0; 
    }

    if(child > 0){//shows we are in parent
        wait = waitpid(child, NULL, 0); //wait for child to terminate
        return 0;
    }
}