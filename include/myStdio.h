#ifndef MYSTDIO_H
#define MYSTDIO_H

#include <stdio.h>
#include "myInterpreter.h"
#include "myPicoc.h"

//这个文件内容不全，lyx

#ifdef __cplusplus
extern "C" {
#endif

    extern FILE *CStdOut;
    extern struct ValueType *FilePtrType;

    void BasicIOInit();
    void StdioOutPutc(int OutCh, struct StdOutStreamStruct *Stream);
    void StdioOutPuts(const char *Str, struct StdOutStreamStruct *Stream);
    void StdioFprintfWord(struct StdOutStreamStruct *Stream, const char *Format, unsigned int Value);
    void StdioFprintfFP(struct StdOutStreamStruct *Stream, const char *Format, double Value);
    void StdioFprintfPointer(struct StdOutStreamStruct *Stream, const char *Format, void *Value);
    int StdioBasePrintf(struct ParseState *Parser, FILE *Stream, char *StrOut, int StrOutLen, char *Format, struct StdVararg *Args);
    int StdioBaseScanf(struct ParseState *Parser, FILE *Stream, char *StrIn, char *Format, struct StdVararg *Args);

    void StdioPutc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioPutchar(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioSetbuf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioSetvbuf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioUngetc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioPuts(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioGets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioGetchar(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void StdioPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

#ifdef __cplusplus
}
#endif

#endif // MYSTDIO_H
