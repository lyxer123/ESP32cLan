#ifndef INCLUDE_H
#define INCLUDE_H

#include <Arduino.h>
#include "picoc.h"
#include "interpreter.h"
#include "myVar.h"

#ifndef NO_HASH_INCLUDE

/* Struct for include libraries */
struct IncludeLibrary
{
    char *IncludeName;
    void (*SetupFunction)(void);
    struct LibraryFunction *FuncList;
    const char *SetupCSource;
    struct IncludeLibrary *NextLib;
};

/* Global variables */
extern struct IncludeLibrary *IncludeLibList;
extern char listIncludes;

/* Function declarations */
void IncludeInit(void);
void IncludeCleanup(void);
void IncludeRegister(const char *IncludeName, void (*SetupFunction)(void), struct LibraryFunction *FuncList, const char *SetupCSource);
void PicocIncludeAllSystemHeaders(int inctmpl);
void IncludeFile(char *FileName);
char fileExists(char *fileName);

#endif /* NO_HASH_INCLUDE */

#endif /* INCLUDE_H */
