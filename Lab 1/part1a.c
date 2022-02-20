#include <stdio.h>
#include <unistd.h>
#include <errno.h> 

int main (int argc, char* argv[]) 
{ 
    char* filepath = argv[1]; 
    int returnval; 

    // Check file existence 
    returnval = access (filepath, F_OK); //checks if file can be accessed and if it exists
    if (returnval == 0) //if file descriptor is 0, there are no issues.
        printf ("\n %s exists\n", filepath); 
    else 
    { 
        if (errno == ENOENT) //if there is issues, checks errno with ENOENT (code for do not exist) and outputs the error
            printf ("%s does not exist\n", filepath); 
        else if (errno == EACCES) //if there is issues, checks errno with EACCES (code for cannot access) and outputs the error
            printf ("%s is not accessible\n", filepath); 
        return 0;
    } 
    
    // Check read access with filepath and if it has read permission
    returnval = access (filepath, R_OK); //check if file is accessible with read permission
    if (returnval == 0)//check for value 0 meaning if there are no issues
        printf ("\n %s read permissions is accessible \n" , filepath);
    else{
        printf ("\n %s read permissions is not accessible \n" , filepath);
    }
    // Check write access with filepath and if it has write permission
    returnval = access (filepath, W_OK); 
    if (returnval == 0) //if file descriptor is 0, there are no issues.
        printf ("\n %s write permissions is accessible \n" , filepath);
    else{
        printf ("\n %s write permissions is not accessible \n" , filepath);
    }

    return 0;
}