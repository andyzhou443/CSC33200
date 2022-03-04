#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
    int value = atoi(argv[1]); //changes input char to int

    if (argc != 2){ //error if there is more than 2 args
        printf ("Error: There can only be one parameter"); //error message
        return 1;
    }

    int fq = 0, fr = 0, wait, wait2, total = 0, oddTotal =0, evenTotal=0; //variables for forks, wait, and total sums of calculations
    fq = fork(); //forks first child

    if (fq == -1){ //error if fork fails
        printf("error fork was unsuccessful\n"); //error message
        return 1;
    }

    if(fq == 0){//checks if we are in the child 
        printf("Adding the following even values:"); //message to show values
        for (int i = 2; i <= value; i +=2){ //outputting all the even values lower or equal to input
            printf("%i ", i); //prints out the added values
            evenTotal = evenTotal + i; //adds all values to evenTotal
        }
        printf("\n%i\n",evenTotal); //outputs the even sum

    }
    
    if(fq > 0){ //we are in the parent process
        wait = waitpid(fq, NULL, 0); //wait for first child to finish
        fr = fork();//forks second child in parent
        
        if (fr == -1){ //checks error in forking
            printf("error fork was unsuccessful\n"); //error message
            return 1;
        }

        if(fr == 0){//process in second child
            printf("Adding the following odd values:");
            for (int i = 1; i <= value; i +=2){ //increment through all the odd values that are equal or less than input
                printf("%i ", i); //prints all odd values
                oddTotal = oddTotal + i; //sum of all value
            }
            printf("\n%i \n",oddTotal); //outputs all the sume 
        }

        if (fr > 0){ // happens if we are in parent process
            wait2 = waitpid(fr, NULL, 0);//waits for second child to finish
            printf("Adding the all the values lower than the input:"); 
            for (int i = 1; i <= value; i++){//goes though all the values before and equal the input
                printf("%i ", i); //prints all the values
                total = total + i; //adds all the values to total
            }
            printf("\n%i\n",total); //prints out total
        }

    }
    return 0; 
}