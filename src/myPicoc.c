/* picoc main program - this varies depending on your operating system and how you're using picoc */ 
/* include only picoc.h here - should be able to use it with only the external interfaces, no internals from interpreter.h */
#include "myPicoc.h"

/* platform-dependent code for running programs is in this file */

/**************************************************************************
Copyright (c) 2009-2011, Zik Saleeba
All rights reserved.
************************************************************************/
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "myPicoc.h"
#include "myInterpreter.h"

extern char * Prompt;
/* space for the the stack */
// extern char buf[BUFSIZE];
int picoc_main()
{
    int i;
    for (i=0;i<BUFSIZE;i++) buf[i]=0;
    int DontRunMain = FALSE;
    int StackSize = HEAP_SIZE;
    PicocInitialise(StackSize);
    
    Prompt = "picoc> ";
    PicocIncludeAllSystemHeaders(1);
    PicocParseInteractive();
    
    
    PicocCleanup();
    return PicocExitValue;
}
