/* picoc mini standard C library - provides an optional tiny C standard library and built in functions
 * if BUILTIN_MINI_STDLIB is defined */

#include <Arduino.h>

#include "globals.h"
#include "myPicoc.h"
#include "myClibrary.h"

#include <FS.h>

const char myFont[][8] PROGMEM = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00},
  {0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, 0x00},
  {0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, 0x00},
  {0x00, 0x23, 0x13, 0x08, 0x64, 0x62, 0x00, 0x00},
  {0x00, 0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x00},
  {0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00, 0x00},
  {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00},
  {0x00, 0xA0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00},
  {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00},
  {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00},
  {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00},
  {0x00, 0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00},
  {0x00, 0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00},
  {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00},
  {0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00},
  {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00},
  {0x00, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00},
  {0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
  {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00},
  {0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xAC, 0x6C, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00},
  {0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00},
  {0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00},
  {0x00, 0x02, 0x01, 0x51, 0x09, 0x06, 0x00, 0x00},
  {0x00, 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00, 0x00},
  {0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, 0x00},
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
  {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00},
  {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00, 0x00},
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00},
  {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, 0x00},
  {0x00, 0x3E, 0x41, 0x41, 0x51, 0x72, 0x00, 0x00},
  {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00},
  {0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00},
  {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00},
  {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00},
  {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, 0x00},
  {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, 0x00},
  {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00},
  {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00},
  {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00},
  {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00},
  {0x00, 0x26, 0x49, 0x49, 0x49, 0x32, 0x00, 0x00},
  {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00},
  {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00},
  {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00},
  {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00, 0x00},
  {0x00, 0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00},
  {0x00, 0x03, 0x04, 0x78, 0x04, 0x03, 0x00, 0x00},
  {0x00, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00},
  {0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00},
  {0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00},
  {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00},
  {0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00, 0x00},
  {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, 0x00},
  {0x00, 0x38, 0x44, 0x44, 0x28, 0x00, 0x00, 0x00},
  {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, 0x00},
  {0x00, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x00},
  {0x00, 0x08, 0x7E, 0x09, 0x02, 0x00, 0x00, 0x00},
  {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, 0x00, 0x00},
  {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00},
  {0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x80, 0x84, 0x7D, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00},
  {0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, 0x00},
  {0x00, 0x7C, 0x08, 0x04, 0x7C, 0x00, 0x00, 0x00},
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00},
  {0x00, 0xFC, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00},
  {0x00, 0x18, 0x24, 0x24, 0xFC, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x7C, 0x08, 0x04, 0x00, 0x00, 0x00},
  {0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00},
  {0x00, 0x04, 0x7F, 0x44, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x3C, 0x40, 0x40, 0x7C, 0x00, 0x00, 0x00},
  {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, 0x00},
  {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, 0x00},
  {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00},
  {0x00, 0x1C, 0xA0, 0xA0, 0x7C, 0x00, 0x00, 0x00},
  {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00},
  {0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x41, 0x36, 0x08, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x02, 0x01, 0x01, 0x02, 0x01, 0x00, 0x00},
  {0x00, 0x02, 0x05, 0x05, 0x02, 0x00, 0x00, 0x00}
};

#ifdef ESP32
  #include <SPIFFS.h>
  // #include "SPIFFS.h"
  #include <ESP32Servo.h>
#endif

#ifdef BME280
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>
  Adafruit_BME280 bme; // I2C
#endif

#ifdef ePAPER
  #include <GxEPD.h>
  #include <GxGDEP015OC1/GxGDEP015OC1.cpp> // 1.54" b/w

  // FreeFonts from Adafruit_GFX
  #include <Fonts/FreeMonoBold9pt7b.h>
  #include <Fonts/FreeMonoBold12pt7b.h>
  #include <Fonts/FreeMonoBold18pt7b.h>
  #include <Fonts/FreeMonoBold24pt7b.h>

  #include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
  #include <GxIO/GxIO.cpp>

  GxIO_Class io(SPI, /*CS=D3*/ 17, /*DC=D4*/ 16, /*RST=D4*/ -1); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
  GxEPD_Class display(io, -1, -1 /*RST=D4*/ /*BUSY=D2*/);        // default selection of D4(=2), D2(=4)
  int didEpaperInit = 0;

  void ePaper_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    if (didEpaperInit != 0)
      return;
    display.init(74880);
    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.update();
    display.setCursor(0, 20);
    didEpaperInit = 1;
  }
  void ePaper_powerDown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    display.powerDown();
  }
  void ePaper_setCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    display.setCursor(x, y);
  }
  void ePaper_setTextColor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int color = Param[0]->Val->Integer;
    display.setTextColor(color);
  }
  void ePaper_println(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *buf = (char *)Param[0]->Val->Pointer;
    display.println(buf);
  }
  void ePaper_update(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    display.update();
  }
  void ePaper_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    int width = Param[2]->Val->Integer;
    int height = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    display.drawRect(x, y, width, height, color);
  }
  void ePaper_fillRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    int width = Param[2]->Val->Integer;
    int height = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    display.fillRect(x, y, width, height, color);
  }
  void ePaper_drawLine(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    display.drawLine(x1, y1, x2, y2, color);
  }
#endif

void loop();
extern char doScreenCapture;
boolean screenServer(void);
void doLoop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  loop();
#ifdef TFT
  if (doScreenCapture == 1)
  {
    screenServer();
    doScreenCapture = 0;
  }
#endif
}

#ifdef NEO_PIXEL
  #include <Adafruit_NeoPixel.h>
  Adafruit_NeoPixel *neoPixel;
  void NEO_begin_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin = Param[1]->Val->Integer;
    int count = Param[0]->Val->Integer;
    neoPixel = new Adafruit_NeoPixel(count, pin, NEO_GRB + NEO_KHZ800);
  }
  void NEO_setup(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int brightness = Param[0]->Val->Integer;
    neoPixel->begin();
    neoPixel->show();
    neoPixel->setBrightness(brightness);
  }
  void NEO_setPixelColorRGB(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    int n = Param[0]->Val->Integer;
    int r = Param[1]->Val->Integer;
    int g = Param[2]->Val->Integer;
    int b = Param[3]->Val->Integer;
    neoPixel->setPixelColor((uint16_t)n, (uint8_t)r, (uint8_t)g, (uint8_t)b);
  }
  void NEO_setPixelColorRGBW(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    int n = Param[0]->Val->Integer;
    int r = Param[1]->Val->Integer;
    int g = Param[2]->Val->Integer;
    int b = Param[3]->Val->Integer;
    int w = Param[4]->Val->Integer;
    neoPixel->setPixelColor((uint16_t)n, (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)w);
  }
  void NEO_setPixelColor32(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint16_t n, uint32_t c);
    int n = Param[0]->Val->Integer;
    int c = Param[1]->Val->Integer;
    neoPixel->setPixelColor((uint16_t)n, c);
  }
  void NEO_fill(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint32_t c=0, uint16_t first=0, uint16_t count=0);
    int c = Param[0]->Val->Integer;
    int first = Param[1]->Val->Integer;
    int count = Param[2]->Val->Integer;
    neoPixel->fill(c, (uint16_t)first, (uint16_t)count);
  }
  void NEO_setBrightness(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint8_t);
    int brightness = Param[0]->Val->Integer;
    neoPixel->setBrightness((uint8_t)brightness);
  }
  // Fill strip pixels one after another with a color. Strip is NOT cleared
  // first; anything there will be covered pixel by pixel. Pass in color
  // (as a single 'packed' 32-bit value, which you can get by calling
  // neoPixel->Color(red, green, blue) as shown in the loop() function above),
  // and a delay time (in milliseconds) between pixels.
  void NEO_colorWipe(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // uint32_t color, int wait) {
    int color = Param[0]->Val->Integer;
    int wait = Param[1]->Val->Integer;
    for (int i = 0; i < neoPixel->numPixels(); i++)
    {                                    // For each pixel in strip...
      neoPixel->setPixelColor(i, color); //  Set pixel's color (in RAM)
      neoPixel->show();                  //  Update strip to match
      delay(wait);                       //  Pause for a moment
    }
  }

  // Theater-marquee-style chasing lights. Pass in a color (32-bit value,
  // a la neoPixel->Color(r,g,b) as mentioned above), and a delay time (in ms)
  // between frames.
  void NEO_theaterChase(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // uint32_t color, int wait) {
    int color = Param[0]->Val->Integer;
    int wait = Param[1]->Val->Integer;
    for (int a = 0; a < 10; a++)
    { // Repeat 10 times...
      for (int b = 0; b < 3; b++)
      {                    //  'b' counts from 0 to 2...
        neoPixel->clear(); //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in steps of 3...
        for (int c = b; c < neoPixel->numPixels(); c += 3)
        {
          neoPixel->setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        neoPixel->show(); // Update strip with new contents
        delay(wait);      // Pause for a moment
      }
    }
  }

  // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
  void NEO_rainbow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // int wait) {
    int wait = Param[0]->Val->Integer;
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
      for (int i = 0; i < neoPixel->numPixels(); i++)
      { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = firstPixelHue + (i * 65536L / neoPixel->numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        neoPixel->setPixelColor(i, neoPixel->gamma32(neoPixel->ColorHSV(pixelHue)));
      }
      neoPixel->show(); // Update strip with new contents
      delay(wait);      // Pause for a moment
    }
  }

  // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
  void NEO_theaterChaseRainbow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // int wait) {
    int wait = Param[0]->Val->Integer;
    int firstPixelHue = 0; // First pixel starts at red (hue 0)
    for (int a = 0; a < 30; a++)
    { // Repeat 30 times...
      for (int b = 0; b < 3; b++)
      {                    //  'b' counts from 0 to 2...
        neoPixel->clear(); //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in increments of 3...
        for (int c = b; c < neoPixel->numPixels(); c += 3)
        {
          // hue of pixel 'c' is offset by an amount to make one full
          // revolution of the color wheel (range 65536) along the length
          // of the strip (neoPixel->numPixels() steps):
          int hue = firstPixelHue + c * 65536L / neoPixel->numPixels();
          uint32_t color = neoPixel->gamma32(neoPixel->ColorHSV(hue)); // hue -> RGB
          neoPixel->setPixelColor(c, color);                           // Set pixel 'c' to value 'color'
        }
        neoPixel->show();            // Update strip with new contents
        delay(wait);                 // Pause for a moment
        firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
      }
    }
  }
#endif

#ifdef ESP32
ESP32PWM PWMs[16];
int pwmAssigns[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
// struct pwmRange
// {
//   float min;
//   float max;
// };
pwmRange pwmRanges[16];
float pwmFreqs[4] = {-1.0, -1.0, 0 - 1.0, -1.0};
void PrintAndWebOut(String what);
int pwmRes[40];
int pwmFreq[40];
#endif

extern "C"
{
  extern char literal;
}
#ifdef OLED
  #include <U8g2lib.h>
  extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8x8;
  extern int oi;
#endif // OLED

#ifdef SSD1306OLED
  #include "SSD1306Wire.h"
  extern SSD1306Wire display;
  extern OLEDDISPLAY_COLOR OLEDcolor;
#endif

#ifdef BME280
  float temp, pressure, rh;
  void BME_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    bool status = bme.begin(0x76);
    if (!status)
      sendContent("Could not find a valid BME280 sensor, check wiring!");
    delay(200);
    bme.readTemperature();
    bme.readPressure();
    bme.readHumidity();
  }
  void BME_readTemp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    temp = bme.readTemperature() * 9 / 5 + 32; // *F
    ReturnValue->Val->FP = temp;
  }
  void BME_readPressure(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    pressure = bme.readPressure() * 29.53 / 100000; // in Hg
    ReturnValue->Val->FP = pressure;
  }
  void BME_readRH(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    rh = bme.readHumidity();
    ReturnValue->Val->FP = rh;
  }
#endif BME280

#ifdef TFT
  #include <TftGauge.h>
  #include <Hershey.h>
  extern TFT_eSPI tft;
  void drawJpeg(char *filename, int xpos, int ypos);
  void FontShow();
  extern Hershey HF;
#endif // TFT

