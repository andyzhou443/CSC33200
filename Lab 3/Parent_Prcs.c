#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (void){
    //parent P
    int child1 = 0, child2 = 0, error, wait, wait2;
    child1 = fork(); //forks the first child

    if (child1 == -1){ //checks for error in forking first child
        printf("error fork was unsuccessful\n");//error print message
        return 1;
    }

    if(child1 == 0){ //shows we are in child 1
        execl("Prcs_P1", "Prcs_P1", NULL); //executes the Prcs_P1 program
        error = errno;
        printf("EXECL Failed: %i\n", error); //if date command fails, this error message will execute
        return 0;
    }

    if(child1 > 0){//shows that we are in parent
        wait = waitpid(child1, NULL, 0); //wait for child to terminate
        child2 = fork(); //creates child 2
        if (child2 == -1){ //checks for error in forking child 2
            printf("error fork was unsuccessful\n");//error print message
            return 1;
        }

        if(child2 == 0){ //shows we are in child 2
            execl("Prcs_P2", "Prcs_P2", NULL); //executes the Prcs_P2 program
            error = errno;
            printf("EXECL Failed: %i\n", error); //if date command fails, this error message will execute
        }

        if(child2 > 0){ //shows we are in parent
            wait2 = waitpid(child2, NULL, 0); //waits for child2 to finish
            return 0;
        }
    }
}