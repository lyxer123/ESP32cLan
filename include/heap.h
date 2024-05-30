#ifndef HEAP_H
#define HEAP_H

#include <Arduino.h>

/* Define to use system's malloc */
#define USE_MALLOC_HEAP
//#define USE_MALLOC_STACK

/* Adjust these parameters as needed */
#define HEAP_SIZE 1024
#define ALIGN_TYPE double

/* Alignment macros */
#define MEM_ALIGN(x) (((x) + (sizeof(ALIGN_TYPE) - 1)) & ~(sizeof(ALIGN_TYPE) - 1))

/* Constants for free list buckets and memory splitting */
#define FREELIST_BUCKETS 8
#define SPLIT_MEM_THRESHOLD 16

/* Structure for allocated nodes */
struct AllocNode
{
    int Size;
    struct AllocNode *NextFree;
};

/* Function prototypes */
void HeapInit(int StackOrHeapSize);
void HeapCleanup();
void *HeapAllocStack(int Size);
void HeapUnpopStack(int Size);
int HeapPopStack(void *Addr, int Size);
void HeapPushStackFrame();
int HeapPopStackFrame();
void *HeapAllocMem(int Size);
void HeapFreeMem(void *Mem);

#ifdef DEBUG_HEAP
void ShowBigList();
#endif

#endif /* HEAP_H */
