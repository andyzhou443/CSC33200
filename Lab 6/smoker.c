#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main(){
    int count = 0, pid =0, randNum = 0;
    int agent, tobacco, paper, match, lock;
    int counter = 10;

    agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (agent == -1){
        printf ("agent segmentation failed\n");
        return -1;
    }
    sem_create(agent, 0);

    tobacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (tobacco == -1){
        printf ("tobacco segmentation failed\n");
        return -1;
    }
    sem_create(tobacco, 0);

    paper = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (paper == -1){
        printf ("paper segmentation failed\n");
        return -1;
    }
    sem_create(paper, 0);

    match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (match == -1){
        printf ("match segmentation failed\n");
        return -1;
    }
    sem_create(match, 0);

    lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (lock == -1){
        printf ("lock segmentation failed\n");
        return -1;
    }
    sem_create(lock, 1);



}