void setFont(char *font);
#ifdef TFT
int nGauges = 0;
TftGauge *gauges[8];
void TFT_Gauge(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  Serial.println("Entered TftGauge constructer");
  float xc = Param[0]->Val->FP;
  float yc = Param[1]->Val->FP;
  float sang = Param[2]->Val->FP;
  float eang = Param[3]->Val->FP;
  float radius = Param[4]->Val->FP;
  float sval = Param[5]->Val->FP;
  float eval = Param[6]->Val->FP;
  int divisions = Param[7]->Val->Integer;
  float increments = Param[8]->Val->FP;
  int color = Param[9]->Val->Integer;
  char *fmt = (char *)Param[10]->Val->Pointer;
  char *valueFmt = (char *)Param[11]->Val->Pointer;
  if (nGauges < 8)
  {
    gauges[nGauges++] = new TftGauge(xc, yc, sang, eang, radius, sval, eval, divisions, increments, color, fmt, valueFmt);
    ReturnValue->Val->Integer = nGauges - 1;
  }
  else
    ReturnValue->Val->Integer = -1;
}
void TFT_Gauge_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // void draw(int gaugeNumber);
  int gaugeNumber = Param[0]->Val->Integer;
  if (gauges[gaugeNumber] != 0)
    gauges[gaugeNumber]->draw();
  else
    Serial.printf("GaugeNumber %d is not initialized\n", gaugeNumber);
}
void TFT_Gauge_drawDanger(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // void drawDanger(int gaugeNumber,float sangle,float eangle,int color);

  int gaugeNumber = Param[0]->Val->Integer;
  float sangle = Param[1]->Val->FP;
  float eangle = Param[2]->Val->FP;
  int color = Param[3]->Val->Integer;
  if (gauges[gaugeNumber] != 0)
    gauges[gaugeNumber]->drawDanger(sangle, eangle, color);
  else
    Serial.printf("GaugeNumber %d is not initialized\n", gaugeNumber);
}
void TFT_Gauge_drawDangerByValue(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int gaugeNumber = Param[0]->Val->Integer;
  float sangle = Param[1]->Val->FP;
  float eangle = Param[2]->Val->FP;
  int color = Param[3]->Val->Integer;
  if (gauges[gaugeNumber] != 0)
    gauges[gaugeNumber]->drawDangerByValue(sangle, eangle, color);
  else
    Serial.printf("GaugeNumber %d is not initialized\n", gaugeNumber);
  // void drawDangerByValue(int gaugeNumber,float svalue,float evalue,int color);
}
void TFT_Gauge_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // void setPosition(int gaugeNumber,float value);
  int gaugeNumber = Param[0]->Val->Integer;
  float value = Param[1]->Val->FP;
  if (gauges[gaugeNumber] != 0)
    gauges[gaugeNumber]->setPosition(value);
  else
    Serial.printf("GaugeNumber %d is not initialized\n", gaugeNumber);
}
void TFT_Gauge_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int i;
  for (i = 0; i < nGauges; i++)
    gauges[i]->~TftGauge();
  nGauges = 0;
}
int nVbars = 0;
TftVbarGraph *Vbars[8];
void TFT_VbarGraph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //(float x,float y,int width,int height,float sval,float eval,int divisions,float increments,int color,char * fmt,char * valueFmt);
  // Serial.println("Entered VbarGraph constructer");
  float x = Param[0]->Val->FP;
  float y = Param[1]->Val->FP;
  int width = Param[2]->Val->Integer;
  int height = Param[3]->Val->Integer;
  float sval = Param[4]->Val->FP;
  float eval = Param[5]->Val->FP;
  int divisions = Param[6]->Val->Integer;
  float increments = Param[7]->Val->FP;
  int color = Param[8]->Val->Integer;
  char *fmt = (char *)Param[9]->Val->Pointer;
  char *valueFmt = (char *)Param[10]->Val->Pointer;
  if (nVbars < 8)
  {
    Vbars[nVbars++] = new TftVbarGraph(x, y, width, height, sval, eval, divisions, increments, color, fmt, valueFmt);
    ReturnValue->Val->Integer = nVbars - 1;
  }
  else
    ReturnValue->Val->Integer = -1;
}
void TFT_VbarGraph_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int gaugeNumber = Param[0]->Val->Integer;
  if (Vbars[gaugeNumber] != 0)
    Vbars[gaugeNumber]->draw();
  else
    Serial.printf("VbarGauge %d is not initialized\n", gaugeNumber);
}
void TFT_VbarGraph_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int gaugeNumber = Param[0]->Val->Integer;
  float value = Param[1]->Val->FP;
  if (Vbars[gaugeNumber] != 0)
    Vbars[gaugeNumber]->setPosition(value);
  else
    Serial.printf("VbarGauge %d is not initialized\n", gaugeNumber);
}

void TFT_VbarGraph_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int i;
  for (i = 0; i < nVbars; i++)
    Vbars[i]->~TftVbarGraph();
  nVbars = 0;
}
int nHbars = 0;
TftHbarGraph *Hbars[8];
void TFT_HbarGraph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //(float x,float y,int width,int height,float sval,float eval,int divisions,float increments,int color,char * fmt,char * valueFmt);
  //  Serial.println("Entered HbarGraph constructer");
  float x = Param[0]->Val->FP;
  float y = Param[1]->Val->FP;
  int width = Param[2]->Val->Integer;
  int height = Param[3]->Val->Integer;
  float sval = Param[4]->Val->FP;
  float eval = Param[5]->Val->FP;
  int divisions = Param[6]->Val->Integer;
  float increments = Param[7]->Val->FP;
  int color = Param[8]->Val->Integer;
  char *fmt = (char *)Param[9]->Val->Pointer;
  char *valueFmt = (char *)Param[10]->Val->Pointer;
  if (nHbars < 8)
  {
    Hbars[nHbars++] = new TftHbarGraph(x, y, width, height, sval, eval, divisions, increments, color, fmt, valueFmt);
    ReturnValue->Val->Integer = nHbars - 1;
  }
  else
    ReturnValue->Val->Integer = -1;
}
void TFT_HbarGraph_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int gaugeNumber = Param[0]->Val->Integer;
  if (Hbars[gaugeNumber] != 0)
    Hbars[gaugeNumber]->draw();
  else
    Serial.printf("HbarGauge %d is not initialized\n", gaugeNumber);
}
void TFT_HbarGraph_setPosition(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int gaugeNumber = Param[0]->Val->Integer;
  float value = Param[1]->Val->FP;
  if (Hbars[gaugeNumber] != 0)
    Hbars[gaugeNumber]->setPosition(value);
  else
    Serial.printf("HbarGauge %d is not initialized\n", gaugeNumber);
}

void TFT_HbarGraph_dropGauges(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int i;
  for (i = 0; i < nHbars; i++)
    Hbars[i]->~TftHbarGraph();
  nHbars = 0;
}
// uint16_t * data[10241];
int slines = 8;
boolean screenServer(void);
boolean screenServer(String FileName);
int cCount = 0;
void iScroll() // internal function available in helper functions
{
  // scrolling vertical slices
  uint16_t *data = (uint16_t *)malloc(10241 * 2);
  int sw = 10240 / (240 - slines); // scroll width
  int sh = 240 - slines;           // scroll height
  int iters = 320 / sw;
  int remainder = (1.0 * 320 / sw - 320 / sw) * sw + 0.5;
  for (int j = 0; j < iters; j++)
  {
    tft.readRect(j * sw, slines, sw, sh, (uint16_t *)data);
    tft.pushRect(j * sw, 0, sw, sh, (uint16_t *)data);
  }
  if (remainder != 0)
  {
    tft.readRect(iters * sw, slines, remainder, sh, (uint16_t *)data);
    tft.pushRect(iters * sw, 0, remainder, sh, (uint16_t *)data);
  }
  free(data);
  tft.fillRect(0, 240 - slines, 320, slines, tft.textbgcolor);
}
void screenCapture(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  screenServer();
}
void scroll(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  iScroll();
}
void setScrollPixels(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int sa = Param[0]->Val->Integer;
  int oldSlines = slines;
  slines = sa;
  int sa2 = slines - oldSlines;
  if (sa2 > 0)
  {
    oldSlines = slines;
    slines = sa2;
    iScroll();
    slines = oldSlines;
  }
  tft.setCursor(0, 240 - slines);
  cCount = 0;
}
void consoleAlert(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
// char * what)
{
  cCount = 0;
  char *what = (char *)Param[0]->Val->Pointer;
  int fcolor = (int)tft.textcolor;
  int bcolor = tft.textbgcolor;
  tft.setTextColor(0, 0xf100);
  iScroll();
  int i;
  int sa = (int)tft.textsize;
  int llen = 320 / 6 / sa;
  int toScroll = 0;
  if (strlen(what) > llen)
  {
    toScroll = strlen(what) / llen;
    if (toScroll > 0)
      for (i = 0; i < toScroll; i++)
        iScroll();
  }
  tft.setCursor(0, 240 - slines - toScroll * toScroll);
  tft.print(what);
  tft.setTextColor((uint32_t)fcolor, (uint32_t)bcolor);
}
void iconsoleOut(char *what)
{
  char Buf[240];
  char *Bufp = (char *)&Buf;
  int toScroll = 0;
  char hasCR = 0;
  int i;
  strncpy(Bufp, what, 239);
  // DEBUGP.printf("Bufp in iConsole->%s\n",Bufp);
  if (strstr(Bufp, ">-> ") > 0)
  {
    Bufp = strstr(Bufp, ">->") + 4; // DEBUGP.print("d >-> ");
    // DEBUGP.println(Bufp);
  }
  if (Bufp[strlen(Bufp) - 1] == '\n')
  { // DEBUGP.print("has [CR]");
    hasCR = 1;
    Bufp[strlen(Bufp) - 1] = 0;
  }
  if (strstr(Bufp, "</td></tr>") > 0)
  {
    *strstr(Bufp, "</td></tr>") = 0; // DEBUGP.print("d </td></tr");
    // DEBUGP.println(Bufp);
  }
  if (strlen(Bufp) > 0) // DEBUGP.println(Bufp);
    int i;
  int sa = (int)tft.textsize;
  int llen = 320 / 6 / sa;
  // DEBUGP.printf("cCount is %d strlen(Bufp) is %d\n",cCount,strlen(Bufp));
  if ((strlen(Bufp) + cCount) > llen)
  {
    cCount += strlen(Bufp);
    // DEBUGP.printf("cCount updated to %d\n",cCount);
    toScroll += cCount / llen;
    if (toScroll > 0)
      for (i = 0; i < toScroll; i++)
      {
        iScroll();
        tft.cursor_y -= slines;
        cCount = cCount % llen;
      }
    cCount = cCount % llen;
    // DEBUGP.printf("cCount updated to %d\n",cCount);
  }
  if (strlen(Bufp) > 0)
  {
    tft.print(Bufp);
    if (toScroll == 0)
      cCount += strlen(Bufp); // DEBUGP.printf("tft.print(\"%s\")\n",Bufp);
  }

  if (hasCR == 1)
  {
    iScroll();
    tft.setCursor(0, 240 - slines); // DEBUGP.println("Ordered scroll for [CR]");
    cCount = 0;
  }
}
extern char toConsole;
void setConsoleOn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  int state = Param[0]->Val->Integer;
  toConsole = (char)state;
  if (state >= 1)
  {
    tft.fillScreen(0);
    tft.setCursor(0, 240 - slines);
    cCount = 0;
  }
  // DEBUGP.printf("tft.setCursor(0,%d)",240-slines);
}
void consoleOut(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
// char * what)
{
  char *what = (char *)Param[0]->Val->Pointer;

  iconsoleOut(what);
}
void HFsetCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int x,int y);
  int x = Param[0]->Val->Integer;
  int y = Param[1]->Val->Integer;
  HF.setCursor(x, y);
}
void HFsetStrokeDelay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int delay);
  int delay = Param[0]->Val->Integer;
  HF.setStrokeDelay(delay);
}
void HFdrawStringRotated(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int x,int y,int r,float scale,int color,float a,char * string);
  int x = Param[0]->Val->Integer;
  int y = Param[1]->Val->Integer;
  int r = Param[2]->Val->Integer;
  float scale = Param[3]->Val->FP;
  int color = Param[4]->Val->Integer;
  float a = Param[5]->Val->FP;
  char *string = (char *)Param[6]->Val->Pointer;
  HF.drawStringRotated(x, y, r, scale, color, a, string);
  // draw string rotated only works for up to two character strings and was
  // produced to support drawing circular guage annotations
  // with some math you can use it to draw test along circles or angled lines
}
void HFdrawString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int x,int y,float scale,int color,char * string);
  int x = Param[0]->Val->Integer;
  int y = Param[1]->Val->Integer;
  float scale = Param[2]->Val->FP;
  int color = Param[3]->Val->Integer;
  char *string = (char *)Param[4]->Val->Pointer;
  HF.drawString(x, y, scale, color, string);
}
void HFdrawStringOpaque(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int x,int y,float scale,int fcolor,int bcolor,char * string);
  int x = Param[0]->Val->Integer;
  int y = Param[1]->Val->Integer;
  float scale = Param[2]->Val->FP;
  int fcolor = Param[3]->Val->Integer;
  int bcolor = Param[4]->Val->Integer;
  char *string = (char *)Param[5]->Val->Pointer;
  HF.drawStringOpaque(x, y, scale, fcolor, bcolor, string);
}
void HFdrawCenteredString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int y,float scale,int color,char * string);
  int y = Param[0]->Val->Integer;
  float scale = Param[1]->Val->FP;
  int color = Param[2]->Val->Integer;
  char *string = (char *)Param[3]->Val->Pointer;
  HF.drawCenteredString(y, scale, color, string);
}
void HFgetStringSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // char * it,float scale); returns int
  char *string = (char *)Param[0]->Val->Pointer;
  float scale = Param[1]->Val->FP;
  int rv = HF.getStringSize(string, scale);
  ReturnValue->Val->Integer = rv;
}
void HFdraw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // char chr,float scale,int color);
  char chr = Param[0]->Val->Character;
  float scale = Param[1]->Val->FP;
  int color = Param[2]->Val->Integer;
  HF.draw(chr, scale, color);
}
void HFdrawRotated(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // int xc,int yc,char chr,float scale,int color,float angle);
  int xc = Param[0]->Val->Integer;
  int yc = Param[1]->Val->Integer;
  char chr = Param[2]->Val->Character;
  float scale = Param[3]->Val->FP;
  int color = Param[4]->Val->Integer;
  float angle = Param[5]->Val->FP;
  HF.drawRotated(xc, yc, chr, scale, color, angle);
}
void HFsetFont(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  char *str = (char *)Param[0]->Val->Pointer;
  HF.setFont(str);
}
#endif
// extern struct StackFrame *TopStackFrame;

