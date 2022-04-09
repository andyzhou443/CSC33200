/*
Write a special simple command interpreter that takes a command and its arguments.
This interpreter is a program where the main process creates a child process to execute
the command using exec() family functions. After executing the command, it asks for
a new command input ( parent waits for child). The interpreter program will get
terminated when the user enters exit.

LOGIC:
Parent
 - reading the whole command (all the spaces , |, etc.)
 - into one giant string
 - split the string into little bits
    - split based on |
    - each fragment is passed to a child
 - spawn n children (where n is the number of fragments)
 - waitpid for child to exit
 - giant while loop
 - set up the file descriptors as pipes for children to read from (stdout -> stdin) AKA USE DUP
 - "exit"

Child
 - parsing whatever the parent gives in
 - parses based on the first space
 - prepare command, args this way
 - reads from the pipes that the parents gives it
 - exec command

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main (void){

    int child, child2, error;

    // create a big array that stores what the user puts in
    // index 1 of the array goes into command
    //all values of the array goes into args with a NULL at the end
    char input[64];
    char* command, command2; //input command
    
    while (1){
        char* executeableInfo[64];
        for(int i = 0; i < 64; i++)
            executeableInfo[i] = 0;
        int counter = 0, counter2 = 0;
        printf("command: ");
        scanf(" %[^\n]s", input); //scan until it reaches new line

        if(strcmp(input,"exit") ==0)
            exit(0);
        

        if(strchr(input, '|') != NULL){ //checks if string contains |
            command = strtok (input, " ");
            char* executeableInfoTwo[64];
            for(int i = 0; i < 64; i++)
                executeableInfoTwo[i] = 0;
                
            int pipefd[2];
            if (pipe(pipefd) == -1){
                printf("error pipe was unsuccessful\n");//error print message
                return 1;
            }
            char* pieceOne = strtok(input,"|"); //split 
            char* pieceTwo = strchr(&input,'\0') + 3;

            while (pieceOne != NULL){
                executeableInfo[counter] = pieceOne;
                pieceOne = strtok (NULL, " ");
                counter++;
            }

            while (pieceTwo != NULL){
                executeableInfoTwo[counter2] = pieceTwo;
                pieceTwo = strtok (NULL, " ");
                counter2++;
            }
            child = fork();
            if (child == -1){ //checks for error in forking child
                printf("error fork was unsuccessful\n");//error print message
                return 1;
            }

            if(child == 0){ //shows we are in child

                //dup sending end of pipe to stdoutput using dup
                dup2(pipefd[1], 1);

                execvp(executeableInfo[0], executeableInfo); 
                error = errno;
                printf("EXECL Failed: %s\n", strerror(error)); //if date command fails, this error message will execute


            }

            if (child > 0){
                child2 = fork(); 
                if (child2 == -1){ //checks for error in forking child
                    printf("error fork was unsuccessful\n");//error print message
                    return 1;
                }

                if(child2 == 0){ //shows we are in child
                    waitpid(child, NULL, 0); //NOT SURE IF THIS IS LEGALLLLLLLLLLLL
                    close(1);
                    dup2(pipefd[0], 1);
                    //using dup to reference file despitor at the recieving end of the pipe to stdinput

                    execvp(executeableInfoTwo[0], executeableInfoTwo); 
                    error = errno;
                    printf("EXECL Failed: %s\n", strerror(error)); //if date command fails, this error message will execute


                    //NEED TO MAKE SURE CHILD passes to CHILD2
                    //USE DUP AND WELL AS PIPEs

                
                return 0;
                }
                if (child > 0 && child2 > 0){
                    waitpid(child, NULL, 0);
                    waitpid(child2, NULL, 0);
                }
            }

            
        }
        else{
            command = strtok (input, " ");
            while (command != NULL){
                executeableInfo[counter] = command;
                command = strtok (NULL, " ");
                counter++;
            }

            child = fork(); //forks the child

            if (child == -1){ //checks for error in forking child
                printf("error fork was unsuccessful\n");//error print message
                return 1;
            }

            if(child == 0){ //shows we are in child
                execvp(executeableInfo[0], executeableInfo); 
                error = errno;
                printf("EXECL Failed: %s\n", strerror(error)); //if date command fails, this error message will execute
            }

            if(child > 0){ //shows are we in parent
                if(strchr(input,'|')){
                    waitpid(child2, NULL, 0);
                }
                waitpid(child, NULL, 0); //wait for child to terminate
            }
        }
    }
    return 0;
}