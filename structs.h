// Arthur Knapp
// AK146316
// structs.h

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