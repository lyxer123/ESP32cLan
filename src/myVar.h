#ifndef MYVAR_H
#define MYVAR_H



// void PicocInitialise(int StackSize);
// void PicocIncludeAllSystemHeaders(int inctmpl);

#ifdef __cplusplus
extern "C" {
#endif

struct StackFrame;  // 前向声明
extern struct StackFrame *TopStackFrame;

#ifdef __cplusplus
}
#endif

#endif

