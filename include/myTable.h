#ifndef MYTABLE_H
#define MYTABLE_H

#include <Arduino.h>
#include "myInterpreter.h"

#define STRING_TABLE_SIZE 1024  // Adjust as necessary

struct Table
{
    short Size;
    short OnHeap;
    struct TableEntry **HashTable;
};

/* hash table data structure */
struct TableEntry
{
    struct TableEntry *Next;  /* next item in this hash chain */
    const char *DeclFileName; /* where the variable was declared */
    unsigned short DeclLine;
    unsigned short DeclColumn;

    union TableEntryPayload
    {
        struct ValueEntry
        {
            char *Key;         /* points to the shared string table */
            struct Value *Val; /* the value we're storing */
        } v;                   /* used for tables of values */

        char Key[1]; /* dummy size - used for the shared string table */

        struct BreakpointEntry /* defines a breakpoint */
        {
            const char *FileName;
            short int Line;
            short int CharacterPos;
        } b;

    } p;
};

extern struct Table StringTable;
extern struct TableEntry *StringHashTable[STRING_TABLE_SIZE];
extern char *StrEmpty;

/* Function declarations */
void TableInit();
static unsigned int TableHash(const char *Key, int Len);
void TableInitTable(struct Table *Tbl, struct TableEntry **HashTable, int Size, int OnHeap);
static struct TableEntry *TableSearch(struct Table *Tbl, const char *Key, int *AddAt);
int TableSet(struct Table *Tbl, char *Key, struct Value *Val, const char *DeclFileName, int DeclLine, int DeclColumn);
int TableGet(struct Table *Tbl, const char *Key, struct Value **Val, const char **DeclFileName, int *DeclLine, int *DeclColumn);
struct Value *TableDelete(struct Table *Tbl, const char *Key);
static struct TableEntry *TableSearchIdentifier(struct Table *Tbl, const char *Key, int Len, int *AddAt);
char *TableSetIdentifier(struct Table *Tbl, const char *Ident, int IdentLen);
char *TableStrRegister2(const char *Str, int Len);
char *TableStrRegister(const char *Str);
void TableStrFree();

#endif /* MYTABLE_H */
