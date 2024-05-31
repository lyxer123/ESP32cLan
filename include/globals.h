#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

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

    void sendln(char *it);
    void sendc(char it);
    void send(char *it);
    void sprint(char *it);
    void sendContent(char *it);

#ifdef __cplusplus
}
#endif

#endif