// const char *Ident;
extern void sendContent(const char *it);
extern void send(char *it);
extern void sendc(char it);
extern void sendln(char *it);
#ifdef ESP32
#include <WebServer.h>
#else
#include <ESP8266WebServer.h>
#endif
#ifdef ESP32
extern WebServer server;
#else
extern ESP8266WebServer server;
#endif
#include <Arduino.h>

extern "C"
{
  #include "myPicoc.h"
  #include "myInterpreter.h"
  #include "myVariable.h"
  // struct StackFrame *TopStackFrame;     //lyx
  extern char listIncludes;
#ifndef ESP32
#include "user_interface.h"
#endif // ESP32
}

extern "C"
{
  extern char SingleStep;

  /* the picoc version string */
  // static const char *VersionString = NULL;
  const char *VersionString = NULL;
  /* endian-ness checking */
  const int __ENDIAN_CHECK__ = 1;
  int BigEndian = 0;
  int LittleEndian = 0;

  int nwatches = 0;
  char watches[20][33];
  void stopDebug(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    SingleStep = 0;
  }
  void Debug(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    SingleStep = 1;
  }
  void Watch(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int i;
    char *what = (char *)Param[0]->Val->Pointer;
    for (i = 0; i < nwatches; i++)
      if (strcmp((char *)&watches[i][0], what) == 0)
      {
        // Ssend("Watch already in place");
        return;
      }
    //  sprint("Adding watch for ");sprint(what);sprint("\n");
    strncpy((char *)&watches[nwatches++][0], what, 32);
    char fbuf[20];
    // snprintf((char *)&fbuf,32,"%d watches in place\n",nwatches);
    // sprint((char *)&fbuf);
  }
  void dropWatch(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *what = (char *)Param[0]->Val->Pointer;
    if (nwatches == 0)
      return;
    for (int i = 0; i < nwatches; i++)
    {
      if (strcmp((char *)&watches[i][0], what) == 0) // found matching watch variable
      {
        // Serial.printf("Found watched item %s at line %d\n",what,i);
        for (int j = i; j < nwatches; j++)
        {
          strncpy((char *)&watches[j][0], (char *)&watches[j + 1][0], 32);
        }
        nwatches--;
      }
    }
  }
  /* global initialisation for libraries */
  void LibraryInit()
  {
    /* define the version number macro */
    VersionString = TableStrRegister(PICOC_VERSION);
    VariableDefinePlatformVar(NULL, "PICOC_VERSION", CharPtrType, (union AnyValue *)&VersionString, FALSE);

    /* define endian-ness macros */
    BigEndian = ((*(char *)&__ENDIAN_CHECK__) == 0);
    LittleEndian = ((*(char *)&__ENDIAN_CHECK__) == 1);

    VariableDefinePlatformVar(NULL, "BIG_ENDIAN", &IntType, (union AnyValue *)&BigEndian, FALSE);
    VariableDefinePlatformVar(NULL, "LITTLE_ENDIAN", &IntType, (union AnyValue *)&LittleEndian, FALSE);
  }

  /* add a library */
  void LibraryAdd(struct Table *GlobalTable, const char *LibraryName, struct LibraryFunction *FuncList)
  {
    struct ParseState Parser;
    int Count;
    char *Identifier;
    struct ValueType *ReturnType;
    struct Value *NewValue;
    void *Tokens;
    char *IntrinsicName = TableStrRegister("c library");

    /* read all the library definitions */
    for (Count = 0; FuncList[Count].Prototype != NULL; Count++)
    {
      // Ssend((char *)FuncList[Count].Prototype);Ssend("\n");
      Tokens = LexAnalyse(IntrinsicName, FuncList[Count].Prototype, strlen((char *)FuncList[Count].Prototype), NULL);
      LexInitParser(&Parser, FuncList[Count].Prototype, Tokens, IntrinsicName, TRUE, FALSE);
      TypeParse(&Parser, &ReturnType, &Identifier, NULL);
      NewValue = ParseFunctionDefinition(&Parser, ReturnType, Identifier);
      NewValue->Val->FuncDef.Intrinsic = (void (*)())FuncList[Count].Func;
      HeapFreeMem(Tokens);
    }
  }

  /* print a type to a stream without using printf/sprintf */
  void PrintType(struct ValueType *Typ)
  {
    char b[21];
    snprintf((char *)&b, 20, "Type is #%d\n", Typ->Base);
    switch (Typ->Base)
    {
    case TypeVoid:
      PrintAndWebOut(F("void"));
      break;
    case TypeInt:
      PrintAndWebOut(F("int"));
      break;
    case TypeShort:
      PrintAndWebOut(F("short"));
      break;
    case TypeChar:
      PrintAndWebOut(F("char"));
      break;
    case TypeLong:
      PrintAndWebOut(F("long"));
      break;
    case TypeUnsignedInt:
      PrintAndWebOut(F("unsigned int"));
      break;
    case TypeUnsignedShort:
      PrintAndWebOut(F("unsigned short"));
      break;
    case TypeUnsignedLong:
      PrintAndWebOut(F("unsigned long"));
      break;
#ifndef NO_FP
    case TypeFP:
      PrintAndWebOut(F("double"));
      break;
#endif // NO_FP
    case TypeFunction:
      PrintAndWebOut(F("function"));
      break;
    case TypeMacro:
      PrintAndWebOut(F("macro"));
      break;
    case TypePointer:
      if (Typ->FromType)
        PrintType(Typ->FromType);
      PrintAndWebOut(F("*"));
      break;
    case TypeArray:
      PrintType(Typ->FromType);
      PrintAndWebOut(F("["));
      if (Typ->ArraySize != 0)
      {
        snprintf((char *)&b, 20, "%d", Typ->ArraySize);
        PrintAndWebOut((char *)&b);
      }
      PrintAndWebOut(F("]"));
      break;
    case TypeStruct:
      PrintAndWebOut(F("struct "));
      PrintAndWebOut((char *)Typ->Identifier);
      break;
    case TypeUnion:
      PrintAndWebOut(F("union "));
      PrintAndWebOut((char *)Typ->Identifier);
      break;
    case TypeEnum:
      PrintAndWebOut(F("enum "));
      PrintAndWebOut((char *)Typ->Identifier);
      break;
    case TypeGotoLabel:
      PrintAndWebOut(F("goto label "));
      break;
    case Type_Type:
      PrintAndWebOut(F("type "));
      break;
    }
  }

#ifdef BUILTIN_MINI_STDLIB

  /*
   * This is a simplified standard library for small embedded systems. It doesn't require a system stdio library to operate.
   * A more complete standard library for larger computers is in the library_XXX.c files.
   */

  IOFILE *CStdOut;
  IOFILE CStdOutBase;

  static int TRUEValue = 1;
  static int ZeroValue = 0;

  void BasicIOInit()
  {
    //    CStdOutBase.Putch = &PlatformPutc;
    CStdOut = &CStdOutBase;
  }

  /* initialise the C library */
  void CLibraryInit()
  {
    /* define some constants */
    VariableDefinePlatformVar(NULL, "NULL", &IntType, (union AnyValue *)&ZeroValue, FALSE);
    VariableDefinePlatformVar(NULL, "TRUE", &IntType, (union AnyValue *)&TRUEValue, FALSE);
    VariableDefinePlatformVar(NULL, "FALSE", &IntType, (union AnyValue *)&ZeroValue, FALSE);
  }

  /* stream for writing into strings */
  void SPutc(unsigned char Ch)
  {
    PrintAndWebOut((char *)&Ch); // struct StringOutputStream *Out = &Stream->Str;
    //*Out->WritePos++ = Ch;
  }

  /* print a character to a stream without using printf/sprintf */
  void PrintCh(char OutCh)
  {
    char lb[3];
    snprintf((char *)&lb, 2, "%c", OutCh);
    lb[1] = 0;
    sprint((char *)&lb);
  }

  /* print a string to a stream without using printf/sprintf */
  void PrintStr(const char *Str)
  {
    sprint((char *)Str);
  }

  /* print a single character a given number of times */
  void PrintRepeatedChar(char ShowChar, int Length)
  {
    while (Length-- > 0)
      PrintCh(ShowChar);
  }

  /* print an unsigned integer to a stream without using printf/sprintf */
  void PrintUnsigned(unsigned long Num, unsigned int Base, int FieldWidth, int ZeroPad, int LeftJustify)
  {
    char Result[33];
    int ResPos = sizeof(Result);

    Result[--ResPos] = '\0';
    if (Num == 0)
      Result[--ResPos] = '0';

    while (Num > 0)
    {
      unsigned long NextNum = Num / Base;
      unsigned long Digit = Num - NextNum * Base;
      if (Digit < 10)
        Result[--ResPos] = '0' + Digit;
      else
        Result[--ResPos] = 'a' + Digit - 10;

      Num = NextNum;
    }

    if (FieldWidth > 0 && !LeftJustify)
      PrintRepeatedChar(ZeroPad ? '0' : ' ', FieldWidth - (sizeof(Result) - 1 - ResPos));

    PrintCh((char)Result[ResPos]);

    if (FieldWidth > 0 && LeftJustify)
      PrintRepeatedChar(' ', FieldWidth - (sizeof(Result) - 1 - ResPos));
  }

  /* print an integer to a stream without using printf/sprintf */
  void PrintSimpleInt(long Num)
  {
    char lbuf[21];
    snprintf((char *)&lbuf, 20, "%d", Num);
    sprint((char *)&lbuf); // PrintInt(Num, -1, FALSE, FALSE);
  }

  /* print an integer to a stream without using printf/sprintf */
  void PrintInt(long Num, int FieldWidth, int ZeroPad, int LeftJustify)
  {
    if (Num < 0)
    {
      PrintCh('-');
      Num = -Num;
      if (FieldWidth != 0)
        FieldWidth--;
    }

    PrintUnsigned((unsigned long)Num, 10, FieldWidth, ZeroPad, LeftJustify);
  }

#ifndef NO_FP
  /* print a double to a stream without using printf/sprintf */
  void PrintFP(double Num)
  {
    int Exponent = 0;
    int MaxDecimal;

    if (Num < 0)
    {
      char min = '-';
      PrintCh(min);
      Num = -Num;
    }

    if (Num >= 1e7)
      Exponent = log10(Num);
    else if (Num <= 1e-7 && Num != 0.0)
      Exponent = log10(Num) - 0.999999999;

    Num /= pow(10.0, Exponent);
    PrintInt((long)Num, 0, FALSE, FALSE);
    char dot = '.';
    PrintCh(dot);
    Num = (Num - (long)Num) * 10;
    char z = '0';
    if (abs(Num) >= 1e-7)
    {
      for (MaxDecimal = 6; MaxDecimal > 0 && abs(Num) >= 1e-7; Num = (Num - (long)(Num + 1e-7)) * 10, MaxDecimal--)
        PrintCh(z);
      char lbuf[21];
      snprintf((char *)&lbuf, 20, "%f", Num + 1e-7);
      PrintAndWebOut((char *)&lbuf);
    }
    else
      PrintCh(z);

    if (Exponent != 0)
    {
      char e = 'e';
      PrintCh(e);
      PrintInt(Exponent, 0, FALSE, FALSE);
    }
  }
#endif // NO_FP

  void PrintWithCommas(unsigned long n, int width)
  {
    char Bf[201];
    int m[4], i;
    unsigned long nh;
    nh = n;
    int wd = log10(n) + 1;
    wd = wd + (wd - 1) / 3;
    for (i = wd; i < width; i++)
      sendContent(" ");
    for (i = 0; i < 4; i++)
    {
      m[i] = n % 1000;
      n = n / 1000;
    }
    if (nh < 1000)
      snprintf((char *)&Bf, 200, "%d", m[0]);
    else if (nh < 1000000)
      snprintf((char *)&Bf, 200, "%d,%03d", m[1], m[0]);
    else if (nh < 1000000000)
      snprintf((char *)&Bf, 200, "%d,%03d,%03d", m[2], m[1], m[0]);
    else
      snprintf((char *)&Bf, 200, "%d,%03d,%03d,%03d", m[3], m[2], m[1], m[0]);
    PrintAndWebOut((char *)&Bf);
    return;
  }

  /* intrinsic functions made available to the language */
  void GenericPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //DebugP.println("Entered GenericPrintf");
    // literal = 1;
    sendContent("<tr><td colspan=\"2\" style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:10px; FONT-FAMILY:Courier\">-> ");
    literal = 0;

    char Bf[501], Buf[501];
    char *FPos;
    struct Value *NextArg = Param[0];
    struct ValueType *FormatType;
    int ArgCount = 1;

    char *Format = (char *)Param[0]->Val->Pointer;
    int ip = 0;

    for (FPos = Format; *FPos != '\0'; FPos++)
    {
      while (*FPos != '%' && *FPos != 0)
        Buf[ip++] = *FPos++;
      if (*FPos == 0)
      {
        Buf[ip] = 0;
        String hit;
        int len = strlen((char *)&Buf);
        int i;
        for (i = 0; i < len; i++)
        {
          if (Buf[i] != 13)
            hit += Buf[i];
          else if (Buf[i] == 13)
            hit += "<br/>";
          // else if (Buf[i]==10) hit+="<br/>";
          // else if (Buf[i]==' ') hit+="&nbsp;";
        }
        send((char *)hit.c_str());
        break;
      }
      if (*FPos == '%')
      {
        Buf[ip++] = *FPos++;
        while (isdigit((int)*FPos) || *FPos == '.' || *FPos == '-')
          Buf[ip++] = *FPos++;
        Buf[ip++] = *FPos;
        Buf[ip] = 0;

        /* now check the format type */
        switch (*FPos)
        {
        case 's':
          FormatType = CharPtrType;
          break;
        case 'd':
        case 'u':
        case 'x':
        case 'X':
        case 'b':
        case 'c':
        case ',':
          FormatType = &IntType;
          break;
#ifndef NO_FP
        case 'f':
          FormatType = &FPType;
          break;
#endif // NO_FP
        case '%':
        {
          Buf[--ip] = 0;
          ip = 0;
          send((char *)&Buf);
          strcpy((char *)&Buf, "");
          FormatType = NULL;
          break;
        }
        case '\0':
          FPos--;
          FormatType = NULL;
          break;
        default:
          sendc(*FPos);
          FormatType = NULL;
          break;
        }

        if (FormatType != NULL)
        {
          /* we have to format something */
          if (ArgCount >= NumArgs)
            sendContent("XXX too few params");                        /* not enough parameters for format */
          else
          {
            NextArg = (struct Value *)((char *)NextArg + MEM_ALIGN(sizeof(struct Value) + TypeStackSizeValue(NextArg)));
            if (NextArg->Typ != FormatType &&
                !((FormatType == &IntType || *FPos == 'f') && IS_NUMERIC_COERCIBLE(NextArg)) &&
                !(FormatType == CharPtrType && (NextArg->Typ->Base == TypePointer ||
                                                (NextArg->Typ->Base == TypeArray && NextArg->Typ->FromType->Base == TypeChar))))
              sendContent("XXX bad type1\n");                         /* bad type for format */

            else
            {
              switch (*FPos)
              {
              case 's':
              {
                char *Str;
                // Serial.println("doing a string expansion");
                if (NextArg->Typ->Base == TypePointer)
                  Str = (char *)NextArg->Val->Pointer;
                else
                  Str = &NextArg->Val->ArrayMem[0];

                if (Str == NULL)
                  sendContent("NULL");
                else
                  snprintf((char *)&Bf, 200, (char *)&Buf, Str);
                Serial.printf("string expansion for format %s is %s\n",(char *)&Buf,(char *)&Bf);
                sendContent((char *)&Bf);
                break;
              }

              case 'd':
                printf("doing int with format %s and num %d\n",(char *)&Buf,ExpressionCoerceInteger(NextArg));
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceInteger(NextArg));
                sendContent((char *)&Bf);
                break;
              case 'u':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                sendContent((char *)&Bf);
                break;
              case 'x':
              case 'X':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                sendContent((char *)&Bf);
                break;
              case 'b':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                sendContent((char *)&Bf);
                break;
              case 'c':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                sendContent((char *)&Bf);
                break;
              case ',':
              { // handle the new , format type
                char *cp;
                cp = strstr((char *)&Buf, "%");
                if (cp != (char *)&Buf)
                {
                  *cp = 0;
                  snprintf((char *)&Bf, 200, "%s", (char *)&Buf);
                  sendContent((char *)&Bf);
                  cp++;
                }
                int wd = 0;
                while (isdigit((int)*cp))
                  wd = wd * 10 + *cp++ - '0';
                PrintWithCommas((unsigned long)ExpressionCoerceUnsignedInteger(NextArg), wd);
                break;
              }
#ifndef NO_FP
              case 'f':
              {
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceFP(NextArg));
                sendContent((char *)&Bf);
                break;
              }
#endif // NO_FP
                FPos++;
              }
            }

            ArgCount++;
            ip = 0;
          }
        }
        // else
        // PrintCh(*FPos, Stream);
      }
    }
    sendContent("</td></tr>");
  }

  /* printf(): print to console output */
  void LibPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // struct OutputStream ConsoleStream;

    // ConsoleStream.Putch = &PlatformPutc;
    GenericPrintf(Parser, ReturnValue, Param, NumArgs);
  }
  void LibPrint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // struct OutputStream ConsoleStream;

    // ConsoleStream.Putch = &PlatformPutc;
    GenericPrintf(Parser, ReturnValue, Param, NumArgs);
  }
  /* sprintf(): print to a string */
  void LibSPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // Serial.println("In LibSPrintf");
    char Bf[501], Buf[501];
    char *FPos;
    struct Value *NextArg = Param[1];
    struct ValueType *FormatType;
    int ArgCount = 1;
    
    char *oBuf = (char *)Param[0]->Val->Pointer;
    strcpy((char *)oBuf, "");
    char *Format = (char *)Param[1]->Val->Pointer;
    int ip = 0;
    //  Serial.println("Got to ip=0;");
    //  Serial.println(Format);

    for (FPos = Format; *FPos != '\0'; FPos++)
    {
      while (*FPos != '%' && *FPos != 0)
        Buf[ip++] = *FPos++;
      if (*FPos == 0)
      {
        Buf[ip] = 0;
        strncat(oBuf, (char *)&Buf, 500);
        break;
      }
      if (*FPos == '%')
      {
        //      Serial.println("Got to format specifier");
        Buf[ip++] = *FPos++;
        while (isdigit((int)*FPos) || *FPos == '.' || *FPos == '-')
          Buf[ip++] = *FPos++;
        Buf[ip++] = *FPos;
        Buf[ip] = 0;

        /* now check the format type */
        switch (*FPos)
        {
        case 's':
          FormatType = CharPtrType;
          break;
        case 'd':
        case 'u':
        case 'x':
        case 'X':
        case 'b':
        case 'c':
        case ',':
          FormatType = &IntType;
          break;
#ifndef NO_FP
        case 'f':
          FormatType = &FPType;
          break;
#endif // NO_FP
        case '%':
        {
          Buf[--ip] = 0;
          ip = 0;
          strncat(oBuf, (char *)&Buf, 500);
          strcpy((char *)&Buf, "");
          FormatType = NULL;
          break;
        }
        case '\0':
          FPos--;
          FormatType = NULL;
          break;
        default:
          strncat(oBuf, (char *)*FPos, 500);
          FormatType = NULL;
          break;
        }

        if (FormatType != NULL)
        {
          /* we have to format something */
          if (ArgCount >= NumArgs)
            strncat(oBuf, "XXX too few params", 500); /* not enough parameters for format */
          else
          {
            NextArg = (struct Value *)((char *)NextArg + MEM_ALIGN(sizeof(struct Value) + TypeStackSizeValue(NextArg)));
            if (NextArg->Typ != FormatType &&
                !((FormatType == &IntType || *FPos == 'f') && IS_NUMERIC_COERCIBLE(NextArg)) &&
                !(FormatType == CharPtrType && (NextArg->Typ->Base == TypePointer ||
                                                (NextArg->Typ->Base == TypeArray && NextArg->Typ->FromType->Base == TypeChar))))
              strncat(oBuf, "XXX bad type", 500); /* bad type for format */
            else
            {
              switch (*FPos)
              {
              case 's':
              {
                char *Str;

                if (NextArg->Typ->Base == TypePointer)
                  Str = (char *)NextArg->Val->Pointer;
                else
                  Str = &NextArg->Val->ArrayMem[0];

                if (Str == NULL)
                  strncat(oBuf, "NULL", 500);
                else
                  snprintf((char *)&Bf, 200, (char *)&Buf, Str);
                strncat(oBuf, (char *)&Bf, 500);
                break;
              }
              case 'd':
                //  printf("doing int with format %s and num %d\n",(char *)&Buf,ExpressionCoerceInteger(NextArg));
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceInteger(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              case 'u':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              case 'x':
              case 'X':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              case 'b':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              case 'c':
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceUnsignedInteger(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              case ',':
              { // handle the new , format type
                char *cp;
                cp = strstr((char *)&Buf, "%");
                *cp = 0;
                snprintf((char *)&Bf, 200, "%s", (char *)&Buf);
                strncat(oBuf, (char *)&Bf, 500);
                cp++;
                int wd = 0;
                while (isdigit((int)*cp))
                  wd = wd * 10 + *cp++ - '0';
                PrintWithCommas((unsigned long)ExpressionCoerceUnsignedInteger(NextArg), wd);
                break;
              }
#ifndef NO_FP
              case 'f':
              {
                snprintf((char *)&Bf, 200, (char *)&Buf, ExpressionCoerceFP(NextArg));
                strncat(oBuf, (char *)&Bf, 500);
                break;
              }
#endif // NO_FP
                FPos++;
              }
            }

            ArgCount++;
            ip = 0;
          }
        }
        //  else
        //  PrintCh(*FPos, Stream);
      }
    }
    //  Serial.print(oBuf);
  }

  /* get a line of input. protected from buffer overrun */
  void LibGets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char prompt[] = "";
    ReturnValue->Val->Pointer = (char *)PlatformGetLine((char *)Param[0]->Val->Pointer, GETS_BUF_MAX, (char *)&prompt);
    if (ReturnValue->Val->Pointer != NULL)
    {
      char *EOLPos = (char *)strchr((char *)Param[0]->Val->Pointer, '\n');
      if (EOLPos != NULL)
        *EOLPos = '\0';
    }
  }

  void LibGetc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = PlatformGetCharacter();
  }

  void LibExit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    PlatformExit(Param[0]->Val->Integer);
  }
