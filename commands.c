// commands.c
// Arthur Knapp
// AK146316

// This file contains the functions for processing the commands from the query file. Following is
// information about each function.

// Functions:

// numberOfAttributes:
// This functions prints the number of attributes from a specified relation.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the number of attributes for that relation
// is printed. There is a flag called "foundRel" that is by default set to 0, and is set to 1 if the
// relation is found. If the flag is 0 after all of the relations are searched through, the function
// will print an error message stating that the relation was not found.

// tupleLength:
// This function prints the length of each tuple from a specified relation.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the length of the tuple will be calculated
// by looping through the attributes table and finding the sum of all attribute sizes. After the
// loop is completed, this value will be printed. There is a flag called "foundRel" that is by default
// set to 0, and is set to 1 if the relation is found. If the flag is 0 after all of the relations
// are searched through, the function will print an error message stating that the relation was not found.

// attributeInfo:
// This function prints the type (int or string) and the length of the specified attribute.
// It loops through the relation table comparing the relation from the query file with the relation
// name in the relation struct array. If the relation is found, the type and the length of the specified
// attribute will be found by looping through the attributes table and finding the specified attribute.
// Once it is found, the type and the length of the attribute will be printed. There are two flags called
// "foundRel" and "foundAttr". These flags will are set to 0 by default. If the relation and attribute
// specified are found, the flags will be set to 1. If they are not found, they will remain 0 and the
// function will print an error message for which flag remains 0.

// count:
// This function will compute and print the number of tuples in the specified relation. To find this value,
// the tuplen function will be called and will return the size of each tuple. After this value is found,
// the size of the data file for the specified relation will be found. This value will be found by using
// fseek to get to the end of the file and then using ftell to get the size. After the file size is found,
// the size of the data file will be divided by the value returned by tuplen(length of each tuple). There
// is a flag called "foundRel" that is by default set to 0, and is set to 1 if the relation is found. If
// the flag is 0 after all of the relations are searched through, the function will print an error message
// stating that the relation was not found.

// project:
// This function will print out all of the data for a specified attribute, without printing duplacates.
// To find this data the functionwill loop the relation and attributes tables until the specified information
// is found. While looping, a starting point for reading from the data file is being calculated by adding the
// current attribute size and storing it into an int variable. Using this starting point, the attributes from
// the data file will read. Each attribute will be stored into a linked list. While inserting the attributes
// into the linked list, the value being inserted will be compared to values already in the linked list to check
// for duplacates. If a duplacate is found, the attribute will not be added. There is a flag called "foundRel"
// that is by default set to 0, and is set to 1 if the relation is found. If the flag is 0 after all of the
// relations are searched through, the function will print an error message stating that the relation was not found.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"

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
        printf("Error: Relation Not Found\n"); fflush(stdout);
    }
}

int tupleLength(char *arg1, int countFlag)
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
            
            if (countFlag == 0)
            // Checks to see if tuplen was called from the query file and prints tuple size
            {
                printf("Length Of Tuple: %d\n", tupleSize); fflush(stdout);
            }
            
            foundRel = 1;
            // Set foundRel to 1 to signify finding the relation
        }
    }
    
    if (foundRel == 0)
    // Checks to see if the relation was not found and prints error message
    {
        printf("Error: Relation Not Found\n"); fflush(stdout);
    }
    
    if (countFlag == 0)
    // Checks if tuplen was called from the query file and returns zero
    {
        return 0;
    }
    
    else
    // If tuplen was called from numberOfTuples, return tuple size
    {
        return tupleSize;
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
                    printf("Attribute Type: %c\n", attrTable[j].type); fflush(stdout);
                    printf("Attribute Size: %d\n", attrTable[j].size); fflush(stdout);
                    
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
        printf("Error: Relation Not Found\n"); fflush(stdout);
    }
    
    if (foundAttr == 0)
    // Checks if foundAttr wasn't found and prints error message
    {
        printf("Error: Attribute Not Found\n"); fflush(stdout);
    }
}

