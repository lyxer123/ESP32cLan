#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <pgmspace.h>
#include <esp_system.h>
#include <esp_heap_caps.h>

#define _INT32_ long
#define _UINT32_ unsigned long
#define _INT16_ int
#define _UINT16_ unsigned int

#define D0 26
#define D1 22
#define D2 21
#define D3 17
#define D4 16
#define D5 18
#define D6 19
#define D7 23
#define D8 5
#define A0 36

extern const char myFont[][8] PROGMEM;

#ifdef ESP32
    #ifdef SSD1306OLED
        #define BUILTIN_LED 25
    #else
        #define BUILTIN_LED 2
    #endif
#endif // ESP32

// String getValue(String data, char separator, int index);
extern char didPlines;

#ifdef __cplusplus
extern "C"
{
#endif

    struct StackFrame;  // 前向声明
    extern struct StackFrame *TopStackFrame;

    void sendln(char *it);
    void sendc(char it);
    void send(char *it);
    void sprint(char *it);
    void sendContent(char *it);

#ifdef __cplusplus
}
#endif



#endif