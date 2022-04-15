/*
There are n (n>1) students enrolled in a course. The course covers x number of
chapters from a textbook (x > 1).
In each chapter y number of homeworks are assigned (y>=1). The average grade for each
homework in all the chapters need to be found out.
To solve this, write program which has the main process as Director process, which
reads a file containing grades of all homeworks of all chapters and creates x number of
Manager processes. Each Manager process will take care of solving a chapter. Each
manager process will create y number of Worker process and pass marks of n students
to each of them and they calculate and print the average.
The input file should contain the data according to the value of x and y and n. For
example, the input text file and the process tree for x = 2 and y = 2 and n= 10 will look
like the following:
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include <errno.h>


int main(void){


    char* filepath = "quiz_grades.txt"; //directs the code to the readme.txt file
    int spaces = 0, newline = 0, newspace = 0, fd;
    int students = 0, managers = 0, workers = 2, columns = 0, average = 0;
    int managerfd = 0, workersfd = 0;
    int i = 0, j = 0;
    char str[100];
    char buffer[fd]; //buffer to hold all read 

    FILE* file = fopen("quiz_grades.txt", "r");//opens the file and make sure it is readable
    fd = open (filepath, S_IRUSR|S_IWUSR);//checks if the file can be opened and can be read and written
    if (fd == -1){ //if file descriptor returns error, print out error messege
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be opened\n");

        read (fd,buffer,sizeof(buffer)); //reads through all the file and inputs it into a buffer

        while (i < sizeof(buffer)){ //used to count how many newline
            if (buffer[i] == '\n'){
                newline++;
            } 
            i++;
        }
        
        while (i < sizeof(buffer)){ //used to count how many spaces
            if (buffer[i] == ' '){
                spaces++;
            } 
            i++;
        }
        spaces = spaces/(newline + 1); //adds 1 more since there is 1 unaccounted space


        columns = spaces + 1; //adds 1 more since there is 1 unaccounted column
        int columnDecrement = columns; //coutner for columns
        managers = columns/2; //assuming there are a manager for every two homeworks
        int managerDecrement = managers;//counter for manager
        students = newline + 1; //adds 1 more student since there is 1 unaccoutned student

        int stringStore;
        char *tempBuffer[2] = {0,0};
        int scoreArray[columns][students];//creating 2d array to store all grades

        for (int a = 0; a < students; a++){
            for (int b = 0; b < columns; b ++){
                fscanf(file, "%i", &scoreArray[a][b]); //creates 2d array containing grades
                printf("%i", scoreArray[a][b]);
            }
        }
        
        for(int x = 0; x < managers; x++){ //loops throught number of managers
            managerfd = fork();//create number of managers based on the amount needed
            if (managerfd == -1){// error message
                 printf("\n fork() failed with error [%s]\n",strerror(errno)); 
                return 1; 
            }
            if (managerfd == 0){ //checks if we are in child
                for (int y = 0; y < workers; y++){ // loops have manager create worker childs
                    workersfd = fork();
                    if (workersfd == -1){ //error message
                        printf("\n fork() failed with error [%s]\n",strerror(errno)); 
                        return 1; 
                    }
                    if (workersfd == 0){ //checks if we are in worker child
                        int total = 0, average = 0; //create the counters needed to calculate grades
                        for (int rowValue = 0; rowValue < students; rowValue++){ //incremet through the rows 
                            total = scoreArray[rowValue][y]; //calculates the grades 
                        }
                        average = total/students; //divides the sum of grades by total number of students
                        sprintf(tempBuffer, "%i", average); //turns average to 
                        printf ("Homework : %i, ", average); //prints out homework grades

                    } 

                }

                while (columns > 0){ //wait for the column childs the complete
                    wait(NULL);
                    columnDecrement--;
                }
            }
        }
        while (managers > 0){//wait for the manager childs the complete
            wait(NULL);
            managerDecrement--;
        }
        return 0;
    }
}
