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
#include <string.h>
#include <errno.h>


int main(int argc, char* argv[]){

    char* source = argv[1];
    int error;
    int manager, worker, chapter, grade;



    return 0;
}
