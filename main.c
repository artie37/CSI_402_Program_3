// Arthur Knapp
// AK146316
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

int main(int argc, const char * argv[])
{
    FILE *configFile;
    FILE *queryFile;
    // Define file pointers for the config file and query file
    
    if (argc != ARGS)
    // If the number of arguments is not 3, close program.
    {
        fprintf(stderr, "Error: Incorrect Number Of Arguments\n");
        exit(1);
    }
    
    if ((configFile = fopen(argv[FIRST_ARG], "r")) == NULL)
    {
        fprintf(stderr, "Error: Could Not Open configfile\n");
        exit(1);
    }
    
    if ((queryFile = fopen(argv[SECOND_ARG], "r")) == NULL)
    {
        fprintf(stderr, "Error: Could Not Open queryfile\n");
        exit(1);
    }
    
    
    
    return 0;
}

