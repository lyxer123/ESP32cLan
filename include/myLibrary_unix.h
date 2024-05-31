#ifndef MYLIBRARY_UNIX_H
#define MYLIBRARY_UNIX_H

#include "myInterpreter.h"

/* Function declarations */
void UnixSetupFunc(void);
char *PlatformReadFile(char *FileName);
void Clineno(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void irand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void picocexit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Sleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void CurLinePrint(struct ParseState *Parser);
void prntLines(struct ParseState *Parser);
void LinePrint(char *src, int line, int col);
void PlatformLibraryInit(void);

/* List of all library functions and their prototypes */
extern struct LibraryFunction UnixFunctions[];

#endif /* LIBRARY_UNIX_H */
