// Arthur Knapp
// AK146316
// structs.h

// Struct Descriptions:

// RelationsTable:
// Stores the name, offset and number of attributes from the relations file

// AttributesTable:
// Stores the name, type and size from the attributes file

// LinkedList:
// Stores the value from the data file of the attribute entered in the command line.
// This will be used by the project and select commands.

typedef struct RelationsTable
{
    char name[NAME_SIZE];
    int offset;
    int numAttr;
} RelationsTable;

typedef struct AttributesTable
{
    char name[NAME_SIZE];
    char type;
    int size;
} AttributesTable;

typedef struct LinkedList
{
    char *name;
    int num;
    
    struct LinkedList *next;
} Node;
