#ifndef MYCTYPE_H
#define MYCTYPE_H

#include <Arduino.h>
#include "myInterpreter.h"

// Function prototypes
void StdIsalnum(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsalpha(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsblank(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIscntrl(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsdigit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsgraph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIslower(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsprint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIspunct(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsspace(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsupper(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsxdigit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdTolower(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdToupper(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdIsascii(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdToascii(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

#endif /* MYCTYPE_H */