#define PICOC_LIBRARY
#ifdef PICOC_LIBRARY

#ifndef NO_FP
  void StdlibAtof(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = atof((char *)Param[0]->Val->Pointer);
  }
#endif // NO_FP

  void StdlibAtoi(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = atoi((char *)Param[0]->Val->Pointer);
  }

  void StdlibAtol(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = atol((char *)Param[0]->Val->Pointer);
  }

#ifndef NO_FP
  void StdlibStrtod(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = strtod((char *)Param[0]->Val->Pointer, (char **)Param[1]->Val->Pointer);
  }
#endif // NO_FP

  void StdlibStrtol(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = strtol((char *)Param[0]->Val->Pointer, (char **)Param[1]->Val->Pointer, Param[2]->Val->Integer);
  }

  void StdlibStrtoul(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = strtoul((char *)Param[0]->Val->Pointer, (char **)Param[1]->Val->Pointer, Param[2]->Val->Integer);
  }

  void StdlibRand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = rand();
  }

  void StdlibSrand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    srand(Param[0]->Val->Integer);
  }

  void StdlibAbs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = abs(Param[0]->Val->Integer);
  }

  void StdlibLabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = labs(Param[0]->Val->Integer);
  }

  void LibSin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = sin(Param[0]->Val->FP);
  }

  void LibCos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = cos(Param[0]->Val->FP);
  }

  void LibTan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = tan(Param[0]->Val->FP);
  }

  void LibAsin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = asin(Param[0]->Val->FP);
  }

  void LibAcos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = acos(Param[0]->Val->FP);
  }

  void LibAtan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = atan(Param[0]->Val->FP);
  }

  void LibSinh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = sinh(Param[0]->Val->FP);
  }

  void LibCosh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = cosh(Param[0]->Val->FP);
  }

  void LibTanh(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = tanh(Param[0]->Val->FP);
  }

  void LibExp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = exp(Param[0]->Val->FP);
  }

  void LibFabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = fabs(Param[0]->Val->FP);
  }

  void LibLog(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = log(Param[0]->Val->FP);
  }

  void LibLog10(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = log10(Param[0]->Val->FP);
  }

  void LibPow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = pow(Param[0]->Val->FP, Param[1]->Val->FP);
  }

  void LibSqrt(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = sqrt(Param[0]->Val->FP);
  }

  void LibRound(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = floor(Param[0]->Val->FP + 0.5); /* XXX - fix for soft float */
  }

  void LibCeil(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = ceil(Param[0]->Val->FP);
  }

  void LibFloor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->FP = floor(Param[0]->Val->FP);
  }
