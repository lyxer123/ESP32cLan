#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

extern String HTMLout;
extern const char MobileFreindlyWidth[] PROGMEM;

#ifdef ePAPER
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h> // 1.54" b/w
extern GxGDEP015OC1 display;           // 1.54" b/w display
#endif

#ifndef ESP32
#define FS_NO_GLOBALS
#include <FS.h>
#include <ESP8266WiFi.h>
#else
#include "LittleFS.h"
#include <WiFi.h>
#endif
#include <WiFiClient.h>
#include <WiFiServer.h>

#ifdef ESP32
#include <HTTPUpdate.h>
#include <WebServer.h>
extern WebServer server;
#else
#include <ESP8266WebServer.h>
extern ESP8266WebServer server;
#endif

#include <Wire.h>
#include <time.h>

#ifdef TFT
#include <TFT_eSPI.h> // Hardware-specific library
#include <JPEGDecoder.h>
#include <Hershey.h>
extern TFT_eSPI tft;
#endif

#ifdef OLED
#include <U8g2lib.h>
// the OLED used
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8x8;
#endif

#ifdef SSD1306OLED
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
extern SSD1306Wire display;
extern OLEDDISPLAY_COLOR OLEDcolor;
#endif

#ifdef ESP32
extern File fsUploadFile;
#else
extern fs::File fsUploadFile;
#endif

extern char sendChunked;
extern String programArgs;
extern String ProgramName;
extern String GlobalNames[200];
extern int GlobalCount;

extern "C" {
#include "myPicoc.h"
#include "myInterpreter.h"
extern char listIncludes;
void IncludeFile(char *FileName);
void idrop(char *what);
void addGlobal(char *what);
void DeleteGlobals();
void espRestart();
void shortEspRestart();
char *getProgramArgs();
extern char SingleStep;
extern struct ParseState Parser;
extern enum ParseResult Ok;
extern char buf[BUFSIZE];
extern char *Prompt;
extern byte didit;
extern byte line_available;
extern char literal;
extern char toConsole;
#ifdef TFT
void iconsoleOut(char *what);
#endif
void sendContent(char *it);
void sok();
int hextoi(char i);
void urldecode(char *src, char *dst);
extern char WebResponse;
extern char WebResponseBuf[400];
char *PlatformGets(char *Buf, int MaxLen, const char *Prompt);
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt);
void DebugPrintln(char *what);
void DebugPrintInt(int what);
void sPrintln(char *what);
void sPrintInt(int what);
void sprint(char *what);
void ssend(char *what);
char *PlatformReadFile(char *FileName);
int PlatformGetCharacter();
void printLines(char *src);
void sendc(char it);
void sendln(char *it);
void send(char *it);
void PlatformPutc(unsigned char OutCh, FILE *Stream);
extern int nwatches;
void sok();
void sendEOF();
void send(char *it);
extern int RunningProgram;
void Ssend(char *it);
void sendc(char it);
void sendln(char *it);
char fileExists(char *fileName);
}


uint32_t getFreeHeapSize(void);
void setup();
void loop();
void runProgram();

void handleFileUpdate();
bool CheckIfLoggedIn();
String SettingsPageHandeler();
String getContentType(String filename);
void StartUpProgramTimer();
void DoSomeFileManagerCode();
void serialFlush();
String getValueforPrograming(String data, char separator, int index);

String getValue(String data, char separator, int index);
String FetchWebUrl(String URLtoGet, int PortNoForPage);


#endif // MAIN_H