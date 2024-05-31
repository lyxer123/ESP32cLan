#ifndef MYLEX_H
#define MYLEX_H

#include <Arduino.h>
#include "myInterpreter.h"

#ifdef NO_CTYPE
#define isalpha(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
#define isdigit(c) ((c) >= '0' && (c) <= '9')
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n')
#endif

#define isCidstart(c) (isalpha(c) || (c)=='_' || (c)=='#')
#define isCident(c) (isalnum(c) || (c)=='_')

#define IS_HEX_ALPHA_DIGIT(c) (((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define IS_BASE_DIGIT(c,b) (((c) >= '0' && (c) < '0' + (((b)<10)?(b):10)) || (((b) > 10) ? IS_HEX_ALPHA_DIGIT(c) : FALSE))
#define GET_BASE_DIGIT(c) (((c) <= '9') ? ((c) - '0') : (((c) <= 'F') ? ((c) - 'A' + 10) : ((c) - 'a' + 10)))

#define NEXTIS(c,x,y) { if (NextChar == (c)) { LEXER_INC(Lexer); GotToken = (x); } else GotToken = (y); }
#define NEXTIS3(c,x,d,y,z) { if (NextChar == (c)) { LEXER_INC(Lexer); GotToken = (x); } else NEXTIS(d,y,z) }
#define NEXTIS4(c,x,d,y,e,z,a) { if (NextChar == (c)) { LEXER_INC(Lexer); GotToken = (x); } else NEXTIS3(d,y,e,z,a) }
#define NEXTIS3PLUS(c,x,d,y,e,z,a) { if (NextChar == (c)) { LEXER_INC(Lexer); GotToken = (x); } else if (NextChar == (d)) { if (Lexer->Pos[1] == (e)) { LEXER_INCN(Lexer, 2); GotToken = (z); } else { LEXER_INC(Lexer); GotToken = (y); } } else GotToken = (a); }
#define NEXTISEXACTLY3(c,d,y,z) { if (NextChar == (c) && Lexer->Pos[1] == (d)) { LEXER_INCN(Lexer, 2); GotToken = (y); } else GotToken = (z); }

#define LEXER_INC(l) ( (l)->Pos++, (l)->CharacterPos++ )
#define LEXER_INCN(l, n) ( (l)->Pos+=(n), (l)->CharacterPos+=(n) )
#define TOKEN_DATA_OFFSET 2

#define MAX_CHAR_VALUE 255

struct ReservedWord
{
    const char *Word;
    enum LexToken Token;
    const char *SharedWord;
};

struct TokenLine
{
    struct TokenLine *Next;
    unsigned char *Tokens;
    int NumBytes;
};

extern char *Prompt;

/* Function declarations */
void LexInit(void);
void LexCleanup(void);
enum LexToken LexCheckReservedWord(const char *Word);
enum LexToken LexGetNumber(struct LexState *Lexer, struct Value *Value);
enum LexToken LexGetWord(struct LexState *Lexer, struct Value *Value);
unsigned char LexUnEscapeCharacterConstant(const char **From, const char *End, unsigned char FirstChar, int Base);
unsigned char LexUnEscapeCharacter(const char **From, const char *End);
enum LexToken LexGetStringConstant(struct LexState *Lexer, struct Value *Value, char EndChar);
enum LexToken LexGetCharacterConstant(struct LexState *Lexer, struct Value *Value);
void LexSkipComment(struct LexState *Lexer, char NextChar, enum LexToken *ReturnToken);
enum LexToken LexScanGetToken(struct LexState *Lexer, struct Value **Value);
int LexTokenSize(enum LexToken Token);
void *LexTokenise(struct LexState *Lexer, int *TokenLen);
void *LexAnalyse(const char *FileName, const char *Source, int SourceLen, int *TokenLen);
void LexInitParser(struct ParseState *Parser, const char *SourceText, void *TokenSource, char *FileName, int RunIt, int EnableDebugger);
enum LexToken LexGetRawToken(struct ParseState *Parser, struct Value **Value, int IncPos);
void LexHashIncPos(struct ParseState *Parser, int IncPos);
void LexHashIfdef(struct ParseState *Parser, int IfNot);
void LexHashIf(struct ParseState *Parser);
void LexHashElse(struct ParseState *Parser);
void LexHashEndif(struct ParseState *Parser);
enum LexToken LexGetToken(struct ParseState *Parser, struct Value **Value, int IncPos);
enum LexToken LexRawPeekToken(struct ParseState *Parser);
void LexToEndOfLine(struct ParseState *Parser);
void *LexCopyTokens(struct ParseState *StartParser, struct ParseState *EndParser);
void LexInteractiveClear(struct ParseState *Parser);
void LexInteractiveCompleted(struct ParseState *Parser);
void LexInteractiveStatementPrompt(void);

#endif /* LEX_H */
