#ifndef MYSTRING_H
#define MYSTRING_H

#include <Arduino.h>
#include "myInterpreter.h"

#ifndef BUILTIN_MINI_STDLIB
#ifdef WIN32
#pragma warning(disable: 4996)
#endif

/* Function declarations */
void Stringstrcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrncpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrncmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Stringstrcat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrncat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringIndex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringRindex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrlen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringMemset(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringMemcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringMemcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringMemmove(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringMemchr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrchr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrrchr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrcoll(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrerror(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrspn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrcspn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrpbrk(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrstr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrtok(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrxfrm(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrdup(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StringStrtok_r(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

/* creates various system-dependent definitions */
void StringSetupFunc(void);

extern struct LibraryFunction StringFunctions[];

#endif /* !BUILTIN_MINI_STDLIB */

#endif /* MYSTRING_H */
