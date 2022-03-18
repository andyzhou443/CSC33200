/*
Prcs_P1.c: Create two files namely, destination1.txt and destination2.txt with read, write, and execute permissions.

[Step 2] Prcs_P2.c: Copy the contents of source.txt1 into destination1.txt and destination2.txt as per the following procedure.
1. Read the next 100 characters from source.txt, and among characters read, replace each char- acter ’1’ with character ’L’ and all 
characters are then written in destination1.txt
2. Then the next 50 characters are read from source.txt, and among characters read, replace each character ’3’ with character ’E’ and 
all characters are then written in destination2.txt.
3. The previous steps are repeated until the end of file source.txt. The last read may not have 100 or 50 characters.
Once you’re done with successful creation of executables for the above two steps do the following.
Write a C program and call it Parent_Prcs.c. Execute the files as per the following procedure using exec system call.
[1] source.txt is provided with the assignment.

[Step 3] Using fork create a child process, say Child 1 that executes Prcs_P1. This will create two destination files according to Step 1.

[Step 4] After Child 1 finishes its execution, use fork to create another child process, say Child 2 and execute
Prcs_P2 that accomplishes the procedure described in Step 2.
*/

#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h> 

int main(int argc, char* argv[]){

    char* filename1 = "destination1.txt"; 
    char* filename2 = "destination2.txt";
    int file1Desc,file2Desc;

    //Prcs_P1.c: Create two files namely, destination1.txt and destination2.txt with read, write, and execute permissions.
    file1Desc = creat(filename1, 0777); //create destination file with all privliges
    if (file1Desc == -1){ //if file descriptor returns error, print out error messege
        printf("\n creat() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file1 created\n");
    }

    file2Desc = creat(filename2, 0777); //create destination file with all privliges
    if (file2Desc == -1){ //if file descriptor returns error, print out error messege
        printf("\n creat() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file2 created\n");
    }

}