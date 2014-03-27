// linked_list.c
// Arthur Knapp
// AK146316

// Functions:

// linkedListString:
// A function that inserts strings into a linked list. If the string being entered is the first string being entered,
// the function createNewListString is called. Before insertion, the string being entered is commpared to each string
// in the list to see if the current string is a duplicate. If it is a duplicate, the string is not entered.

// linkedListInt:
// Exactly the same as LinkedListString except it handles an int instead of a string.

// createNewListString:
// Creates a new list list by allocating memory to a new node. After the node is created, make the node
// point to null. This signifies that it is the last node in the list. After that, insert the string into
// the new node the have the new node, head, and tail point to each other.

// createNewListInt:
// Exactly the same as createNewListString excepti it handles an int instead of a string.

// printListString:
// Have the head node point to the temperary node pointer pCurr. Loop through the list with pCurr until
// pCurr == NULL, meaning the end of the linked list is reached. Print the string with each iteration of
// the loop.

// printListInt:
// Exactly the same as printListString except it handles an int instead of a string.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"

Node *pHead = NULL;
Node *pTail = NULL;

void linkedListString(char *attrName)
{
    if (pHead == NULL)
    // Checks to see if the head node is pointing to null and calls 'createNewList'.
    // If the head node is pointing to null, the list is empty and a new list must be created.
    {
        createNewListString(attrName);
    }
    
    else
    // Runs if the list is not empty and inserts the new node at the end of the list
    {
        Node *pNewNode = malloc(sizeof(Node));
        // Creates new node to be inserted into the list
        Node *pCurr = pHead;
        // Creates node to loop through linked list
        pNewNode -> name = malloc(strlen(attrName));
    
        strcpy(pNewNode -> name, attrName);
        // Insert the string into the new node
        
        if (pHead == pTail)
        // Checks to see if the new node is going to be the second node in the list.
        // If head and tail are the same, there is only one node.
        {
            if (strcmp(pHead -> name, attrName) == 0)
            // If the string about to be inserted into the list equals the string in
            // the head node, do nothing. This will eliminate duplicate entries.
            {}
            
            else
            // Inserts the new node if the current string does not equal to the head node
            {
                pHead -> next = pNewNode;
                // Head node points to the new node
                pTail = pNewNode;
                // Insert the new node into tail
                pNewNode -> next = NULL;
                // Remove the new node from the list
            }
        }
        
        else
        // If the new node is not the second node
        {
            while (pCurr != NULL)
            // Loop through list to insert node
            {
                if (strcmp(pCurr -> name, attrName) == 0)
                // If the string about to be inserted into the list equals the string in
                // the current node, break out of loop. This will eliminate duplicate entries.
                {
                    break;
                }
                
                else if (pCurr -> next == NULL)
                // If the current node points to null, insert the current node
                {
                    pTail -> next = pNewNode;
                    // Point the tail node to the new node
                    pNewNode -> next = NULL;
                    // Remove the new node from the list
                    pTail = pNewNode;
                    // Insert the new node into tail
                }
                
                pCurr = pCurr -> next;
                // Move to next node
            }
        }
    }
}

void linkedListInt(int attrNum)
{
    Node *pNewNode = malloc(sizeof(Node));
    // Creates new node to be inserted into the list
    Node *pCurr = pHead;
    // Creates node to loop through linked list
    
    if (pHead == NULL)
    // Checks to see if the head node is pointing to null and calls 'createNewList'.
    // If the head node is pointing to null, the list is empty and a new list must be created.
    {
        createNewListInt(attrNum);
    }
    
    else
    // Runs if the list is not empty and inserts the new node at the end of the list
    {
        if (pHead == pTail)
        // Checks to see if the new node is going to be the second node in the list.
        // If head and tail are the same, there is only one node.
        {
            if (pHead -> num == attrNum)
            // If the number about to be inserted into the list equals the number in
            // the head node, do nothing. This will eliminate duplicate entries.
            {}
            
            else
            // Inserts the new node if the current string does not equal to the head node
            {
                pNewNode -> num = attrNum;
                // Insert the number into the new node
                pHead -> next = pNewNode;
                // Head node points to the new node
                pTail = pNewNode;
                // Insert the new node into tail
                pNewNode -> next = NULL;
                // Remove the new node from the list
            }
        }
        
        else
        // If the new node is not the second node
        {
            while (pCurr != NULL)
            // Loop through list to insert node
            {
                if (pCurr -> num == attrNum)
                // If the number about to be inserted into the list equals the number in
                // the current node, break out of loop. This will eliminate duplicate entries.
                {
                    break;
                }
                
                else if (pCurr -> next == NULL)
                // If the current node points to null, insert the current node
                {
                    pNewNode -> num = attrNum;
                    // Insert the number into the new node
                    pTail -> next = pNewNode;
                    // Point the tail node to the new node
                    pNewNode -> next = NULL;
                    // Remove the new node from the list
                    pTail = pNewNode;
                    // Insert the new node into tail
                }
                
                pCurr = pCurr -> next;
                // Move to next node
            }
        }
    }
}

void createNewListString(char *attrName)
{
    Node *pNewNode = malloc(sizeof(Node));
    // Creates new node to be inserted into the list
    pNewNode -> next = NULL;
    // Set the new nodes reference to null
    pNewNode -> name = malloc(strlen(attrName));
    
    strcpy(pNewNode -> name, attrName);
    // Insert the string into the new node
    
    pHead = pTail = pNewNode;
    // Set the head and tail equal to the new node because
    // there is only one node.
}

void createNewListInt(int attrNum)
{
    Node *pNewNode = malloc(sizeof(Node));
    // Creates new node to be inserted into the list
    
    pNewNode -> next = NULL;
    // Set the new nodes refence to null
    
    pNewNode -> num = attrNum;
    // Insert the int into the new node
    
    pHead = pTail = pNewNode;
    // Set the head and tail equal to the new node because
    // there is only one node.
}

void printListString()
{
    Node *pCurr = pHead;
    // Node pointer to loop through list
    
    if (pHead == NULL)
    // If the list is empty, print error message
    {
        printf("Error: Nothing was read into the list\n"); fflush(stdout);
    }
    
    else
    // If the list is not empty
    {
        while (pCurr != NULL)
        // Loop through the list and print values
        {
            printf("%s\n", pCurr -> name); fflush(stdout);
            // Print the value in the current node
            
            pCurr = pCurr -> next;
            // Move to next node
        }
        
        pHead = NULL;
    }
    
    free(pCurr);
}

void printListInt()
{
    Node *pCurr = pHead;
    // Node pointer to loop through list
    
    if (pHead == NULL)
    // If the list is empty, print error message
    {
        printf("Error: Nothing was read into the list\n"); fflush(stdout);
    }
    
    else
    // If the list is not empty
    {
        while (pCurr != NULL)
        // Loop through the list and print values
        {
            printf("%d\n", pCurr -> num); fflush(stdout);
            // Print the value in the current node
            
            pCurr = pCurr -> next;
            // Move to next node
        }
        
        pHead = NULL;
    }
    
    free(pCurr);
}