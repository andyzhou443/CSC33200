    /*
    [Step 2] Prcs_P2.c: Copy the contents of source.txt1 into destination1.txt and destination2.txt as per the following procedure.
    1. Read the next 100 characters from source.txt, and among characters read, replace each char- acter ’1’ with character ’L’ and all 
    characters are then written in destination1.txt
    2. Then the next 50 characters are read from source.txt, and among characters read, replace each character ’3’ with character ’E’ and 
    all characters are then written in destination2.txt.
    3. The previous steps are repeated until the end of file source.txt. The last read may not have 100 or 50 characters.
    Once you’re done with successful creation of executables for the above two steps do the following.
    Write a C program and call it Parent_Prcs.c. Execute the files as per the following procedure using exec system call.
    [1] source.txt is provided with the assignment.
    */
    
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h> 

int main(int argc, char* argv[]){

    int count; //integert to keep track of how many bytes passed by
    char* sourcefile = "source.txt";
    char* filename1 = "destination1.txt";
    char* filename2 = "destination2.txt";
    int file1Desc,file2Desc,sourceDesc,returnValue, destDescriptor, destDescriptor2;
    struct stat OGfileCharacteristics; //used for fstat
    char hundredBuffer[100]; //buffer for 100 char array
    char fiftyBuffer[50]; //buffer for 50 char array
    sourceDesc = access(sourcefile, F_OK); //checks existence of file

    if (sourceDesc == -1){ //if file descriptor returns error, print out error messege
        printf("\n access() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }   
    else{
        printf("\n file can be accessed\n");
    }

    destDescriptor = open (filename1, O_RDWR); //checks existence of file
    if (destDescriptor == -1){ //if file descriptor returns error, print out error messege
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }     
    else{
        printf("\n file can be open\n");
    }

    destDescriptor2 = open (filename2, O_RDWR); //checks existence of file
    if (destDescriptor2 == -1){ //if file descriptor returns error, print out error messege
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }   
    else{
        printf("\n file can be open\n");
    }

    sourceDesc = open (sourcefile, S_IRUSR);//checks if the file can be opened and can be read
    if (sourceDesc == -1){ //if file descriptor returns error, print out error messege
        printf("\n open() failed with error [%s]\n",strerror(errno)); 
        return 1; 
    }
    else{
        printf("\n file can be opened\n");
        
        fstat(sourceDesc,&OGfileCharacteristics); //takes info form file descriptor and write it to OGfilecharacteristics
    
        while (count <= OGfileCharacteristics.st_size){//loops through the whole file 
            returnValue = read (sourceDesc,hundredBuffer,100); //reads all of the source file form the start to the end. 

            for (int i = 0; i < 100; i ++){ //loops through 100 buffer
                if (hundredBuffer[i] == '1'){//checks if index value is 1, if it is change to L
                    hundredBuffer[i] = 'L';
                }
            }
            count = count + returnValue; //increment count by number of bytes read
            returnValue = write(destDescriptor,hundredBuffer,returnValue); //write to the file based on how many bytes read

            returnValue = read (sourceDesc,fiftyBuffer,50); //reads all of the source file form the start to the end. 
            for (int i = 0; i < 50; i ++){ //loops through the 50 buffer
                if (fiftyBuffer[i] == '3'){ //checks if index value is 3, if it is change to E
                    fiftyBuffer[i] = 'E';
                }
            }
            count = count + returnValue; //increment count by number of bytes read
            returnValue = write(destDescriptor2,fiftyBuffer,returnValue); //write to the file based on how many bytes read
        }

        return 0;
    }
}


