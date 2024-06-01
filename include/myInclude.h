#ifndef MYINCLUDE_H
#define MYINCLUDE_H

#include <Arduino.h>
#include "myPicoc.h"
#include "myInterpreter.h"

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
