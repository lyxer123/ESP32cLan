#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
void runProgram();
extern String HTMLout;
extern const char MobileFreindlyWidth[] PROGMEM;

String getValue(String data, char separator, int index);

#endif // MAIN_H