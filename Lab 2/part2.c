#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (void){
    //parent P
    int a = 10, b = 25, fq = 0, fr = 0, wait, wait2;
    fq = fork(); //forks the first child

    if (fq == -1){ //checks for error in forking first child
        printf("error fork was unsuccessful\n");//error print message
        return 1;
    }

    if(fq == 0){ //shows we are in child Q
        a = a + b; //adds a and b and stores it in a
        printf("Process Q a = %i, b = %i , PID = %i\n" , a, b, getpid());//print message

        fr = fork();//forks second child inside child 1
        
        if (fr == -1){ //error in forking
            printf("error fork was unsuccessful\n"); //error message
            return 1;
        }

        else if (fr != 0){ //checks if we are not in child
            b = b + 20; //calculations for B
            printf("Process R a = %i, b = %i , PID = %i\n", a,b,getpid()); //error message
        }

        else{ //happens in child Q only
            a=(a*b)+30; //calculations for child Q for 
            printf("Process Q a = %i, b = %i , PID = %i\n", a,b,getpid()); //print message
        }
    }

    else{//calculations for parent process
        b=a+b-5;//calculations for the parent process
        printf("a = %i, b = %i , PID = %i\n", a,b,getpid());//print message
    }
    wait = waitpid(fq, NULL, 0); //wait for child 1 to terminate
    wait2 = waitpid(fr, NULL, 0); //wait for child 2 to terminate
    return 0;
} 