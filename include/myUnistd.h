#ifndef MYUNISTD_H
#define MYUNISTD_H

#include <Arduino.h>
#include <stdio.h>
#include <limits.h>
#include "myInterpreter.h"

#ifndef BUILTIN_MINI_STDLIB
#include <unistd.h>

/* Function declarations for unistd.h functions */
void UnistdAccess(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdAlarm(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdChdir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdChroot(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdChown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdClose(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdConfstr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdCtermid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdDup(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdDup2(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Unistd_Exit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFchown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFchdir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFdatasync(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFork(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFpathconf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFsync(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdFtruncate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetcwd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetdtablesize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetegid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGeteuid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetgid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGethostid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetlogin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetlogin_r(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetpagesize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetpass(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetpgrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetpid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetppid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetuid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdGetwd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdIsatty(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdLchown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdLink(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdLockf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdLseek(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdNice(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdPathconf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdPause(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdRead(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdReadlink(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdRmdir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSbrk(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetgid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetpgid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetpgrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetregid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetreuid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetsid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSetuid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSymlink(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSync(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdSysconf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdTcgetpgrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdTcsetpgrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdTruncate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdTtyname(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdTtyname_r(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdUalarm(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdUnlink(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdUsleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdVfork(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void UnistdWrite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

/* Unistd setup function */
void UnistdSetupFunc(void);

#endif /* !BUILTIN_MINI_STDLIB */

#endif /* MYUNISTD_H */
