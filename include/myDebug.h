#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <Arduino.h>
#include "myInterpreter.h"

#ifndef NO_DEBUGGER
    /* Constants */
    #define BREAKPOINT_TABLE_SIZE 21
    #define BREAKPOINT_HASH(p) ( ((unsigned long)(p)->FileName) ^ (((p)->Line << 16) | (0 << 16)) )

    /* Global variables */
    extern char SingleStep;
    extern char DebugBar[];
    extern char sendChunked;
    extern struct Table BreakpointTable;
    extern struct TableEntry *BreakpointHashTable[BREAKPOINT_TABLE_SIZE];
    extern int BreakpointCount;
    extern int DebugManualBreak;

    /* Function declarations */
    void DebugInit(void);
    void DebugCleanup(void);
    void DebugSetBreakpoint(struct ParseState *Parser);
    int DebugClearBreakpoint(struct ParseState *Parser);
    void DebugCheckStatement(struct ParseState *Parser);
    void PrintValue(struct Value *Var);
    int DebugStep(struct ParseState *Parser);
    void prntLines(struct ParseState *Parser);

#endif /* !NO_DEBUGGER */

#endif /* DEBUG_H */
