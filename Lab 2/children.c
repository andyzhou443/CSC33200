#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (void){

    int child1,child2,PID1,PID2,wait1,wait2;
    child1 = fork(); //creates first child
    
    if (child1 == -1){ //checks if creating the first child results in error
        printf("error fork was unsuccessful\n");//print error message
        return 1;
    }

    else if (child1 == 0) //happens if its in child
    {
        PID1 = getpid(); //variable stores childs PID
        printf("I am child one, my pid is: %i \n", PID1); //print message
        return 1;
    }

    else if (child1 > 0){ //checks if we are in the parent
        wait1 = waitpid(child1, NULL, 0); //waits for first child to terminate 
        child2 = fork(); //forks second child after confirming we are in parent
        wait2 = waitpid(child2, NULL, 0); //waits for second child to terminate
        if (child2 == -1){ //error message if forking fails
            printf("error fork was unsuccessful\n");
            return 1;
        }    

        else if (child2 == 0) //shows we are in child2
        {
            PID2 = getpid(); //variable stores child2s PID
            printf("I am child two, my pid is: %i \n", PID2);//print message
        }
    }
    return 0;
}