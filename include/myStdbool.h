/* myStdbool.h - Header file for myStdbool.c */

#ifndef MYSTDBOOL_H
#define MYSTDBOOL_H

#include <Arduino.h>
#include "myInterpreter.h"

#ifndef BUILTIN_MINI_STDLIB

/* Boolean type definition */
typedef int bool;

/* Function to set up standard boolean values */
void StdboolSetupFunc(void);

#endif /* !BUILTIN_MINI_STDLIB */

#endif /* MYSTDBOOL_H */
