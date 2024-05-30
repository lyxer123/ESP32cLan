#ifndef PARSE_H
#define PARSE_H

#include "interpreter.h"

/* Function declarations */
void ParseCleanup(void);
enum ParseResult ParseStatementMaybeRun(struct ParseState *Parser, int Condition, int CheckTrailingSemicolon);
int ParseCountParams(struct ParseState *Parser);
struct Value *ParseFunctionDefinition(struct ParseState *Parser, struct ValueType *ReturnType, char *Identifier);
void ParseDeclarationAssignment(struct ParseState *Parser, struct Value *NewVariable, int DoAssignment);
int ParseDeclaration(struct ParseState *Parser, enum LexToken Token);
void ParseMacroDefinition(struct ParseState *Parser);
void ParserCopy(struct ParseState *To, struct ParseState *From);
void ParserCopyPos(struct ParseState *To, struct ParseState *From);
void ParseFor(struct ParseState *Parser);
enum RunMode ParseBlock(struct ParseState *Parser, int AbsorbOpenBrace, int Condition);
void ParseTypedef(struct ParseState *Parser);
enum ParseResult ParseStatement(struct ParseState *Parser, int CheckTrailingSemicolon);
void PicocParse(const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger);
void PicocParseInteractiveNoStartPrompt(int EnableDebugger);
void PicocParseInteractive(void);

/* External functions */
void CurLinePrint(struct ParseState *Parser);
void PrintLines(struct ParseState *Parser);

#endif /* PARSE_H */
