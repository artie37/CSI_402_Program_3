// commands.c
// Arthur Knapp
// AK146316

// This file contains the functions for processing the commands from the query file

// Functions:
// numberOfAttributes: This functions prints the number of attributes from a specified relation.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the number of attributes for that relation
// is printed. There is a flag called "foundRel" that is by default set to 0 and is set to 1 if the
// relation is found. If the flag is 0 after all of the relations are search through, the function
// will print an error message stating that the relation was not found.

// tupleLength: This function prints the length of each tuple from a specified relation.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the length of the tuple will be calculated
// by looping through the attributes table and finding the sum of all attribute sizes. After the
// loop is completed, this value will be printed. There is a flag called "foundRel" that is by default
// set to 0 and is set to 1 if the relation is found. If the flag is 0 after all of the relations
// are search through, the function will print an error message stating that the relation was not found.

// attributeInfo: This function prints the type (int or string) and the length of the specified attribute.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the type and the length of the specified
// attribute will be found by looping through the attributes table and finding the specified attribute.
// Once it is found, the type and the length of the attribute will be printed. There are two flags called
// "foundRel" and "foundAttr". These flags will are set to 0 by default. If the relation and attribute
// specified are found, the flags will be set to 1. If they are not found, they will remain 0 and the
// function will print an error message for which flag remains 0.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
//#include "globals.h"
#include "externs.h"


void numberOfAttributes(char *arg1)
{
    int i = 0;
    // Int variable to loop through relations table
    int foundRel = 0;
    // Int variable to signify that the relation is found
    
    for (; i < relations; i++)
    // Loops through the relation struct array 'relations' times
    {
        if (strcmp(arg1, relTable[i].name) == 0)
        // Checks to see if the desired relation name is found and prints
        // the number of attributes.
        {
            printf("Number Of Attributes: %d\n", relTable[i].numAttr); fflush(stdout);
            foundRel = 1;
            // Set foundRel to 1 to signify finding the relation
        }
    }
    
    if (foundRel == 0)
    // Checks to see if the relation was not found and prints an error message
    {
        printf("Error: Relation Not Found For numattr\n"); fflush(stdout);
    }
}

void tupleLength(char *arg1)
{
    int i = 0;
    // Int variable to loop through relations table
    int j;
    // Int variable to loop through attributes table
    int attrEnd;
    // Int variable to store the attributes loop condition
    int foundRel = 0;
    // Int variable to signify that the relation is found
    int tupleSize = 0;
    // Int variable to store the total tuple size
    
    for (; i < relations; i++)
    // Loops through the relations struct array 'relations' times
    {
        if (strcmp(arg1, relTable[i].name) == 0)
        // Checks to see if the relation is found and finds tuple size
        {
            attrEnd = relTable[i].offset + relTable[i].numAttr;
            // Calculates attribute loop condition
            
            for (j = relTable[i].offset; j < attrEnd; j++)
            // Loops through the attributes table 'attrEnd' times and sums tuple size
            {
                tupleSize += attrTable[j].size;
            }
            
            printf("Length Of Tuple: %d\n", tupleSize);
            foundRel = 1;
            // Set foundRel to 1 to signify finding the relation
        }
    }
    
    if (foundRel == 0)
    // Checks to see if the relation was not found and prints error message
    {
        printf("Error: Relation Not Found For tuplen\n");
    }
}

void attributeInfo(char *arg1, char *arg2)
{
    int i = 0;
    // Int variable to loop through relations table
    int j;
    // Int variable to loop through attributes table
    int attrEnd;
    // Int variable to store the attributes loop condition
    int foundRel = 0;
    // Int variable to signify that the relation is found
    int foundAttr = 0;
    // Int variable to signify that the attribute is found
        
    for (; i < relations; i++)
    // Loops through the relations struct 'relations' times
    {
        if (strcmp(arg1, relTable[i].name) == 0)
        // Checks to see if the relation is found and loops through attributes
        {
            attrEnd = relTable[i].offset + relTable[i].numAttr;
            // Calculates attribute loop condition
            
            for (j = relTable[i].offset; j < attrEnd; j++)
            // Loops through the attributes table 'attrEnd' times and finds type and size
            {
                if (strcmp(arg2, attrTable[j].name) == 0)
                // Checks to see if the attribute is found and prints the attribute type and size
                {
                    printf("Attribute Type: %c\n", attrTable[j].type);
                    printf("Attribute Size: %d\n", attrTable[j].size);
                    
                    foundAttr = 1;
                    // Set foundAttr to 1 to signify finding attribute
                }
            }
            
            foundRel = 1;
            // Set foundRel to 1 to signify finding relation
        }
    
    }
    
    if (foundRel == 0)
    // Checks if foundRel wasn't found and prints error message
    {
        printf("Error: Relation Not Found\n");
    }
    
    if (foundAttr == 0)
    // Checks if foundAttr wasn't found and prints error message
    {
        printf("Error: Attribute Not found\n");
    }
}