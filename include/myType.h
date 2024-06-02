#ifndef MYTYPE_H
#define MYTYPE_H

#include "myInterpreter.h"


/* some basic types */
extern struct ValueType UberType;
extern struct ValueType IntType;
extern struct ValueType ShortType;
extern struct ValueType CharType;
extern struct ValueType LongType;
extern struct ValueType UnsignedIntType;
extern struct ValueType UnsignedShortType;
extern struct ValueType UnsignedLongType;
#ifndef NO_FP
    extern struct ValueType FPType;
#endif
extern struct ValueType VoidType;
extern struct ValueType TypeType;
extern struct ValueType FunctionType;
extern struct ValueType MacroType;
extern struct ValueType EnumType;
extern struct ValueType GotoLabelType;
extern struct ValueType *CharPtrType;
extern struct ValueType *CharPtrPtrType;
extern struct ValueType *CharArrayType;
extern struct ValueType *VoidPtrType;

/* add a new type to the set of types we know about */
struct ValueType *TypeAdd(struct ParseState *Parser, struct ValueType *ParentType, enum BaseType Base, int ArraySize, const char *Identifier, int Sizeof, int AlignBytes);

/* given a parent type, get a matching derived type and make one if necessary. 
 * Identifier should be registered with the shared string table. */
struct ValueType *TypeGetMatching(struct ParseState *Parser, struct ValueType *ParentType, enum BaseType Base, int ArraySize, const char *Identifier, int AllowDuplicates);

/* stack space used by a value */
int TypeStackSizeValue(struct Value *Val);

/* memory used by a value */
int TypeSizeValue(struct Value *Val, int Compact);

/* memory used by a variable given its type and array size */
int TypeSize(struct ValueType *Typ, int ArraySize, int Compact);

/* add a base type */
void TypeAddBaseType(struct ValueType *TypeNode, enum BaseType Base, int Sizeof, int AlignBytes);

/* initialise the type system */
void TypeInit(void);

/* deallocate heap-allocated types */
void TypeCleanupNode(struct ValueType *Typ);

void TypeCleanup(void);

/* parse a struct or union declaration */
void TypeParseStruct(struct ParseState *Parser, struct ValueType **Typ, int IsStruct);

/* create a system struct which has no user-visible members */
struct ValueType *TypeCreateOpaqueStruct(struct ParseState *Parser, const char *StructName, int Size);

/* parse an enum declaration */
void TypeParseEnum(struct ParseState *Parser, struct ValueType **Typ);

/* parse a type - just the basic type */
int TypeParseFront(struct ParseState *Parser, struct ValueType **Typ, int *IsStatic);

/* parse a type - the part at the end after the identifier. eg. array specifications etc. */
struct ValueType *TypeParseBack(struct ParseState *Parser, struct ValueType *FromType);

/* parse a type - the part which is repeated with each identifier in a declaration list */
void TypeParseIdentPart(struct ParseState *Parser, struct ValueType *BasicTyp, struct ValueType **Typ, char **Identifier);

/* parse a type - a complete declaration including identifier */
void TypeParse(struct ParseState *Parser, struct ValueType **Typ, char **Identifier, int *IsStatic);

#endif /* MYTYPE_H */
