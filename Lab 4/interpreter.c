#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    char command[128];
    char* argument;
    int child;    

    printf("\n➜ "); //first command input
    scanf(" %[^\n]s", command); // scan first user input, %[^\n]s allows for whitespaces

    while(strcmp(command, "quit")) { //loop will terminate when user enters "quit"
        char* flagArray[5];
        argument = strtok(command, " "); // command line flags/arguments happen after space, so split the input after the space
        int index = 0; // Index counter for command array
        
        while(argument != NULL) { 
            flagArray[index++] = argument; // Insert into into current index in array and increment index
            argument = strtok(NULL, " "); // Seperate string at next space
        }
        
        child = fork();
        if (child == 0) { // Child successfully forked
	  	    execvp (flagArray[0], flagArray);
	  	    printf ("EXECVP Failed\n");
        }
        
        wait(NULL); // wait for child process
        printf("\n➜ "); //gets ready for next command input
        scanf(" %[^\n]s", command); // scans next user input
        
    }      
    printf("\nQuiting....\n");
    return 0;
}