#endif // PICOC_LIBRARY

#ifndef NO_STRING_FUNCTIONS
  void LibMalloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Pointer = malloc(Param[0]->Val->Integer);
  }

#ifndef NO_CALLOC
  void LibCalloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Pointer = calloc(Param[0]->Val->Integer, Param[1]->Val->Integer);
  }
#endif // NO_CALLOC

#ifndef NO_REALLOC
  void LibRealloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Pointer = realloc(Param[0]->Val->Pointer, Param[1]->Val->Integer);
  }
#endif // NO_REALLOC

  void LibFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    free(Param[0]->Val->Pointer);
  }

  void Libstrcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *To = (char *)Param[0]->Val->Pointer;
    char *From = (char *)Param[1]->Val->Pointer;
    int ccount = 0;
    while (*From != '\0')
      *To++ = *From++;

    *To = '\0';
  }

  void LibStrncpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *To = (char *)Param[0]->Val->Pointer;
    char *From = (char *)Param[1]->Val->Pointer;
    int Len = Param[2]->Val->Integer;

    for (; *From != '\0' && Len > 0; Len--)
      *To++ = *From++;

    if (Len > 0)
      *To = '\0';
  }

  void LibStrcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Str1 = (char *)Param[0]->Val->Pointer;
    char *Str2 = (char *)Param[1]->Val->Pointer;
    int StrEnded;

    for (StrEnded = FALSE; !StrEnded; StrEnded = (*Str1 == '\0' || *Str2 == '\0'), Str1++, Str2++)
    {
      if (*Str1 < *Str2)
      {
        ReturnValue->Val->Integer = -1;
        return;
      }
      else if (*Str1 > *Str2)
      {
        ReturnValue->Val->Integer = 1;
        return;
      }
    }

    ReturnValue->Val->Integer = 0;
  }

  void LibStrncmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Str1 = (char *)Param[0]->Val->Pointer;
    char *Str2 = (char *)Param[1]->Val->Pointer;
    int Len = Param[2]->Val->Integer;
    int StrEnded;

    for (StrEnded = FALSE; !StrEnded && Len > 0; StrEnded = (*Str1 == '\0' || *Str2 == '\0'), Str1++, Str2++, Len--)
    {
      if (*Str1 < *Str2)
      {
        ReturnValue->Val->Integer = -1;
        return;
      }
      else if (*Str1 > *Str2)
      {
        ReturnValue->Val->Integer = 1;
        return;
      }
    }

    ReturnValue->Val->Integer = 0;
  }

  void Libstrcat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *To = (char *)Param[0]->Val->Pointer;
    char *From = (char *)Param[1]->Val->Pointer;

    while (*To != '\0')
      To++;

    while (*From != '\0')
      *To++ = *From++;

    *To = '\0';
  }
  void Libstrncat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *To = (char *)Param[0]->Val->Pointer;
    char *From = (char *)Param[1]->Val->Pointer;
    int len = Param[2]->Val->Integer;

    while (*To != '\0')
      To++;

    while (*From != '\0' && len-- > 0)
      *To++ = *From++;

    *To = '\0';
  }
  void LibIndex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Pos = (char *)Param[0]->Val->Pointer;
    int SearchChar = Param[1]->Val->Integer;

    while (*Pos != '\0' && *Pos != SearchChar)
      Pos++;

    if (*Pos != SearchChar)
      ReturnValue->Val->Pointer = NULL;
    else
      ReturnValue->Val->Pointer = Pos;
  }

  void LibRindex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Pos = (char *)Param[0]->Val->Pointer;
    int SearchChar = Param[1]->Val->Integer;

    ReturnValue->Val->Pointer = NULL;
    for (; *Pos != '\0'; Pos++)
    {
      if (*Pos == SearchChar)
        ReturnValue->Val->Pointer = Pos;
    }
  }

  void LibStrlen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Pos = (char *)Param[0]->Val->Pointer;
    int Len;

    for (Len = 0; *Pos != '\0'; Pos++)
      Len++;

    ReturnValue->Val->Integer = Len;
  }

  void LibMemset(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    /* we can use the system memset() */
    memset(Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer);
  }

  void LibMemcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    /* we can use the system memcpy() */
    memcpy(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer);
  }

  void LibMemcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    unsigned char *Mem1 = (unsigned char *)Param[0]->Val->Pointer;
    unsigned char *Mem2 = (unsigned char *)Param[1]->Val->Pointer;
    int Len = Param[2]->Val->Integer;

    for (; Len > 0; Mem1++, Mem2++, Len--)
    {
      if (*Mem1 < *Mem2)
      {
        ReturnValue->Val->Integer = -1;
        return;
      }
      else if (*Mem1 > *Mem2)
      {
        ReturnValue->Val->Integer = 1;
        return;
      }
    }

    ReturnValue->Val->Integer = 0;
  }

#endif BUILTIN_MINI_STDLIB
  // library additions for character/graphics display mainpulation

#ifdef SSD1306OLED
  int oline = 0;
  int oWidth = 64;
  int oHeight = 48;
  int oLines = 6;
  int oChars = 32;
  int cx, cy;
  char ochars[6][33];
  void oclear(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    display.clear();
    display.display();
    display.setContrast(20);
    display.setBrightness(30);
    OLEDdidWhen = millis();
    cx = 0;
    cy = 0;
  }
  void oinvertDisplay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int invert = Param[0]->Val->Integer;
    if (invert == 1)
      display.invertDisplay();
    else
      display.normalDisplay();
  }
  void onormalDisplay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int invert = Param[0]->Val->Integer;
    display.normalDisplay();
  }
  void odisplay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    display.display();
    OLEDdidWhen = millis();
  }
  void osetPixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    display.setPixel(x, y);
    OLEDdidWhen = millis();
  }
  void odrawLine(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x0 = Param[0]->Val->Integer;
    int y0 = Param[1]->Val->Integer;
    int x1 = Param[2]->Val->Integer;
    int y1 = Param[3]->Val->Integer;
    display.drawLine(x0, y0, x1, y1);
    OLEDdidWhen = millis();
  }
  void odrawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    display.drawRect(x, y, w, h);
    OLEDdidWhen = millis();
  }
  void ofillRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    display.fillRect(x, y, w, h);
    OLEDdidWhen = millis();
  }

  void osetCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    cx = Param[0]->Val->Integer;
    cy = Param[1]->Val->Integer;
    OLEDdidWhen = millis();
  }
  void osetFontSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int fontIndex = Param[0]->Val->Integer;
    if (fontIndex < 1 || fontIndex > 3)
      Serial.printf("Only font sizes of 1-3 allowed\n");
    if (fontIndex == 1)
      display.setFont(ArialMT_Plain_10);
    if (fontIndex == 2)
      display.setFont(ArialMT_Plain_16);
    if (fontIndex == 3)
      display.setFont(ArialMT_Plain_24);
    OLEDdidWhen = millis();
  }
  void osetColor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int color = Param[0]->Val->Integer;
    display.setColor((OLEDDISPLAY_COLOR)color);
    OLEDdidWhen = millis();
  }
  void odrawString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int x = Param[0]->Val->Integer;
    int y = Param[1]->Val->Integer;
    char *str = (char *)Param[2]->Val->Pointer;
    display.setColor((OLEDDISPLAY_COLOR)BLACK);
    display.fillRect(x, y, 8, 128 - x);
    display.setColor((OLEDDISPLAY_COLOR)WHITE);
    display.drawString(x, y, str);
    OLEDdidWhen = millis();
  }
  void oprint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *str = (char *)Param[0]->Val->Pointer;
    display.print(str);
    OLEDdidWhen = millis();
  }
  void oprintln(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *str = (char *)Param[0]->Val->Pointer;
    display.println(str);
    OLEDdidWhen = millis();
  }
  void oconsolePrintln(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *str = (char *)Param[0]->Val->Pointer;
    if (oline >= 1)
    {
      display.clear();
      oline = 0;
      cx = 0;
      cy = oline * 10;
      // scroll before output
      for (int i = 1; i < 6; i++)
      {
        strncpy((char *)&ochars[i - 1][0], (char *)&ochars[i][0], 32);
        display.drawString(0, (i - 1) * 10, (char *)&ochars[i][0]);
      }
      display.display();
    }
    else
    {
      cx = 0;
      cy = oline * 10;
    }
    if (strlen(str) > oChars)
      *(str + oChars) = 0;
    display.drawString(0, 50, str);
    strncpy((char *)&ochars[5][0], str, 32);
    oline++;
    display.display();
    OLEDdidWhen = millis();
  }
  void oconsoleInit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    for (int i = 0; i < 6; i++)
      strcpy((char *)&ochars[i][0], "");
    display.clear();
    display.display();
    OLEDdidWhen = millis();
  }
#endif SSD1306OLED


#ifdef TFT
  void TFT_invertDisplay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(boolean i)
    int invert = Param[0]->Val->Integer;
    tft.invertDisplay((bool)invert);
  }
  void TFT_drawEllipse(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color),
    short x0 = Param[0]->Val->ShortInteger;
    short y0 = Param[1]->Val->ShortInteger;
    short rx = Param[2]->Val->ShortInteger;
    short ry = Param[3]->Val->ShortInteger;
    short color = Param[4]->Val->ShortInteger;
    tft.drawEllipse(x0, y0, rx, ry, color);
  }
  void TFT_fillEllipse(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color),
    short x0 = Param[0]->Val->ShortInteger;
    short y0 = Param[1]->Val->ShortInteger;
    short rx = Param[2]->Val->ShortInteger;
    short ry = Param[3]->Val->ShortInteger;
    short color = Param[4]->Val->ShortInteger;
    tft.fillEllipse(x0, y0, rx, ry, color);
  }
  void TFT_readRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint16_t *data);
    int x0 = Param[0]->Val->Integer;
    int y0 = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    uint16_t *data = (uint16_t *)Param[4]->Val->Pointer;
    tft.readRect(x0, y0, w, h, data);
  }
  void TFT_pushRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint16_t *data);
    int x0 = Param[0]->Val->Integer;
    int y0 = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    uint16_t *data = (uint16_t *)Param[4]->Val->Pointer;
    tft.pushRect(x0, y0, w, h, data);
  }

  void TFT_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *str = (char *)Param[0]->Val->Pointer;
    int x = Param[1]->Val->Integer;
    int y = Param[2]->Val->Integer;
    drawJpeg(str, x, y);
  }
  void TFT_drawRoundRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //  drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),

    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    int radius = Param[4]->Val->Integer;
    int color = Param[5]->Val->Integer;
    tft.drawRoundRect(x1, y1, w, h, radius, color);
  }
  void TFT_fillRoundRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //  drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int w = Param[2]->Val->Integer;
    int h = Param[3]->Val->Integer;
    int radius = Param[4]->Val->Integer;
    int color = Param[5]->Val->Integer;
    tft.fillRoundRect(x1, y1, w, h, radius, color);
  }
  void TFT_drawCircle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_drawCircle(int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int radius = Param[2]->Val->Integer;
    int color = Param[3]->Val->Integer;
    tft.drawCircle(x1, y1, radius, color);
  }
  void TFT_fillCircle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_fillCircle(int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int radius = Param[2]->Val->Integer;
    int color = Param[3]->Val->Integer;
    tft.fillCircle(x1, y1, radius, color);
  }
  void TFT_drawTriangle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_drawTriangle(int,int,int,int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int x3 = Param[4]->Val->Integer;
    int y3 = Param[5]->Val->Integer;
    int color = Param[6]->Val->Integer;
    tft.drawTriangle(x1, y1, x2, y2, x3, y3, color);
  }
  void TFT_fillTriangle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_fillTriangle(int,int,int,int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int x3 = Param[4]->Val->Integer;
    int y3 = Param[5]->Val->Integer;
    int color = Param[6]->Val->Integer;
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
  }
  void TFT_fillScreen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_fillScreen(int);" },
    int color = Param[0]->Val->Integer;
    tft.fillScreen(color);
    tft.setCursor(0, 240 - tft.textsize * 8);
  }
  void TFT_setTextColor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_setTextColor(int,int);" },
    int cf = Param[0]->Val->Integer;
    int cb = Param[1]->Val->Integer;
    tft.setTextColor(cf, cb);
  }
  void TFT_setCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // void TFT_setCursor(int,int);"
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    tft.setCursor(x1, y1);
  }
  void TFT_print(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_print(char *);" },
    char *str = (char *)Param[0]->Val->Pointer;
    tft.print(str);
  }
  void TFT_setTextSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_setTextSize(int);" },
    int size = Param[0]->Val->Integer;
    int oldSlines = slines;
    tft.setTextSize(size);
    slines = size * 8;
    int sa = slines - oldSlines;
    if (sa > 0)
    {
      oldSlines = slines;
      slines = sa;
      iScroll();
      slines = oldSlines;
    }
    tft.setCursor(0, 240 - slines);
  }
  void TFT_drawLine(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //     "void TFT_drawLine(int,int,int,int,int);"
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    tft.drawLine(x1, y1, x2, y2, color);
  }
  void TFT_fillRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_fillRect(int,int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    tft.fillRect(x1, y1, x2, y2, color);
  }
  void TFT_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    //"void TFT_drawRect(int,int,int,int,int):" },
    int x1 = Param[0]->Val->Integer;
    int y1 = Param[1]->Val->Integer;
    int x2 = Param[2]->Val->Integer;
    int y2 = Param[3]->Val->Integer;
    int color = Param[4]->Val->Integer;
    tft.drawRect(x1, y1, x2, y2, color);
  }

  void fontShow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    FontShow();
  }

