#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#define FS_NO_GLOBALS // needed for using SPIFFS
#include <FS.h> // library for SPI Fast File System SPIFFS
#include <Hershey.h>
#define SlideDelay 100
TFT_eSPI tft = TFT_eSPI();
Hershey HF("serif");
void tftSetup()
{
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(0);
  HF.setFont("serif");
}
void fontShow()
{
  unsigned char i=0;  
  float a;
  char * hr[12]={"12","1","2","3","4","5","6","7","8","9","10","11"};
  //HF.drawRotated(xc,yc,*(string+i),scale,color,a);
  tft.fillScreen(0);
  tft.drawCircle(160,120,75,0xf100);
  float an;
  for (a=90;(a-90)<360;a+=30.0) {an=a/360.0*2*3.14159;yield();tft.drawLine(160+sin(an)*70,120-cos(an)*70,160+sin(an)*77,120-cos(an)*77,0xf100);
  HF.drawStringRotated(160,120,90,0.75,0xffff,a,hr[i++]);yield();}
  tft.drawLine(160,120,110,70,0xf100);tft.fillCircle(160,120,3,0xf100);
  tft.drawLine(160,120,206,80,0xf100);
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0);
  HF.drawStringRotated(60,100,90,1.5,0xffff,135,"Hi");
  HF.drawStringRotated(260,220,90,1.5,0xffff,45,"Hi");
  HF.drawCenteredString(100,1.0,0xffff,"World");
  #ifdef CURSIVE
  HF.setFont("cursive");
  HF.drawCenteredString(200,1,0xffff,"Hello World");
  #endif  
  screenServer();
  delay (SlideDelay);
  #ifdef SERIF
  tft.fillScreen(0x001f);
  HF.setFont("serif");
  HF.drawStringOpaque(1,30,1,0x0,0xffff,"Black On White???");
  HF.drawStringOpaque(1,65,1,0xffff,0x0,"White On Black???");
  HF.drawStringOpaque(10,100,0.75,0x07E0,0xf100,"Christmas Anyone???");
  HF.setFont("cursive");
  int wd=HF.getStringSize("Hello World",1);
  HF.drawStringOpaque(160-wd/2,150,1,0xffff,0x000c,"Hello World");
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0xffff);
  HF.setCursor(10,20);
  HF.setFont("serif");
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,1.0,0);}
  HF.drawCenteredString(215,1,0xf100,"     Serif Font");
  screenServer();
  delay(SlideDelay);
  #endif
  #ifdef SANS
  tft.fillScreen(0xffff);
  HF.setFont("sans");
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,1.0,0);}
  HF.drawCenteredString(215,1,0xf100,"    Sans Font");
  screenServer();
  delay(SlideDelay);
  #endif
  #ifdef SANSB
  tft.fillScreen(0xffff);
  HF.setFont("sansbold");
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,1.0,0);}
  HF.drawCenteredString(215,1,0xf100,"    Sans Font Bold");
  screenServer();
  delay(SlideDelay);
  #endif
  #ifdef GREEK
  tft.fillScreen(0xffff);
  HF.setFont("greek");
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,1.0,0);}
  HF.setFont("serif");
  HF.drawCenteredString(215,1,0xf100,"Greek Font");
  screenServer();
  delay(SlideDelay);
  #endif
  #ifdef CURSIVE
  tft.fillScreen(0xffff);
  HF.setFont("cursive");
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,1.0,0);}
  HF.drawCenteredString(215,1,0xf100,"Cursive Font");
  screenServer();
  #endif
  HF.setFont("serif");
  tft.fillScreen(0xffff);
  HF.setCursor(10,20);
  for (i=32;i<'H';i++) {if (i%32==0) delay(1); HF.draw(i,1.5,0);}
  HF.drawCenteredString(215,1,0xf100,"Serif at Size=1.5");
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0xffff);
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,0.5,0);}
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,0.5,0);}
  HF.drawCenteredString(215,1,0xf100,"Serif at Size=0.5");
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0xffff);
  HF.setCursor(10,20);
  for (i=32;i<127;i++) {if (i%32==0) delay(1); HF.draw(i,0.75,0);}  
  HF.drawCenteredString(215,1,0xf100,"Serif at Size=0.75");
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0);
  HF.setCursor(10,100);
  HF.draw('A',0.5,0xf100);delay(1);
  HF.draw('B',1.0,0xffE0);delay(1);
  HF.draw('C',1.5,0x0fff);delay(1);
  HF.draw('D',2,0xf81f);delay(1);
  HF.draw('E',2.5,0xffff);delay(1);
  HF.draw('W',3,0x70E7);delay(1);
  HF.draw('X',3.5,0x51C5);delay(1);
  screenServer();
  delay(SlideDelay);
  tft.fillScreen(0);
  HF.setFont("cursive");
  HF.drawCenteredString(150,1.4,0xf100,"That's all Folks");
  screenServer();
  
}
void setup() {
  SPIFFS.begin();
  tftSetup();
  fontShow();
}

void loop() {
  // put your main code here, to run repeatedly:
  yield();
}
