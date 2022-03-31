#include <stdio.h>
#include <fcntl.h>      
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Open input file with quiz grades 
    FILE* inputFile  = fopen("quiz_grades.txt","r"); 

    if (inputFile == NULL) { // Check for errors opening input file
        printf("File could not be found.\n"); 
        return 1; // Program terminates without any input
    }
    
    

    // Hard coded values based on input file
    int chapters = 2, homeworks = 2;
    int students = 10;
    int columns = chapters * homeworks;
    int grades[students][columns];

    for(int i = 0; i < students; i ++) {
        for(int j = 0; j < columns; j ++) {
            fscanf(inputFile, "%d", &grades[i][j]); // Save file contents in grades array
            printf("%d ", grades[i][j]); // Print file contents to stdout
            if((j + 1) % (columns) == 0) // if we reached the end of each column print new line
               printf("\n"); 
        }
    }
    
    fclose(inputFile); // Done reading input file
    
    // output file to print averages
    FILE* outputFile = fopen("quiz_averages.txt", "w");
    if (outputFile == NULL) // Check for errors opening output file
        printf("Error: Output file could not be found to write in!\n");

    int num_managers = chapters; // number of managers corresponds to how many chapters there are
    for(int i = 0; i < chapters; i++) { // loop to create managers equal to the number of chapters
        int manager = fork();
        if(manager < 0) { // error forking
            perror("fork");
            return 1;
        } if (manager == 0) { // manager successfully forked
            int num_workers = homeworks; // number of workers per manager
            for(int j = 0; j < homeworks; j ++) { // each manager creating workers equal to the number of homeworks for that chapter
                int worker = fork();
                if (worker < 0) { // check for error forking for each worker
                    perror("fork");
                    return 1;
                } else if (worker == 0) { // worker successfully forked
                    double sum = 0;
                    for(int row = 0; row < students; row ++) // Iterate down the column to get each students grade
                        sum += grades[row][(i*chapters) + j];
                    double avg = sum / students;
                    printf("Chapter: %d, Homework: %d, Average = %g / %d = %g\n", i + 1, j + 1, sum, students, avg); // Write to console
                    if(outputFile != NULL){ // Print to output file if available to open
                        fprintf(outputFile, "Chapter: %d, Homework: %d, Average = %g / %d = %g\n", i + 1, j + 1, sum, students, avg); // Write to output file
                    }
                    exit(0);
                }
            }
            while(num_workers > 0) { // managers wait for the workers
                wait(NULL);
                num_workers--;
            }
            exit(0);
        }
    }
    while(num_managers > 0) { // parent waits for the managers
        wait(NULL);
        num_managers--;
    }

    fclose(outputFile); // Close output file after writting
    return 0;
}