#endif // TFT

  // library additions for Arduino compatibility
  void printLines(char *src);
  void listSrc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    if (Parser->SourceText != NULL)
      printLines((char *)Parser->SourceText);
  }
  void VariableCleanup();
  void idrop(char *Name)
  {
    /* delete this variable or function */
    TableDelete(&GlobalTable, Name);
  }
  void drop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *Name;
    Name = (char *)Param[0]->Val->Pointer;
    /* delete this variable or function */
    TableDelete(&GlobalTable, Name);
  }
  extern char toConsole;
  void ls(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char hs = literal;
    literal = 1;
    char th = toConsole;
#ifdef ESP32
    File root = SPIFFS.open((char *)"/");
    File file = root.openNextFile();
    toConsole = 0;
    sendContent("<tr><td colspan=\"2\" style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:10px; FONT-FAMILY:Courier\">");
    literal = 1;
    toConsole = th;
    sendContent("   File name               Size\n");
    toConsole = 0;
    sendContent("</td></tr>\n");
    toConsole = th;
    char bf[32];
    String space = "                             ";
    while (file)
    {
      String fileName = file.name();
      literal = 1;
      toConsole = 0;
      sendContent("<tr><td colapan=\"2\" style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:10px; FONT-FAMILY:Courier\" >");
      toConsole = th;
      literal = 0;
      sendContent((char *)fileName.c_str());
      int spaces = 25 - fileName.length(); // Tabulate nicely
      literal = 0;
      toConsole = 0;
      sendContent((char *)space.substring(0, spaces).c_str());
      toConsole = th;
#ifdef TFT
      if (th > 0)
        iconsoleOut((char *)space.substring(0, spaces).c_str());
#endif
      snprintf((char *)&bf, 31, "%6d bytes", file.size());
      sendContent((char *)&bf);
      toConsole = 0;
      literal = 1;
      sendContent("</td></tr>");
#ifdef TFT
      if (th != 0)
        iconsoleOut("\n");
#endif
      file = root.openNextFile();
      toConsole = th;
    }
#else
    fs::File root = SPIFFS.open((char *)"/", "r");
    // fs::File file = root.openNextFile();
#endif
    sendContent((char *)"\n");
    literal = hs;
    toConsole = th;
  }
  // void printLines(char *src);
  void printLn(char *src);
  void cat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char fname[34];
    char *FileName;
    int BytesRead, showNums;
    char th = toConsole;
    toConsole = 0;
    literal = 1;
    sendContent("<textarea style=\"FONT-SIZE:14px; COLOR:#000000; LINE-HEIGHT:14px; FONT-FAMILY:Courier\" rows=\"6\" cols=\"120\">");
    literal = 1;
    toConsole = th;
    sendContent("cat(\"");
    FileName = (char *)(Param[0]->Val->Pointer);
    for (int i = 0; i < BUFSIZE; buf[i++] = 0)
      ;
    strncpy((char *)&fname, FileName, 33);
    if (*FileName != '/')
      sprintf((char *)&fname, "/%s", FileName);
    sendContent(FileName);
    sendContent("\", ...)\n");
    showNums = Param[1]->Val->Integer;
#ifdef ESP32
    File fin = SPIFFS.open((char *)&fname, "r");
    if (!fin)
    {
#else
    fs::File fin = SPIFFS.open((char *)&fname, "r");
    if (!fin)
    {
#endif

      sendContent("file open failed for ");
      sendContent((char *)&fname);
      buf[0] = 0;
      return;
    }
    fin.read((uint8_t *)&buf, BUFSIZE - 1);
    fin.close();
    literal = 1;
    if (showNums)
      printLines((char *)&buf);
    else
      printLn((char *)&buf);
    toConsole = 0;
    sendContent("</textarea>");
    toConsole = th;
  }
  void mycat(char *FileName)
  {
    char fname[34];
    int BytesRead;
    for (int i = 0; i < BUFSIZE; buf[i++] = 0)
      ;
    strncpy((char *)&fname, FileName, 33);
    if (*FileName != '/')
      sprintf((char *)&fname, "/%s", FileName);
#ifdef ESP32
    File fin = SPIFFS.open((char *)&fname, "r");
#else
    fs::File fin = SPIFFS.open((char *)&fname, "r");
#endif
    if (!fin)
    {
      sendContent("file open failed for ");
      sendContent((char *)&fname);
      buf[0] = 0;
      return;
    }
    fin.read((uint8_t *)&buf, BUFSIZE - 1);
    fin.close();
    sendContent((char *)&buf);
  }

  void Ctest(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char bf[21];
    snprintf((char *)&bf, 20, "test(%d)\n", Param[0]->Val->Integer);
    sendContent((char *)&bf);
    // Ssend((char *)&bf);       //lyx
    for (int i = 3; i < 11; i++)
    {
      snprintf((char *)&bf, 20, "test line %d\n", i);
      sendContent((char *)&bf);
      // Ssend((char *)&bf);
    }
    ReturnValue->Val->Integer = 1234;
  }

  void printLines(char *src)
  {
    // Ssend("Entered real printLines\n");
    if (listIncludes == 0)
      return;
    char chold = toConsole;
    if (toConsole < 2)
      toConsole = 0;
    char Bf[351];
    int i = 1;
    int doit = 1;
    char *ps;
    char *cp = src;
    while (doit)
    {
      ps = strchr(cp, 13);
      if (ps != 0)
        *ps = ' ';
      ps = strchr(cp, 10);
      if (ps != 0)
      {
        *ps = 0;
        snprintf((char *)&Bf, 350, "%4d %s\n", i++, (char *)cp);
        toConsole = chold;
        sendContent((char *)&Bf);
        *ps++ = 10;
        cp = ps;
        if (*cp == 0)
        {
          doit = 0;
          // Ssend("Done printLines\n");
          toConsole = 0;
          if (didPlines == 0)
          {
            literal = 1;
            sendContent("</textarea><br/>Global Level Outputs<br/><table class=\"text2\" frame=\"vsides\"  rules=\"cols\" cellpadding=\"2\">");
          }
          toConsole = chold;
          literal = 0;
          didPlines = 1;
          return;
        }
      }
      else
      {
        String wout = "";
        toConsole = chold;
        snprintf((char *)&Bf, 350, "%4d %s\n", i++, cp);
        sendContent((char *)&Bf);
        doit = 0;
      }
    }
    // Ssend("Done printLines\n");
    toConsole = 0;
    if (didPlines == 0)
    {
      literal = 1;
      sendContent("</textarea><br/>Global Level Outputs<br/><table class=\"text2\" frame=\"vsides\"  rules=\"cols\" cellpadding=\"2\">");
    }
    didPlines = 1;
    literal = 0;
    toConsole = chold;
  }


  void printLn(char *src)
  {
    char Bf[351];
    // Serial.println(F("In clibrary printLn"));
    int i = 1;
    int doit = 1;
    char *ps;
    char *cp = src;
    while (doit)
    {
      ps = strchr(cp, 10);
      if (ps != 0)
      {
        *ps = 0;
        snprintf((char *)&Bf, 350, "%s\n", cp);
        //  Serial.print((char *)&Bf);
        sendContent((char *)Bf);
        *ps++ = 10;
        cp = ps;
        if (*cp == 0)
          doit = 0;
      }
      else
      {
        sendContent(src);
        doit = 0;
      }
    }
  }
  extern char *Prompt;
  extern int BreakpointCount;
  int DebugClearBreakpoint(struct ParseState *Parser);
  void DebugSetBreakpoint(struct ParseState *Parser);

  void setBkp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    printf("Entered setBkp\n");
    char *filename;
    int lineno;
    struct ParseState tempParse;
    // printf("FileName = %s\n",Parser->FileName);
    lineno = Param[0]->Val->Integer;
    // printf("%s %d\n",filename,lineno);
    tempParse.FileName = Parser->FileName;
    tempParse.Line = lineno;
    tempParse.CharacterPos = 0;
    char lbuf[20];
    sendContent("Breakpoint set at ");
    sprintf((char *)&lbuf, "%d", tempParse.Line);
    sendContent((char *)&lbuf);
    sendContent(" in ");
    sprintf((char *)&lbuf, "%s\n", tempParse.FileName);
    sendContent((char *)&lbuf);
    DebugSetBreakpoint(&tempParse);
  }
  void clearBkp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    // printf("Entered clearBkp\n");
    int lineno;
    struct ParseState tempParse;
    // printf("FileName = %s\n",Parser->FileName);
    lineno = Param[0]->Val->Integer;
    // printf("%s %d\n",filename,lineno);
    tempParse.FileName = Parser->FileName;
    tempParse.Line = lineno;
    tempParse.CharacterPos = 0;
    char lbuf[20];
    sendContent("Breakpoint cleared at ");
    sprintf((char *)&lbuf, "d", tempParse.Line);
    sendContent((char *)&lbuf);
    sendContent(" in ");
    sprintf((char *)&lbuf, "s\n", tempParse.FileName);
    sendContent((char *)&lbuf);
    DebugClearBreakpoint(&tempParse);
  }
  void SDB(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int dmode;
    dmode = Param[0]->Val->Integer;
    if (dmode == 1)
      Prompt = "debug> ";
    else
      Prompt = "picoc> ";
    sendContent(Prompt);
    Parser->DebugMode = dmode;
    char lbuf[20];
    sprintf((char *)&lbuf, "%d", BreakpointCount);
    sendContent((char *)&lbuf);
    sendContent(" Breakpoints are set\n");
    //   if (dmode == 1 && Parser->SourceText!=NULL) LinePrint((char *)Parser->SourceText,Parser->Line,Parser->CharacterPos);
    return;
  }

  void defs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    mycat("defs.txt");
    sendContent("\n");
  }
  void help(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    mycat("defs.txt");
    sendContent("\n");
  }

  void isprime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char lbuf[28];
    long n = Param[0]->Val->Integer;
    if (n % 2 == 0)
      n++;
    long lim = Param[1]->Val->Integer;
    long interval = Param[2]->Val->Integer;
    long k, p, mcount = 0, phold = 0;
    long pc = 0;
    int t1;
    long istrt = n;
    long lastp = n;
    sendContent("\nFinding primes between ");
    PrintWithCommas(n, 0);
    sendContent(" & ");
    PrintWithCommas(lim, 0);
    sendContent("\n\n");
    t1 = millis();
    while (n < (lim))
    {
      k = 3;
      p = 1;
      n = n + 2;
      while ((k * k <= n) && p)
      {
        p = (n % k);
        mcount++;
        k = k + 2;
      }
      if (p)
      {
        pc = pc + 1;
        phold = n;
        if ((pc % interval) == 0)
        {
          sendContent("prime # ");
          PrintWithCommas(pc, 6);
          sendContent(" is ");
          PrintWithCommas(n, 0);
          char lbuf[20];
          sprintf((char *)&lbuf, "%5.2f %% are prime\n", interval * 100.0 / (n - lastp));
          sendContent((char *)&lbuf);
          lastp = n;
        }
      }
    }
    float secs = (millis() - t1) / 1000.0;
    sendContent("Last prime was ");
    PrintWithCommas(phold, 0);
    sendContent("\n");
    sendContent("\n\n");
    PrintWithCommas(pc, 0);
    sendContent(" primes found\n");
    PrintWithCommas(mcount, 0);
    sendContent(" prime check loops performed in ");
    sprintf((char *)&lbuf, "%0.2f", secs);
    sendContent((char *)&lbuf);
    sendContent(" sec\n");
    sendContent("That's ");
    PrintWithCommas(mcount / secs, 0);
    sendContent(" per second\n");
    ReturnValue->Val->Integer = pc;
  }
