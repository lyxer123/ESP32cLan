#ifndef MYWIFI_STUFF_H
#define MYWIFI_STUFF_H

#include "Arduino.h"
#include "globals.h"
#include "WiFi.h"

#ifdef OLED
#include <U8g2lib.h>
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8x8;
extern int oi;
#endif // OLED

#ifdef SSD1306OLED
#include "SSD1306Wire.h"
extern SSD1306Wire display;
extern OLEDDISPLAY_COLOR OLEDcolor;
extern int OLEDdisplayOn;
#endif

#ifdef TFT
#include <TFT_eSPI.h>
#include <Hershey.h>
extern Hershey HF;
extern TFT_eSPI tft;
#endif // TFT

#ifdef ePAPER
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h>
extern GxGDEP015OC1 display;
#endif // ePAPER

void CreateAP(String NetworkName, String NetworkPassword);
bool ConnectToTheWIFI(String NetworkName, String NetworkPassword, String NetworkStaticIP = "", String NetworkGateway = "", String NetworkSubnet = "");


#endif // MYWIFI_STUFF_H
