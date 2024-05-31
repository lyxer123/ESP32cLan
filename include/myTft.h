#ifndef MYTFT_H
#define MYTFT_H

#include <Arduino.h>
#include "myPicoc.h"

#ifdef TFT
#include <TFT_eSPI.h>
#include <SPI.h>
#include <NTPClient.h>
#include <Hershey.h>

extern TFT_eSPI tft;
// extern char buf[BUFSIZE];
extern int indx;
extern float temp, pressure, dp, rh;
extern NTPClient timeClient;
extern Hershey HF;

#define SlideDelay 1000

void drawGuagePointer(int xc, int yc, int sAngle, int eAngle, int rad, int sValue, int eValue, float pos);
void toScreen(String message, int *ln);
void drawJpeg(char *filename, int xpos, int ypos);
void drawGlabels(int ht, int min, int max, int divs);
void drawGlabels2(int ht, int min, int max, int divs);
void drawHnd(int xc, int yc, int x1, int y1, uint color, int indx);
void weatherGuage();
void graphWeather();
void TFTFileDemo();
void FontShow();
void screenServer();

#endif // TFT

#endif // TFT_H
