#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main(){
    int count = 0, matchSmoker = 0, tabaccoSmoker = 0, paperSmoker = 0, randNum = 0; 
    int agent, tobacco, paper, match, lock; //integer for semaphores
    int loopVal = 10; //integer for max number of loops

    agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //establish agent semaphore
    if (agent == -1){
        printf ("agent segmentation failed\n");
        return -1;
    }
    sem_create(agent, 0); //establish semaphore value to 0

    tobacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //establish tobacco semaphore
    if (tobacco == -1){
        printf ("tobacco segmentation failed\n");
        return -1;
    }
    sem_create(tobacco, 0); //establish semaphore value to 0

    paper = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //establish paper semaphore
    if (paper == -1){
        printf ("paper segmentation failed\n");
        return -1;
    }
    sem_create(paper, 0); //establish semaphore value to 0

    match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //establish match semaphore
    if (match == -1){
        printf ("match segmentation failed\n");
        return -1;
    }
    sem_create(match, 0); //establish semaphore value to 0

    lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //establish lock semaphore
    if (lock == -1){
        printf ("lock segmentation failed\n");
        return -1;
    }
    sem_create(lock, 1); //establish semaphore value to 1


    matchSmoker = fork(); //forking matchSmoker child
    if (matchSmoker == -1){ //checks for error in forking child
        printf("error fork1 was unsuccessful\n");//error print message
        return 1;
    }

    else if (matchSmoker == 0){ //checks if it is in matchSmoker child
        do
        {
            P(match); //decrement semaphore until agent releases it
            P(lock);
            printf("Smoker with match used the tabacco and paper\n\n");
            sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
            V(agent);
            V(lock);
        } while(1);
    }

    tabaccoSmoker = fork(); //forking tabaccoSmoker child
    if (tabaccoSmoker == -1){ //checks for error in forking child
        printf("error fork2 was unsuccessful\n");//error print message
        return 1;
    }
 
    else if (tabaccoSmoker == 0){ //checks if it is in tabaccoSmoker child
        do
        {
            P(tobacco); //decrement semaphore until agent releases it
            P(lock);
            printf("Smoker with tabacco used the match and paper\n\n");
            sleep(rand() % 3 + 1); //waits random interval until agent is triggered 
            V(agent);
            V(lock);
        } while(1);
    }

    paperSmoker = fork(); //forking paperSmoker child
    if (paperSmoker == -1){ //checks for error in forking child
        printf("error fork3 was unsuccessful\n");//error print message
        return 1;
    }

    else if (paperSmoker == 0){ //checks if it is in paperSmoker child
        do
        {
            P(paper); //decrement semaphore until agent releases it
            P(lock);
            printf("Smoker with paper used the tabacco and match\n\n");
            sleep(rand() % 3 + 1); //waits random interval until agent is triggered 
            V(agent);
            V(lock);
        } while(1);
    }

    if (matchSmoker > 0 && tabaccoSmoker > 0 && paperSmoker >0 ){ //checks if in parent process
        do
        {
            P(lock);
            randNum = rand() % 3 + 1; //creates random integer from 1 to 3 to determine which items are placed in table
            if (randNum == 1){
                printf("Agent places tobacco and paper on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                V(match); //release match semaphore
            }
            else if (randNum == 2){
                printf("Agent places tobacco and match on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                V(paper); //release paper semaphore
            }
            else if (randNum == 3){
                printf("Agent places match and paper on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                V(tobacco); //release tabacco semaphore
            }
            V(lock);
            P(agent);
            count++;
        }while(count < loopVal); //loops the parent code until it reaches 10
    }

    printf ("Exhange completed %i times\n", count); //lets user know the code is finished and how many transaction it completed
    return 0;
}