#ifdef ESP32
  int getChannel(int pin)
  {
    int i;
    for (i = 0; i < 16; i++)
      if (pwmAssigns[i] == pin)
        break;
    if (i < 16)
      return i;
    else
      return -1;
  }
  int getAvailableChannel()
  {
    int i;
    for (i = 0; i < 16; i++)
      if (pwmAssigns[i] == -1)
        break;
    if (i < 16)
      return i;
    else
      return -1;
  }
  int checkPin(int pin)
  {
    if ((pin == 2) ||                   // 1
        (pin == 4) ||                   // 1
        (pin == 5) ||                   // 1
        ((pin >= 12) && (pin <= 19)) || // 8
        ((pin >= 21) && (pin <= 23)) || // 3
        ((pin >= 25) && (pin <= 27)) || // 3
        (pin == 32) || (pin == 33))     // 2
      return 1;
    else
      Serial.printf("pin %d is not available for PWM\n", pin);
  }
  char servoReport = 1;
  void pwmServo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin = Param[0]->Val->Integer;
    if (!checkPin(pin))
      return;
    float duration = Param[1]->Val->FP;
    int channel = getChannel(pin);
    //  Serial.printf("pwmServo getchannel(%d) returned %d\n",pin,channel);
    if (channel == -1)
    {
      channel = getAvailableChannel();
      //   Serial.printf("Available channel is %d\n",channel);
      if (channel != -1)
      {
        pwmAssigns[channel] = pin;
        PWMs[channel].attachPin(pin, 100.0, 12);
        Serial.flush();
        delay(100);
        //      Serial.printf("pwmServo setting pwmRanges\n");
        pwmRanges[channel].min = 1.5;
        pwmRanges[channel].max = 2.5;
      }
    }
    if (channel != -1)
    {
      // now have to user PWMs[channel] to reference the PWM pin
      // float periodMs=(1.0 / (pwmFreq*1.0)*1000);
      float pwmPeriod = 1000.0 / PWMs[channel].readFreq();
      // Serial.printf("Channel period is %f msec\n",pwmPeriod);
      int pwmValue = duration / pwmPeriod * 4096;
      PWMs[channel].write(pwmValue);
      char bf[60];
      snprintf((char *)&bf, 59, "Setting pin %d to value %d on time of %0.4f msec\n", pin, pwmValue, pwmValue / 4096.0 / pwmPeriod * 100);
      if (servoReport)
        sendContent((char *)&bf);
    }
    else
    {
      char bf[60];
      snprintf((char *)&bf, 59, "Pin %d cannot be used all channels are in use!\n", pin);
      sendContent((char *)&bf);
    }
  }
  void servoAngle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin = Param[0]->Val->Integer;
    if (!checkPin(pin))
      return;
    float angle = Param[1]->Val->FP;
    float angleFraction = angle / 180.0;
    int channel = getChannel(pin);
    //  Serial.printf("servoAngle getchannel(%d) returned %d\n",pin,channel);
    if (channel == -1)
    {
      channel = getAvailableChannel();
      //   Serial.printf("Available channel is %d\n",channel);
      if (channel != -1)
      {
        pwmAssigns[channel] = pin;
        PWMs[channel].attachPin(pin, 100.0, 12);
        Serial.flush();
        delay(100);
        //      Serial.printf("servoAngle setting pwmRanges\n");
        pwmRanges[channel].min = 1.5;
        pwmRanges[channel].max = 2.5;
      }
    }
    if (channel != -1)
    {
      // now have to user PWMs[channel] to reference the PWM pin
      float duration = angle / 180.0 * (pwmRanges[channel].max - pwmRanges[channel].min) + pwmRanges[channel].min;
      //    Serial.printf("angleMin=%f and angleMax=%f and calculated duration is %f\n",pwmRanges[channel].min,pwmRanges[channel].max,duration);
      float pwmPeriod = 1000.0 / PWMs[channel].readFreq();
      // Serial.printf("Channel period is %f msec\n",pwmPeriod);
      int pwmValue = duration / pwmPeriod * 4096;
      PWMs[channel].write(pwmValue);
      char bf[60];
      snprintf((char *)&bf, 59, "Setting pin %d to angle %0.3f on time of %0.3f msec\n", pin, angle, pwmValue / 4096.0 / pwmPeriod * 100);
      if (servoReport)
        sendContent((char *)&bf);
    }
    else
    {
      char bf[60];
      snprintf((char *)&bf, 59, "Pin %d cannot be used all channels are in use!\n", pin);
      sendContent((char *)&bf);
    }
  }
  void setServoRange(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin = Param[0]->Val->Integer;
    if (!checkPin(pin))
      return;
    float angleMin = Param[1]->Val->FP;
    float angleMax = Param[2]->Val->FP;
    int channel = getChannel(pin);
    if (channel == -1)
    {
      channel = getAvailableChannel();
      //   Serial.printf("Available channel is %d\n",channel);
      if (channel != -1)
      {
        pwmAssigns[channel] = pin;
        PWMs[channel].attachPin(pin, 100.0, 12);
        Serial.flush();
        delay(100);
      }
    }
    if (channel != -1)
    {
      pwmRanges[channel].min = angleMin;
      pwmRanges[channel].max = angleMax;
      char bf[100];
      snprintf((char *)&bf, 99, "Setting pin %d to min angle time of %0.3f ms and max angle time of %0.3f ms\n", pin, angleMin, angleMax);
      if (servoReport)
        sendContent((char *)&bf);
    }
    else
    {
      char bf[60];
      snprintf((char *)&bf, 59, "Pin %d cannot be used all channels are in use!\n", pin);
      sendContent((char *)&bf);
    }
  }
  void AnalogWrite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin = Param[0]->Val->Integer;
    if (!checkPin(pin))
      return;
    int val = Param[1]->Val->Integer;
    int channel = getChannel(pin);
    if (channel == -1)
    {
      channel = getAvailableChannel();
      Serial.printf("Available channel is %d\n", channel);
      if (channel != -1)
      {
        pwmAssigns[channel] = pin;
        PWMs[channel].attachPin(pin, 1000.0, 12);
      }
    }
    if (channel != -1)
    {

      PWMs[channel].write(val);
      char bf[100];
      snprintf((char *)&bf, 99, "Setting pin %d to raw value of %d\n", pin, val);
      if (servoReport)
        sendContent((char *)&bf);
    }
    else
    {
      char bf[60];
      snprintf((char *)&bf, 59, "Pin %d cannot be used all channels are in use!\n", pin);
      sendContent((char *)&bf);
    }
  }
  void setServoReport(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int report = Param[0]->Val->Integer;
    servoReport = (char)report;
  }
#endif
#ifndef ESP32
  void heap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    sendContent("\nfree heap size = ");
    char lbuf[20];
    sprintf((char *)&lbuf, "%d\n", ());
    sendContent((char *)&lbuf);
  }
#endif
  void sysTime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = millis() / 8;
  }
  int didPwmInit = 0;
  // pwm_info_t pwm_info;
  uint8_t pins[16];
  uint8_t numPins = 0;

  void PinMode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin;
    char *val;
    pin = Param[0]->Val->Integer;
    char b[60];
    if (pin > 39)
    {
      sendContent("Invalid pin ");
      sprintf((char *)&b, "%d", pin);
      sendContent((char *)&b);
      sendContent(" specified!\n");
      return;
    }
    val = (char *)Param[1]->Val->Pointer;
    if (strcmp((char *)val, "OUTPUT") == 0)
    {
      pinMode(pin, OUTPUT);
    }
    else if (strcmp((char *)val, "INPUT") == 0)
    {
      pinMode(pin, INPUT);
    }
    else if (strcmp((char *)val, "INPUT_PULLUP") == 0)
    {
      pinMode(pin, INPUT_PULLUP);
    }
    else
    {
      sprintf((char *)&b, "Mode of %s not Recognized\n", (char *)val);
      sendContent((char *)&b);
    }
  }
  void DigitalWrite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin, val;
    pin = Param[0]->Val->Integer;
    val = Param[1]->Val->Integer;
    char b[20];
    if (pin > 39)
    {
      PrintAndWebOut("Invalid pin ");
      sprintf((char *)&b, "%d", pin);
      PrintAndWebOut((char *)&b);
      PrintAndWebOut(" specified!\n");
      return;
    }
    digitalWrite(pin, val);
  }
  void Delay(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int dly;
    dly = Param[0]->Val->Integer;
    delay(dly);
  }

  void DigitalRead(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int pin;
    pin = Param[0]->Val->Integer;
    char b[20];
    if (pin > 39)
    {
      PrintAndWebOut("Invalid pin ");
      sprintf((char *)&b, "%d", pin);
      PrintAndWebOut((char *)&b);
      PrintAndWebOut(" specified!\n");
      return;
    }
    if (digitalRead(pin))
      ReturnValue->Val->Integer = 1;
    else
      ReturnValue->Val->Integer = 0;
  }

  void myReadFile(char *FileName)
  {
    int BytesRead;
    char fname[34];
    strncpy((char *)&fname, FileName, 33);
    for (int i = 0; i < BUFSIZE; buf[i++] = 0)
      ;
    if (*FileName != '/')
      sprintf((char *)&fname, "/%s", FileName);
    // send("Opening file ");sendln(((char *)&fname);
    fs::File fin = SPIFFS.open((char *)&fname, "r");
    if (!fin)
    {
      PrintAndWebOut("can't read file ");
      sendln((char *)&fname);
      return;
    }
    fin.read((uint8_t *)&buf, BUFSIZE - 1);
    fin.close();
  }

  char buff[8];
  char *item = 0;
#ifndef ESP32
  void speed(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    int spd = Param[0]->Val->Integer;
    system_update_cpu_freq((uint8)spd);
  }