void numberOfTuples(char *arg1, int countFlag)
{
    int i = 0;
    // Int variable to loop through the relations table
    int foundRel = 0;
    // Int variable to signify that the relation was found
    int dataSize;
    // Int variable to store the size of the data file
    int tupleSize;
    // Int variable to store the tuple size
    int tupleCount;
    // Int variable to store the number of tuples
    FILE *dataFile;
    // File pointer to reference the data file
    char datName[DATA_SIZE];
    // Character array to store relation.dat file name
    
    tupleSize = tupleLength(arg1, countFlag);
    
    for (; i < relations; i++)
    // Loops through relations table 'relations' times
    {
        if (strcmp(arg1, relTable[i].name) == 0)
        // Checks if the specified relation is in the relation table and opens data file
        {
            strcpy(datName, relTable[i].name);
            strcat(datName, ".dat");
            // Insert the relation name into data name, then append
            // '.dat' at the end for the name of the data file.
            // This will be used to open the data file for the proper relation.
            
            if ((dataFile = fopen(datName, "r")) == NULL)
            // If the data file doesn't open, close program
            {
                fprintf(stderr, "Error: Could Not Open Data File\n");
                exit(1);
            }
            
            fseek(dataFile, 0L, SEEK_END);
            // Set pointer to the end of the data file
            dataSize = (int)ftell(dataFile);
            // Insert the current position into dataSize
            
            tupleCount = dataSize / tupleSize;
            // Finds the number of tuples by dividing the size of the
            // data file by the size of each tuple
            
            printf("Number Of Tuples: %d\n", tupleCount); fflush(stdout);
            
            foundRel = 1;
            // Set foundRel to 1 to signify finding the relation
            
            fclose(dataFile);
            // Close data file
        }
    }
    
    if (foundRel == 0)
    // Checks if foundRel wasn't found and prints error message
    {
        printf("Error: Relation Not Found\n"); fflush(stdout);
    }
}

void project(char *arg1, char *arg2)
{
    int i = 0;
    // Int variable to loop through relations table
    int j;
    // Int variable to loop through attributes table
    int attrEnd;
    // Int variable to store the attributes loop condition
    int foundRel = 0;
    // Int variable to signify that the relation was found
    int foundAttr = 0;
    // Int variable to signify that the attribute was found
    int start = 0;
    // Int variable to store the start point of reading the data file
    int num;
    // Int variable to store an int from the data file
    FILE *dataFile;
    // File pointer to reference the data file
    char datName[DATA_SIZE];
    // Character array to store relation.dat file name
    char *data;
    // Character pointer for data from data file

    for (; i < relations; i++)
    // Loop through relations table 'relations' times
    {
        if (strcmp(arg1, relTable[i].name) == 0)
        // Checks if the specified relation is in the relation table and opens data file
        {
            attrEnd = relTable[i].offset + relTable[i].numAttr;
            // Calculates the attribute loop condition
            
            for (j = relTable[i].offset; j < attrEnd; j++)
            // Loop through attributes table 'attrEnd' times
            {
                if (strcmp(arg2, attrTable[j].name) == 0)
                // Checks if the specified attribute is in the attribute table
                {
                    strcpy(datName, relTable[i].name);
                    strcat(datName, ".dat");
                    // Insert the relation name into data name, then append
                    // '.dat' at the end for the name of the data file.
                    // This will be used to open the data file for the proper relation.
                    
                    if ((dataFile = fopen(datName, "r")) == NULL)
                    // If the data file doesn't open, close program
                    {
                        fprintf(stderr, "Error: Could Not Open Data File\n");
                        exit(1);
                    }
                    
                    fseek(dataFile, start, SEEK_SET);
                    // Set pointer to the spot to start reading from
                
                    if (attrTable[j].type == 'I')
                    {
                        while (fread(&num, attrTable[j].size, 1, dataFile) != 0)
                        {
                            LinkedListInt(num);
                            
                            start += tupleLength(arg1, 1);
                            fseek(dataFile, start, SEEK_SET);
                            // Set pointer to the spot to start reading from
                        }
                        
                        printListInt();
                        // Call function to print the list
                    }
                    
                    else
                    {
                        //printf("%d\n", attrTable[j].size);
                        data = malloc(sizeof(char) * attrTable[j].size);
                        // Allocate the size of the attribute to store the attribute
                        // information from the data file.
                        while (fread(data, attrTable[j].size, 1, dataFile) != 0)
                        {
                            //printf("%s\n", data);
                            LinkedListString(data);
                            
                            start += tupleLength(arg1, 1);
                            fseek(dataFile, start, SEEK_SET);
                            // Set pointer to the spot to start reading from
                        }
                        
                        printListString();
                        // Call function to print the list
                    }
                    
                    foundAttr = 1;
                    // Set foundAttr to 1 to signify finding the attribute
                }
                
                start += attrTable[j].size;
            }
            
            foundRel = 1;
            // Set fonudRel to 1 to signify finding the relation
        }
    }
    
    if (foundRel == 0)
    // Checks if foundRel wasn't found and prints error message
    {
        printf("Error: Relation Not Found\n"); fflush(stdout);
    }
    
    if (foundAttr == 0)
    // Checks if foundAttr wasn't found and prints error message
    {
        printf("Error: Attribute Not Found\n"); fflush(stdout);
    }
    
    else
    // If the attritbute was found, close the data file
    {
        fclose(dataFile);
        // Close data file
    }
}