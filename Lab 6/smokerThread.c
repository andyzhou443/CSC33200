
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count = 0, randNum = 0; //counter for loop and random interval
    int loopVal = 10; //max number of loops
pthread_mutex_t agent, tobacco, paper, match, lock; //create proper mutex to control threads

void* MatchSmokerRoutine (){ //Routine for smoker with match to get tabacco and paper
    do
    {
        pthread_mutex_lock(&match); //locks match mutex to stop it from triggering
        pthread_mutex_lock(&lock);
        printf("Smoker with match use tabacco and paper\n\n");
        sleep(rand() % 3 + 1); //waits random interval until agent is triggered 
        pthread_mutex_unlock(&agent); //allows agent to continue placing items
        pthread_mutex_unlock(&lock);
    } while(1);
}

void* TabaccoSmokerRoutine (){ //Routine for smoker with tabacco to get match and paper
    do 
    {
        pthread_mutex_lock(&tobacco); //locks tobacco mutex to stop it from triggering
        pthread_mutex_lock(&lock);
        printf("Smoker with tabacco use match and paper\n\n");
        sleep(rand() % 3 + 1); //waits random interval until agent is triggered 
        pthread_mutex_unlock(&agent); //allows agent to continue placing items
        pthread_mutex_unlock(&lock);
    } while(1);
}

void* PaperSmokerRoutine (){ //Routine for smoker with paper to get match and tabacco
    do
    {
        pthread_mutex_lock(&paper); //locks paper mutex to stop it from triggering
        pthread_mutex_lock(&lock);
        printf("Smoker with paper use tabacco and match\n\n");
        sleep(rand() % 3 + 1); //waits random interval until agent is triggered 
        pthread_mutex_unlock(&agent); //allows agent to continue placing items
        pthread_mutex_unlock(&lock);
    } while(1);
}

void* AgentRoutine(){
    do
        {   
            pthread_mutex_lock(&lock); 
            randNum = rand() % 3 + 1; //generates random interview to choose what items are placed on table
            if (randNum == 1){
                printf("Agent places tobacco and paper on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                pthread_mutex_unlock(&match); //unlockes match mutex which triggers smoker with match
            }
            else if (randNum == 2){
                printf("Agent places tobacco and match on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                pthread_mutex_unlock(&paper); //unlockes paper mutex which triggers smoker with match
            }
            else if (randNum == 3){
                printf("Agent places match and paper on table\n");
                sleep(rand() % 3 + 1); //waits random interval until smoker is triggered 
                pthread_mutex_unlock(&tobacco); //unlockes tabacco mutex which triggers smoker with match
            }
            pthread_mutex_unlock(&lock);
            pthread_mutex_lock(&agent); //locks agent until smoker obtains items
            count++;
        }while(count < loopVal); //loops the process until it reaches 10 times
}

int main(){

    //initialize mutex to control locking and unlocking
    pthread_mutex_init(&agent, NULL);
    pthread_mutex_init(&tobacco, NULL);
    pthread_mutex_init(&paper, NULL);
    pthread_mutex_init(&match, NULL);
    pthread_mutex_init(&lock, NULL);

    //locks mutex before code starts
    pthread_mutex_lock(&match); 
    pthread_mutex_lock(&paper);
    pthread_mutex_lock(&tobacco);
    pthread_mutex_lock(&agent);

    //creates the appropriate pthreads and match it with its respective routines
    pthread_t matchSmoker;
    pthread_create(&matchSmoker, NULL, MatchSmokerRoutine, NULL);


    pthread_t tabaccoSmoker;
    pthread_create(&tabaccoSmoker, NULL, TabaccoSmokerRoutine, NULL);


    pthread_t paperSmoker;
    pthread_create(&paperSmoker, NULL, PaperSmokerRoutine, NULL);

    pthread_t agentThread;
    pthread_create(&agentThread, NULL, AgentRoutine, NULL);
    pthread_join(agentThread, NULL); //waits for agentthread to terminate 

    //destroys all mutex to free memory
    pthread_mutex_destroy(&agent);
    pthread_mutex_destroy(&tobacco);
    pthread_mutex_destroy(&paper);
    pthread_mutex_destroy(&match);
    pthread_mutex_destroy(&lock);

    printf ("Exhange completed %i times\n", count); //lets user know the code is finished and how many transaction it completed
    return 0;
}