#endif
  void Restart(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ESP.restart();
  }

  void AnalogRead(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    ReturnValue->Val->Integer = analogRead(0);
  }
  void Sprint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
  {
    char *src = (char *)Param[0]->Val->Pointer;
    Serial.print(src);
  }

  //,https://github.com/Ameba8195/Arduino/raw/master/release/package_realtek.com_ameba_index.json,https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json,http://digistump.com/package_digistump_index.json,https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  /* list of all library functions and their prototypes */
  // http://download.labs.mediatek.com/package_mtk_linkit_7697_index.json,http://download.labs.mediatek.com/package_mtk_linkit_smart_7688_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://github.com/Ameba8195/Arduino/raw/master/release/package_realtek.com_ameba_index.json,https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json,http://digistump.com/package_digistump_index.json,https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  /* list of all library functions and their prototypes */
  struct LibraryFunction CLibrary[] =
      {
          {Restart, "void restart();"},           // ESP.restart();
          {Watch, "void Watch(char *);"},         // add Watch (if not already added) for variable named char string
          {dropWatch, "void dropWatch(char *);"}, // drop Watch for char string name if present
          {stopDebug, "void stopDebug();"},       // stop Debug single step display
          {Debug, "void Debug();"},               // start Debug single step display
          {Sprint, "void sprint(char *);"},       // Send char string to Serial Monitor
#ifdef ESP32
          {AnalogWrite, "void analogWrite(int,int);"}, // pin,value set pin analog out to value range 0-4095
#else

#endif
          {AnalogRead, "int analogRead();"}, // returns read of A0
          {Ctest, "int test(int);"},         // simply retuns 1234 and does some Console Output
#ifdef SSD1306OLED
          {oconsolePrintln, "void oconsolePrintln(char *);"}, // draw char string at current cursor x,y
          {oconsoleInit, "void oconsoleInit();"},             // must be called to start OLED display
          {oinvertDisplay, "void oinvertDisplay(int);"},      // if arg=1 set  display to reverse video else normal video
          {odrawLine, "void odrawLine(int,int,int,int);"},    // x1,y1,x2,y2
          {ofillRect, "void ofillRect(int,int,int,int);"},    // x,y,width,height
          {odrawRect, "void odrawRect(int,int,int,int);"},    // x,y,width,height
          {oclear, "void oclear(void);"},
          {odrawString, "void odrawString(int,int,char *);"}, // x,y in pixels,char string
          {odisplay, "void odisplay(void);"},                 // update display
          {osetPixel, "void osetPixel(int,int);"},            // x,y
          {osetCursor, "void osetCursor(int,int);"},          // x,y
          {oprint, "void oprint(char *);"},
          {oprintln, "void oprintln(char *);"},
          {osetFontSize, "void osetFontSize(int);"}, //  allowed values 10=ArialMT_Plain_10 16=ArialMT_Plain_16 24=ArialMT_Plain_24
          {osetColor, "void osetColor(int);"},       // 0=black 1=white 2=invert
#endif
#ifdef TFT
          {setConsoleOn, "void setConsoleOn(int);"},                                          // 0 turns console output off for prntf function, 1 turns counsole output on
          {HFsetCursor, "void HFsetCursor(int,int);"},                                        // x,y
          {HFsetStrokeDelay, "void HFsetStrokeDelay(int);"},                                  // set delay between strokes normally 0 non zero make for character drawing animation on screen
          {HFdrawStringRotated, "void HFdrawStringRotated(int,int,float,int,float,char *);"}, // x,y,radius,size,color,angle,char string
          {HFdrawString, "void HFdrawString(int,int,float,int,char *);"},                     // x,y,size,color,char string
          {HFdrawStringOpaque, "void HFdrawStringOpaque(int,int,float,int,int,char *);"},     // x,y,size,foreColor,backColor,char string
          {HFdrawCenteredString, "void HFdrawCenteredString(int,float,int,char *);"},         // y,size,color,char string
          {HFgetStringSize, "int HFgetStringSize(char *,float);"},                            // char string,size -- returns length
          {HFdraw, "void HFdraw(char,float,int);"},                                           // char,size,color
          {HFdrawRotated, "void HFdrawRotated(int,int,char,float,int,float);"},
          {HFsetFont, "void HFsetFont(char *);"},                                    // font name -- allowed values are "serif" "sans" "sansbold" "greek" "cursive"
          {fontShow, "void fontShow(void);"},                                        // runs a Hershey font demo
          {scroll, "void scroll();"},                                                // scrolls scrollPixels vertically upward
          {setScrollPixels, "void setScrollPixels(int);"},                           // scrollPixels -- sets scroll value independent of setTextSize
          {consoleAlert, "void consoleAlert(char *);"},                              // send message char string in black on red to the terminal
          {consoleOut, "void consoleOut(char *);"},                                  // char string to display on console \n are recognized and screen will scroll as necessary to show char string
          {TFT_draw, "void TFT_draw(char *,int,int);"},                              // filename,x,y
          {TFT_print, "void TFT_print(char *);"},                                    // char string to print
          {TFT_setCursor, "void TFT_setCursor(int,int);"},                           // x,y y increases from 0 at top of display
          {TFT_setTextColor, "void TFT_setTextColor(int,int);"},                     // foreColor,backColor
          {TFT_setTextSize, "void TFT_setTextSize(int);"},                           // size
          {TFT_fillScreen, "void TFT_fillScreen(int);"},                             // color
          {TFT_drawLine, "void TFT_drawLine(int,int,int,int,int);"},                 // x1,y1,x2,y2,color
          {TFT_drawRect, "void TFT_drawRect(int,int,int,int,int);"},                 // x,y,width,height,color
          {TFT_fillRect, "void TFT_fillRect(int,int,int,int,int);"},                 // x,y,width,height,color
          {TFT_fillCircle, "void TFT_fillCircle(int,int,int,int);"},                 // xc,yc,radius,color
          {TFT_drawTriangle, "void TFT_drawTriangle(int,int,int,int,int,int,int);"}, // x1,y1,x2,y2,x3,y3,color
          {TFT_fillTriangle, "void TFT_fillTriangle(int,int,int,int,int,int,int);"}, // x1,y1,x2,y2,x3,y3,color
          {TFT_drawCircle, "void TFT_drawCircle(int,int,int,int);"},                 // xc,yc,radius,color
          {TFT_drawRoundRect, "void TFT_drawRoundRect(int,int,int,int,int,int);"},   // x,y,width,height,radius,color
          {TFT_fillRoundRect, "void TFT_fillRoundRect(int,int,int,int,int,int);"},   // x,y,width,height,radius,color
          {TFT_invertDisplay, "void TFT_invertDisplay(int);",},                      // pass 0 for nurmal 1 for inverse
          {TFT_drawEllipse, "void TFT_drawEllipse(short,short,short,short,short);"}, // xc,yc,radiusx,radiusy,color
          {TFT_fillEllipse, "void TFT_fillEllipse(short,short,short,short,short);"}, // xc,yc,radiusx,radiusy,color
          {TFT_readRect, "void TFT_readRect(int,int,int,int,short *);"},             // startx,starty,width,height
          {TFT_pushRect, "void TFT_pushRect(int,int,int,int,short *);"},             // startx,starty,width,height
          {screenCapture, "void screenCapture();"},
          {TFT_Gauge, "int TFT_Gauge(float,float,float,float,float,float,float,int,float,int,char *,char *);"},
          //(float xc,float yc,float sang,float eang,float radius,float sval,float eval,int divisions,float increments,int color,char * fmt,char * valueFmt);
          {TFT_Gauge_draw, "void TFT_Gauge_draw(int);"},                                           // gauge#
          {TFT_Gauge_setPosition, "void TFT_Gauge_setPosition(int,float);"},                       // gauge#,value
          {TFT_Gauge_drawDanger, "void TFT_Gauge_drawDanger(int,float,float,int);"},               // gauge#,startValue,endValue, color
          {TFT_Gauge_drawDangerByValue, "void TFT_Gauge_drawDangerByValue(int,float,float,int);"}, // gsuge#,startValue,endValue, color
          {TFT_Gauge_dropGauges, "void TFT_Gauge_dropGauges();"},
          {TFT_VbarGraph, "int TFT_VbarGraph(float,float,int,int,float,float,int,float,int,char *,char *);"},
          // float x,float y,int width,int height,float sval,float eval,int divisions,float increments,int color,char * fmt,char * valueFmt
          {TFT_VbarGraph_draw, "void TFT_VbarGraph_draw(int);"},                     // gauge#
          {TFT_VbarGraph_setPosition, "void TFT_VbarGraph_setPosition(int,float);"}, // gauge#,value
          {TFT_VbarGraph_dropGauges, "void TFT_VbarGraph_dropGauges();"},            // gauge#
          {TFT_HbarGraph, "int TFT_HbarGraph(float,float,int,int,float,float,int,float,int,char *,char *);"},
          // float x,float y,int width,int height,float sval,float eval,int divisions,float increments,int color,char * fmt,char * valueFmt
          {TFT_HbarGraph_draw, "void TFT_HbarGraph_draw(int);"},                     // gauge#
          {TFT_HbarGraph_setPosition, "void TFT_HbarGraph_setPosition(int,float);"}, // gauge#,value
          {TFT_HbarGraph_dropGauges, "void TFT_HbarGraph_dropGauges();"},            // frees all gauge storage
#endif
#ifndef ESP32
          {speed, "void cpuClock(int);"},
#endif
          {sysTime, "int sysTime();"}, // calls milli
//   { sendToFile,  "void sendToFile(char *);"               },
#ifdef ESP32
          {servoAngle, "void servoAngle(int,float);"},             // pin,angle
          {setServoRange, "void setServoRange(int,float,float);"}, // pin, min_millisec, mac_millisec
          {pwmServo, "void pwmServo(int,float);"},                 // pin,dutyCycle
          {setServoReport, "void setServoReport(int);"},           // 1=on 0=off
#endif
          //    { get,          "void get(char *);"                     },
          {setBkp, "void setBkp(char *,int);"},     // filename,line
          {clearBkp, "void clearBkp(char *,int);"}, // fileName,line
          {ls, "void ls();"},
          {cat, "void cat(char *,int);"}, // fileName,with_linenumbers
          {SDB, "void SDB(int);"},        // o to disable, 1 to enable
          {drop, "void drop(char *);"},   // name
          {listSrc, "void listSrc();"},
          {defs, "void defs();"},
          {help, "void help();"},
          {isprime, "int isprime(int,int,int);"},        // start,end,reportInterval
          {Delay, "void delay(int);"},                   // Arduino equiv delay(milliseconds);
          {DigitalWrite, "void digitalWrite(int,int);"}, // Arduino equiv digitalWrite(pin,value);
          {DigitalRead, "int digitalRead(int);"},        // Arduino equiv int digitalRead(pin);
          {PinMode, "void pinMode(int,char *);"},        // pin,"OUTPUT" or "INPUT" or "INPUT_PULLUP"
#ifndef ESP32
          {heap, "void heap();"},
#endif

#ifdef BME280
          {BME_init, "void BME_init();"},
          {BME_readTemp, "float BME_readTemp();"},
          {BME_readPressure, "float BME_readPressure();"},
          {BME_readRH, "float BME_readRH();"},
#endif // BME280

#ifdef NEO_PIXEL
          {NEO_begin_init, "void NEO_init(int,int);"},                                 // count,pin
          {NEO_setup, "void NEO_setup(int);"},                                         // brightness
          {NEO_setPixelColorRGB, "void NEO_setPixelColorRGB(int,int,int,int);"},       // n,r,g,b
          {NEO_setPixelColorRGBW, "void NEO_setPixelColorRGBW(int,int,int,int,int);"}, // n,r,g,b,w
          {NEO_setPixelColor32, "void NEO_setPixelColor32(int,int);"},                 // n,c
          {NEO_fill, "void NEO_fill(int,int,int);"},                                   // c,first,count
          {NEO_setBrightness, "void NEO_setBrightness(int);"},                         // brightness
          {NEO_colorWipe, "void NEO_colorWipe(int,int);"},
          {NEO_theaterChase, "void NEO_theaterChase(int,int);"},
          {NEO_rainbow, "void NEO_rainbow(int);"},
          {NEO_theaterChaseRainbow, "void NEO_theaterChaseRainbow(int);"},
#endif

#ifdef ePAPER
          {ePaper_init, "void ePaper_init();"},
          {ePaper_setCursor, "void ePaper_setCursor(int,int);"},
          {ePaper_setTextColor, "void ePaper_setTextColor(int);"},
          {ePaper_println, "void ePaper_println(char *);"},
          {ePaper_powerDown, "void ePaper_powerDown();"},
          {ePaper_update, "void ePaper_update();"},
          {ePaper_drawRect, "void ePaper_drawRect(int,int,int,int,int);"},
          {ePaper_fillRect, "void ePaper_fillRect(int,int,int,int,int);"},
          {ePaper_drawLine, "void ePaper_drawLine(int,int,int,int,int);"},
#endif
          {doLoop, "void doLoop();"}, // calls the ESP32Program sketch's loop() function
          {LibPrint, "void print(char *, ...);"},
          {LibPrintf, "void printf(char *, ...);"},
          {LibSPrintf, "char *sprintf(char *, char *, ...);"},
          {LibGets, "char *gets(char *);"},
          {LibGetc, "int getchar();"},
          {LibExit, "void exit(int);"},
#ifdef PICOC_LIBRARY

#ifndef NO_FP
          {StdlibAtof, "float atof(char *);"},
#endif // NO_FP
          {StdlibAtoi, "int atoi(char *);"},
          {StdlibAtol, "int atol(char *);"},
#ifndef NO_FP
          {StdlibStrtod, "float strtod(char *,char **);"},
#endif // NO_FP
          {StdlibStrtol, "int strtol(char *,char **,int);"},
          {StdlibStrtoul, "int strtoul(char *,char **,int);"},
          {StdlibRand, "int rand();"},
          {StdlibSrand, "void srand(int);"},
          {StdlibAbs, "int abs(int);"},
          {StdlibLabs, "int labs(int);"},
          {LibSin, "float sin(float);"},
          {LibCos, "float cos(float);"},
          {LibTan, "float tan(float);"},
          {LibAsin, "float asin(float);"},
          {LibAcos, "float acos(float);"},
          {LibAtan, "float atan(float);"},
          {LibSinh, "float sinh(float);"},
          {LibCosh, "float cosh(float);"},
          {LibTanh, "float tanh(float);"},
          {LibExp, "float exp(float);"},
          {LibFabs, "float fabs(float);"},
          {LibLog, "float log(float);"},
          {LibLog10, "float log10(float);"},
          {LibPow, "float pow(float,float);"},
          {LibSqrt, "float sqrt(float);"},
          {LibRound, "float round(float);"},
          {LibCeil, "float ceil(float);"},
          {LibFloor, "float floor(float);"},
          {LibMalloc, "void *malloc(int);"},
#ifndef NO_CALLOC
          {LibCalloc, "void *calloc(int,int);"},
#endif // NOCALLOC
#ifndef NO_REALLOC
          {LibRealloc, "void *realloc(void *,int);"},
#endif // NO_REALLOC
          {LibFree, "void free(void *);"},
#ifndef NO_STRING_FUNCTIONS
          {Libstrcpy, "void strcpy(char *,char *);"},
          {LibStrncpy, "void strncpy(char *,char *,int);"},
          {LibStrcmp, "int strcmp(char *,char *);"},
          {LibStrncmp, "int strncmp(char *,char *,int);"},
          {Libstrcat, "void strcat(char *,char *);"},
          {Libstrncat, "void strncat(char *,char *,int);"},
          {LibIndex, "char *index(char *,int);"},
          {LibRindex, "char *rindex(char *,int);"},
          {LibStrlen, "int strlen(char *);"},
          {LibMemset, "void memset(void *,int,int);"},
          {LibMemcpy, "void memcpy(void *,void *,int);"},
          {LibMemcmp, "int memcmp(void *,void *,int);"},
#endif // STRING_FUNCTIONS
#endif // PICOC_LIBRARY
          {NULL, NULL}};
}
#endif /* BUILTIN_MINI_STDLIB */