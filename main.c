// Arthur Knapp
// AK146316
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "globals.h"

int main(int argc, const char * argv[])
{
    FILE *configFile;
    FILE *queryFile;
    // Define file pointers for the config file and query file
    FILE *schemaFile;
    FILE *dataFile;
    // Define file pointers for the schema file and data file
    int relations;
    // Declare int to store the number of relations
    int i;
    // Counter for relations for loop
    int j = 0;
    // Counter for attributes for loop
    int tempOffset = 0;
    // Temp offset variable to compute location of each relation in attributes table
    char relName[NAME_SIZE];
    // Character array to store relation name
    char datName[19];
    // Character array to store relation.dat file name
    char schName[19];
    // Character array to store relation.sch file name
    
    
    //if (argc != ARGS)
    // If the number of arguments is not 3, close program.
    if (argc != 2)
    {
        fprintf(stderr, "Error: Incorrect Number Of Arguments\n");
        exit(1);
    }
    
    if ((configFile = fopen(argv[FIRST_ARG], "r")) == NULL)
    // If the config file doesn't open, close program
    {
        fprintf(stderr, "Error: Could Not Open Config File\n");
        exit(1);
    }
    
//    if ((queryFile = fopen(argv[SECOND_ARG], "r")) == NULL)
//    // If the query file dosen't open, close program
//    {
//        fprintf(stderr, "Error: Could Not Open Query File\n");
//        exit(1);
//    }
    
    fscanf(configFile, "%d", &relations);
    // Read the number of relations from the config file
    
    for (i = 0; i < relations; i++)
    // Loops through the config file 'relations' times to read all relations.
    // Declare int 'i' for counting iterations.
    {
        fscanf(configFile, "%s", relTable[i].name);
        // Read relation name into relName
        
        strcpy(datName, relTable[i].name);
        strcat(datName, ".dat");
        // Insert the relation name into data name, then append
        // '.dat' at the end for the name of the data file.
        // This will be used to open the data file for the proper relation.
        
        strcpy(schName, relTable[i].name);
        strcat(schName, ".sch");
        // Insert the relation name into schema name, then append
        // '.sch' at the end for the name of the schema file.
        // This will be used to open the schema file for the proper relation.
        
        if ((schemaFile = fopen(schName, "r")) == NULL)
        // If the schema file doesn't open, close program
        {
            fprintf(stderr, "Error: Could Not Open Schema File\n");
            exit(1);
        }
        
//        if ((dataFile = fopen(datName, "r")) == NULL)
//        // If the data file doesn't open, close progam
//        {
//            fprintf(stderr, "Error: Could Not Open Data File\n");
//            exit(1);
//        }
        
        fscanf(schemaFile, "%d", &relTable[i].numAttr);
        // Read the number of attributes from the schema file
        
        relTable[i].offset = j;
        tempOffset = j;
        
        for (; j < relTable[i].numAttr + tempOffset; j++)
        // Loops through the schema file 'numAttr' times to read all attributes.
        // Declare int 'j' for counting interations
        {
            fscanf(schemaFile, "%s ", attrTable[j].name);
            // Read attribute name from schema file and store it in attribute struct
            fscanf(schemaFile, "%c ", &attrTable[j].type);
            // Read attribute type from schema file and store it in attribute struct
            fscanf(schemaFile, "%d", &attrTable[j].size);
            // Read attribute size from schema file and store it in attribute struct
        }
    }
    
    // Following code is for testing purposes. This code prints out both tables
    // to test that the tables store the information properly.
    i = 0;
    j = 0;
    tempOffset = 0;
    
    while (i < relations)
    {
        printf("Relations Table:\n"); fflush(stdout);
        printf("Name: %s | ", relTable[i].name); fflush(stdout);
        printf("Offset: %d | ", relTable[i].offset); fflush(stdout);
        printf("NumAttr: %d\n", relTable[i].numAttr); fflush(stdout);
        
        printf("\n\n"); fflush(stdout);
        printf("Attributes Table:\n"); fflush(stdout);
        tempOffset = relTable[i].offset;
        
        while (j < relTable[i].numAttr + tempOffset)
        {
            printf("Name: %s | ", attrTable[j].name); fflush(stdout);
            printf("Type: %c | ", attrTable[j].type); fflush(stdout);
            printf("Size: %d\n", attrTable[j].size); fflush(stdout);
            j++;
        }
        
        printf("-----------------------------------------------------------\n\n\n"); fflush(stdout);
        i++;
    }
    return 0;
}

