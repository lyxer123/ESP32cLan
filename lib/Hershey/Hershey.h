/* Hershey Fonts Render library

MIT license
written by Rick Lunglhofer
for Micro Image Systems

*/
#ifndef HERSHEY_H
#define HERSHEY_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define FS_NO_GLOBALS
#include <FS.h>"
//#include "SPIFFS.h" // include for ESP32 builds

// Uncomment to enable printing out nice debug messages.
//#define HERSHEY_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef HF_DEBUG
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif
// define serif to include serif font support
#define SERIF
// define sans to include sans serif font
#define SANS
// define sansBold to include bold version of sans serif font
#define SANSB
// define GREEK to include greek letter font
#define GREEK
// define CURSIVE to include cursive letter font
#define CURSIVE
/**********************************************************************************

colors are entered in 16 bit RGB format with the binary value for 
red in top 5 bits green in next six bits and blue in last 5 bits
i.e. rrrrrggggggbbbbb

scale is a float vaule at scale 1.0 rendering is at the Hershey fort native scale 

setup for use on Wemos D1 mini with the eSPI_TFT library

***********************************************************************************/

class Hershey {
public:
    
	Hershey(char * DefaultFont);

void setFont(char * font);

void setCursor(int x,int y);
void setStrokeDelay(int delay);

void drawStringRotated(int x,int y,int r,float scale,int color,float a,char * string);
// draw string rotated only works for up to two character strings and was
// produced to support drawing circular guage annotations

void drawString(int x,int y,float scale,int color,char * string);

void drawStringOpaque(int x,int y,float scale,int fcolor,int bcolor,char * string);

void drawCenteredString(int y,float scale,int color,char * string);

int getStringSize(char * it,float scale);

void draw(char chr,float scale,int color);

void drawRotated(int xc,int yc,char chr,float scale,int color,float angle);


private:
    int getSize(char * it,float scale);
    void getPt(int indx,float scale,fs::File fin);
    void loadfile(char * fname);
	float pt[2][2];
	char * cp;
	int ox= 5;
    int oy= 20;
    int n;
	int strokeDelay=0;
	int deltax,deltay;
    int hFont[96];
	char fontFile[32];
};


#endif
