#ifndef MYMATH_H
#define MYMATH_H

#include "myInterpreter.h"

/* Function declarations */
void MathSin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathCos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathTan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathAsin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathAcos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathAtan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathAtan2(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathSinh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathCosh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathTanh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathExp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathFabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathFmod(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathFrexp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathLdexp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathLog(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathLog10(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathModf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathPow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathSqrt(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathRound(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathCeil(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void MathFloor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

/* List of all library functions and their prototypes */
extern struct LibraryFunction MathFunctions[];

/* Setup function */
void MathSetupFunc(void);

#endif     /* MATH_H */
