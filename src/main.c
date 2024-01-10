#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>


#include "utils/file_to_string.h"

int main(int argc,char **argv)
{
    FILE *f;
    //error argument
    if (argc < 2 || argc > 4)
    {   
        err(-1,"too few arguments to function");
    }
    //check if there is a file
    if (argc < 3 && (f = fopen(argv[1],"r")) != NULL)
    {
        char *to_evaluate = file_to_string(f);
        fclose(f);
        free(to_evaluate);
    }
    // just a string 
    if else
    {
        if(strcmp("-c",argv[1]) != 0)
        {
            err(-1,"wrong argument");
        }
    }
    // have to do stdin 
    return 0;
}
