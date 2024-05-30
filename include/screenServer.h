#ifndef SCREENSERVER_H
#define SCREENSERVER_H

#include <Arduino.h>

#ifdef TFT

#define PIXEL_TIMEOUT 100     // 100ms Time-out between pixel requests
#define START_TIMEOUT 3000    // 10s Maximum time to wait at start transfer
#define BITS_PER_PIXEL 16     // 24 for RGB colour format, 16 for 565 colour format
#define DEFAULT_FILENAME "tft_screenshots/screenshot" // In case none is specified
#define FILE_TYPE "png"       // jpg, bmp, png, tif are valid
#define FILE_EXT '@'          // Filename extension identifier
#define NPIXELS 8             // Must be integer division of both TFT width and TFT height

boolean screenServer(void);
boolean screenServer(String filename);
boolean serialScreenServer(String filename);
void sendParameters(String filename);

#endif // TFT

#endif // SCREENSERVER_H
