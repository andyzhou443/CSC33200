#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (int argc, char* argv[]){

    int child, error;

    // create a big array that stores what the user puts in
    // index 1 of the array goes into command
    //all values of the array goes into args with a NULL at the end
    char input[1000];
    char firstInput[500];

    char* command; //input command
    char commandDeref = *command;
    char* args[] = {input, NULL};//input command as well as its extensions
    

    child = fork(); //forks the child

    if (child == -1){ //checks for error in forking child
        printf("error fork was unsuccessful\n");//error print message
        return 1;
    }

    if(child == 0){ //shows we are in child
        while (1){
            printf("command: ");
            scanf("%s", input); //takes user input and puts it into input
            breakArray(input);

            getCommand(commandDeref,input);

            if (strcmp(input,"exit") == 1){
                exit(0);
            }
            execvp(command,args); //V for curre
            error = errno;
            printf("EXECL Failed: %i\n", error); //if date command fails, this error message will execute
        
            if strcmp(command,"exit");
        }
        return 0; 

    }

    if(child > 0){ //shows are we in parent
        waitpid(child, NULL, 0); //wait for child to terminate
        return 0;
    }
}