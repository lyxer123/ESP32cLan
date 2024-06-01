#ifndef MYCLIBRARY_H
#define MYCLIBRARY_H

#include <Arduino.h>
#include "globals.h"
#include "myPicoc.h"
#include <FS.h>

#ifdef ESP32
#include "LittleFS.h"
#include <ESP32Servo.h>
#endif

#ifdef BME280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
extern Adafruit_BME280 bme;
void BME_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void BME_readTemp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void BME_readPressure(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void BME_readRH(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif

#ifdef ePAPER
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.cpp>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

extern GxIO_Class io;
extern GxEPD_Class display;
extern int didEpaperInit;

void ePaper_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_powerDown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_setCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_setTextColor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_println(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_update(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_fillRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void ePaper_drawLine(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif

void loop();
extern char doScreenCapture;
boolean screenServer(void);
void doLoop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

#ifdef NEO_PIXEL
#include <Adafruit_NeoPixel.h>
extern Adafruit_NeoPixel *neoPixel;

void NEO_begin_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_setup(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_setPixelColorRGB(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_setPixelColorRGBW(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_setPixelColor32(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_fill(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_setBrightness(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_colorWipe(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_theaterChase(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_rainbow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void NEO_theaterChaseRainbow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif

#ifdef ESP32
extern ESP32PWM PWMs[16];
extern int pwmAssigns[16];
struct pwmRange {
    float min;
    float max;
};
extern pwmRange pwmRanges[16];
extern float pwmFreqs[4];
void PrintAndWebOut(String what);
extern int pwmRes[40];
extern int pwmFreq[40];
#endif

#ifdef OLED
#include <U8g2lib.h>
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8x8;
extern int oi;
#endif

#ifdef SSD1306OLED
#include "SSD1306Wire.h"
extern SSD1306Wire display;
extern OLEDDISPLAY_COLOR OLEDcolor;
#endif

#ifdef TFT
#include <TftGauge.h>
#include <Hershey.h>
extern TFT_eSPI tft;
extern Hershey HF;
void drawJpeg(char *filename, int xpos, int ypos);
void FontShow();
void TFT_Gauge(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_Gauge_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_Gauge_drawDanger(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_Gauge_drawDangerByValue(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_Gauge_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_Gauge_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_VbarGraph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_VbarGraph_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_VbarGraph_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_VbarGraph_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_HbarGraph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_HbarGraph_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_HbarGraph_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void TFT_HbarGraph_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void setFont(char *font);
void screenCapture(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void scroll(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void setScrollPixels(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void consoleAlert(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void setConsoleOn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void consoleOut(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFsetCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFsetStrokeDelay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdrawStringRotated(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdrawString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdrawStringOpaque(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdrawCenteredString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFgetStringSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdraw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFdrawRotated(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void HFsetFont(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif

extern "C" {
    extern char literal;
    extern char listIncludes;
    extern char SingleStep;
    extern const char *VersionString;
    extern const int __ENDIAN_CHECK__;
    extern int BigEndian;
    extern int LittleEndian;
    extern int nwatches;
    extern char watches[20][33];

    // extern WebServer server;    //liuyongxiang
    void stopDebug(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void Debug(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void Watch(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void dropWatch(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
    void LibraryInit();
    void LibraryAdd(struct Table *GlobalTable, const char *LibraryName, struct LibraryFunction *FuncList);
    void PrintType(struct ValueType *Typ);
}

#ifdef BUILTIN_MINI_STDLIB

#ifdef __cplusplus
extern "C" {
#endif

extern const char *VersionString;
extern const int __ENDIAN_CHECK__ ;
extern int BigEndian ;
extern int LittleEndian ;

// IOFILE and IOFILE base structures
// extern IOFILE *CStdOut;
// extern IOFILE CStdOutBase;

// Basic IO Initialization
void BasicIOInit();

// C Library Initialization
void CLibraryInit();

// Stream writing functions
void SPutc(unsigned char Ch);
void PrintCh(char OutCh);
void PrintStr(const char *Str);
void PrintRepeatedChar(char ShowChar, int Length);
void PrintUnsigned(unsigned long Num, unsigned int Base, int FieldWidth, int ZeroPad, int LeftJustify);
void PrintSimpleInt(long Num);
void PrintInt(long Num, int FieldWidth, int ZeroPad, int LeftJustify);
#ifndef NO_FP
void PrintFP(double Num);
#endif

void PrintWithCommas(unsigned long n, int width);

// Intrinsic functions for the language
void GenericPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibPrint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibSPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibGets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibGetc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibExit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

#ifdef PICOC_LIBRARY

#ifndef NO_FP
void StdlibAtof(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif
void StdlibAtoi(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibAtol(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#ifndef NO_FP
void StdlibStrtod(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif
void StdlibStrtol(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibStrtoul(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibRand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibSrand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibAbs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void StdlibLabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

void LibSin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibCos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibTan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibAsin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibAcos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibAtan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibSinh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibCosh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibTanh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibExp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibFabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibLog(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibLog10(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibPow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibSqrt(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibRound(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibCeil(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibFloor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

#endif // PICOC_LIBRARY

#ifndef NO_STRING_FUNCTIONS
void LibMalloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#ifndef NO_CALLOC
void LibCalloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif
#ifndef NO_REALLOC
void LibRealloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif
void LibFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Libstrcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibStrncpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibStrcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibStrncmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Libstrcat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void Libstrncat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibIndex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibRindex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibStrlen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibMemset(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibMemcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibMemcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
#endif // NO_STRING_FUNCTIONS

#endif

#ifdef __cplusplus
}
#endif

#endif // MYCLIBRARY_H
