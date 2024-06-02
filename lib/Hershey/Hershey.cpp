/* Hershey Fonts Render library

MIT license
written by Rick Lunglhofer for Micro Image Systems

*/

#include "Hershey.h"
#include <FS.h>
#include <math.h>
#ifndef ESP32
#include <TFT_eSPI.h> // Hardware-specific library
#else
#include <TFT_eSPI.h> // Hardware-specific library
#endif
extern TFT_eSPI tft;
void yield();
Hershey::Hershey(char * defaultFont)
{
	deltax=0;deltay=0;
	if (strlen(defaultFont)==0) return;
	setFont(defaultFont);
}

void Hershey::setStrokeDelay(int delay)
{
	strokeDelay=delay;
}
void Hershey::loadfile(char * fname)
{
	int i;	
	if (!SPIFFS.exists(fname)) {Serial.print(fname);Serial.println(" Does not exist");}
    fs::File fin=SPIFFS.open(fname,"r");
	int cc=0;
	for (i=0;i<96;i++)
	{
		// iterate through file lines and store offset into hFont[]
		hFont[i]=cc;
		byte done=0;char c;
		while (done==0) 
		{
			fin.readBytes(&c,1);
			cc++;
			//Serial.print(c);
			if (c==10) done=1;
		}
		yield();
		//Serial.print("\n char ");//Serial.printf("%d .%c. finished\n",i,i+' ');
	}
	fin.close();
    strcpy((char *)&fontFile,fname);
}
	//Serial.printf("Done processing %s\n",(char *)&fontFile);
    //Serial.println("leaving loadfile");

void Hershey::setFont(char * font)
{
//	Serial.println("Entering setFont");
	//Serial.println(font);
	int i;
	char fname[32];
    if (strstr(font,"serif")!=0) // Serif Font
	{
		if (strcmp((char *)&fontFile,"/ltr.hrsh")==0) return;
		if (!SPIFFS.exists("/ltr.hrsh")) { Serial.println("File missing");return;}
	  loadfile("/ltr.hrsh");
//	Serial.println("Leaving setFont with serif");
	  return;
	} 
    if (strstr(font,"sansbold")!=0) // Sans Font Bold
	{
		if (strcmp((char *)&fontFile,"/futuram.hrsh")==0) return;
		if (!SPIFFS.exists("/futuram.hrsh")) { Serial.println("File missing");return;}
	  loadfile("/futuram.hrsh");
	//Serial.println("Leaving setFont with sansbold");
	  return;
	}	 
    if (strstr(font,"sans")!=0) // Sans Font
    {
		if (strcmp((char *)&fontFile,"/futural.hrsh")==0) return;
		if (!SPIFFS.exists("/futural.hrsh")) { Serial.println("File missing");return;}
	  loadfile("/futural.hrsh");
	//Serial.println("Leaving setFont with sans");
		return;
	}	 
    if (strstr(font,"greek")!=0) // Greek Font
    {
		if (strcmp((char *)&fontFile,"/greek.hrsh")==0) return;
		if (!SPIFFS.exists("/greek.hrsh")) { Serial.println("File missing");return;}
	  loadfile("/greek.hrsh");
	//Serial.println("Leaving setFont with greek");
		return;
	}	 
    if (strstr(font,"cursive")!=0) // Cursive Font
    {
		if (strcmp((char *)&fontFile,"/cursive.hrsh")==0) return;
		if (!SPIFFS.exists("/cursive.hrsh")) { Serial.println("File missing");return;}
	  loadfile("/cursive.hrsh");
	//Serial.println("Leaving setFont with cursive");
		return;
	}
}

void Hershey::setCursor(int x,int y) {ox=x;oy=y;}

void Hershey::drawStringRotated(int x,int y,int r,float scale,int color,float a,char * string)
{
  int xc,yc;
  float sina,cosa,sinr,cosr;
  sina=sin(a/360.0*2*3.14159);cosa=cos(a/360.0*2*3.14159);
  sinr=sin((a-90)/360.0*2*3.14159);cosr=cos((a-90)/360.0*2*3.14159);
  deltax=14*cosr*(strlen(string)-0.5);deltay=14*sinr*(strlen(string)-0.5);
  xc=x +r*sinr-deltax;
  yc=y- r*cosr-deltay; 
  int i;
  deltax=0;deltay=0;
  for (i=0;i<strlen(string);i++) {yield();/*//Serial.println(*(string+i));*/drawRotated(xc,yc,*(string+i),scale,color,a);}
}

void Hershey::drawString(int x,int y,float scale,int color,char * string)
{
  ox=x;oy=y;
  int i;
  //Serial.printf("Entered drawStrig with string %s\n",string);
  for (i=0;i<strlen(string);i++) { if (i%10==9) yield(); draw(*(string+i),scale,color);}
}

void Hershey::drawStringOpaque(int x,int y,float scale,int fcolor,int bcolor,char * string)
{
	
	int width=getStringSize(string,scale);
	////Serial.print("String width is ");//Serial.print(width);//Serial.print(" for string ");//Serial.println(string);
	tft.fillRect(x,y-16*scale,width,(int)trunc(scale*32),bcolor);
	//Serial.printf("Entered drawStringOpaque with string %s'\n",string);
	drawString(x,y,scale,fcolor,string);
}

void Hershey::drawCenteredString(int y,float scale,int color,char * string)
{
  int xo,yo;
  yo=y;
  int i;
  int len=0;
  for (i=0;i<strlen(string);i++) len+=getSize(string+i,scale);
  yield();
  xo=160-len/2;
  drawString(xo,yo,scale,color,string);
}


int Hershey::getStringSize(char * it,float scale)
{
   int i;
   char * cp=it;
   int w=0;
   for (i=0;i<strlen(it);i++)
   {
     w+=getSize(cp++,scale);
   }
   return w;
}
int Hershey::getSize(char * it,float scale)
{

   float w=0;
   char ch=*it - ' ';
   fs::File fin=SPIFFS.open(fontFile,"r");
   char l,r;
   fin.seek(hFont[ch]+2,(fs::SeekMode)0);
   fin.readBytes(&l,1);
   fin.readBytes(&r,1);
   fin.close();
   w=scale*(-(l - 'R') + (r - 'R'))+0.5;
 //  char buf[64];
 //  sprintf((char *)&buf,"for %c at scale %f width is %d",*it,scale,(int)trunc(w));
 //  //Serial.println((char *)&buf);
   return trunc(w+0.5);
}

int di;
int donePoints=0;
void Hershey::getPt(int indx,float scale,fs::File fin)
{
	char c1,c2;
	fin.readBytes(&c1,1);fin.readBytes(&c2,1);
    if (c1==13) {donePoints=1;Serial.println("Set donePoints");return;}
    //Serial.printf("in getPt indx=%d c1=%c c2=%c\n",indx,c1,c2);
	if (c1==' ' && c2=='R')		
	{indx=1;getPt(0,scale,fin);getPt(1,scale,fin);di++;return;}
  pt[indx][0]=scale*(c1 - 'R')+0.5;
  pt[indx][1]=scale*(c2 - 'R')+0.5;
}

void drawLineAnti(int x0,int y0,int x1,int y1,unsigned int pcolor,bool bright) ;
void Hershey::draw(char chr,float scale,int color)
{
	//Serial.printf("Entered Draw with char %c\n",chr);
	donePoints=0;
  char  ch=chr-' ';
 // //Serial.println(chr);
   char buf[100];
   int indx=0;
   int np;
   int i;
   //sprintf((char *)&buf,"%c %c %c %c",*ch++,*ch++,*ch++,*ch++);
   ////Serial.println((char *)&buf);
   ch=chr-' ';
   fs::File fin=SPIFFS.open((char *)&fontFile,"r");
   if (fin!=0) //Serial.printf("draw opened %s\n",&fontFile);
   ////Serial.print(*ch);//Serial.println(*(ch+1));
   fin.seek(hFont[ch],(fs::SeekMode)0); // seek to character to be drawn
   fin.readBytes((char *)&buf,2);buf[2]=0;np=atoi((char *)&buf); // get # points
   //Serial.printf("Char %c has %d pairs\n",chr,np);
   char lc,rc;fin.readBytes(&lc,1);fin.readBytes(&rc,1);
   float l=-scale*(lc - 'R') -0.5;
   ox+=l;
   float r= scale*(rc - 'R')+0.5;
   //Serial.printf("Char %c has width %f\n",chr,l+r);
   int rpt=(int)ceil(scale);
   ////Serial.print("Repeat = ");//Serial.println(rpt);
   ////Serial.println(*cp);
   for (di=1;di<np;di++)
   {
     int rpt=(int)ceil(scale);
     // end of character processinf if (*cp=='#') {ox+=trunc(r+1);if (ox>320-scale*20) {ox=20;oy+=scale*32;}return;}
     // " R" detection if (*cp==' ' && *(cp+1)=='R')  {cp+=2;indx=0;}
	 //Serial.println(di);
	 char ins[2];
	 int pos=fin.position();
	 fin.readBytes((char *)&ins,2);
	 if (ins[0]==' ' && ins[1]=='R') indx=0;
	 else
	 {
	     fin.seek(pos,(fs::SeekMode)0);
		 if (indx==0) {getPt(0,scale,fin); indx=1;di++;}
		 getPt(1,scale,fin);
		 if (abs(pt[1][0]-pt[0][0])<1) // verticle line
		 for (i=0;i<rpt;i++)tft.drawLine(ox+i+pt[0][0],oy+pt[0][1],ox+i+pt[1][0],oy+pt[1][1],color);
		 else if (abs(pt[1][1]-pt[0][1])<1) // horizontal
		 for (i=0;i<rpt;i++)tft.drawLine(ox+pt[0][0],oy+i+pt[0][1],ox+pt[1][0],oy+i+pt[1][1],color); 
		 else
		 for (i=0;i<rpt;i++) { tft.drawLine(ox+i+pt[0][0],oy+pt[0][1],ox+i+pt[1][0],oy+pt[1][1],color);
		 tft.drawLine(ox+pt[0][0],oy+i+pt[0][1],ox+pt[1][0],oy+i+pt[1][1],color); if (strokeDelay!=0) delay(strokeDelay); }
		 //sprintf((char *)&buf,"%f %f %f %f",pt[0][0],pt[0][1],pt[1][0],pt[1][1]);
		 pt[0][0]=pt[1][0];pt[0][1]=pt[1][1];
		 //Serial.println((char *)&buf);
		 if (donePoints==1) break;
	 }
   }
   fin.close();
   ox+=trunc(r+1);
   if (ox>320-scale*20) {ox=5;oy+=scale*32;}
   return;
   
}

void Hershey::drawRotated(int xc,int yc,char chr,float scale,int color,float angle)
{
  char ch=chr-' ';
 float sinr=sin(angle/360.0*2*3.14159);
 float cosr=cos(angle/360.0*2*3.14159);
  angle=angle-90;
  int chngs=1;
  if (angle>90 && angle<270) {angle-=180;chngs=-1;}
 // //Serial.print(chr);//Serial.print(" ");//Serial.print(xc);//Serial.print(" ");//Serial.print(yc);//Serial.print(" ");//Serial.print(scale);//Serial.print(" ");//Serial.print(color);//Serial.print(" ");
 // //Serial.println(angle);
 float sina=sin(angle/360.0*2*3.14159);
 float cosa=cos(angle/360.0*2*3.14159);
   char buf[100];
   int indx=0;
   int i;
   //sprintf((char *)&buf,"%c %c %c %c",*ch++,*ch++,*ch++,*ch++);
   ////Serial.println((char *)&buf);
   ch=chr-' ';
   fs::File fin=SPIFFS.open((char *)&fontFile,"r");
   fin.seek(hFont[ch],(fs::SeekMode)0); // seek to character to be drawn
   int np;
   fin.readBytes((char *)&buf,2);buf[2]=0;np=atoi((char *)&buf);
   char c1,c2;
   fin.readBytes(&c1,1);fin.readBytes(&c2,1);
   float l=-scale*(c1 - 'R') -0.5;
  // ox+=l;
// x'=x*cos(a) -y*sin(a);
// y'=x*sin(a) +y*cos(a); 
    ox=xc+chngs*l*cosa+chngs*deltax;
    oy=yc+chngs*l*sina+chngs*deltay;
   float r= scale*(c2 - 'R')+0.5;
   int rpt=(int)ceil(scale);
   ////Serial.print("Repeat = ");//Serial.println(rpt);
   ////Serial.println(*cp);
   for (di=1;di<np;di++)
   {
     int rpt=(int)ceil(scale);
    // if (*cp=='#') {  deltax=r*cosa+l*cosa;deltay=r*sina+l*sina;return;}
    // if (*cp==' ' && *(cp+1)=='R')  {cp+=2;indx=0;}
	char ins[2];
	 int pos=fin.position();
	 fin.readBytes((char *)&ins,2);
	 if (ins[0]==' ' && ins[1]=='R') indx=0;
	 else
	 {   
		 fin.seek(pos,(fs::SeekMode)0);
		 if (indx==0) {getPt(0,scale,fin); indx=1;di++;float xp=pt[0][0]*cosa - pt[0][1]*sina; float yp=pt[0][0]*sina + pt[0][1]*cosa;pt[0][0]=xp;pt[0][1]=yp;}
		 if (indx==1) {getPt(1,scale,fin);float xp=pt[1][0]*cosa - pt[1][1]*sina;float yp=pt[1][0]*sina + pt[1][1]*cosa;pt[1][0]=xp;pt[1][1]=yp;}
	// x'=x*cos(a) -y*sin(a);
	// y'=x*sin(a) +y*cos(a);
		 if (abs(pt[1][0]-pt[0][0])<1) // verticle line
		 for (i=0;i<rpt;i++)tft.drawLine(ox+i+pt[0][0],oy+pt[0][1],ox+i+pt[1][0],oy+pt[1][1],color);
		 else if (abs(pt[1][1]-pt[0][1])<1) // horizontal
		 for (i=0;i<rpt;i++)tft.drawLine(ox+pt[0][0],oy+i+pt[0][1],ox+pt[1][0],oy+i+pt[1][1],color);
		 else
		 for (i=0;i<rpt;i++) { tft.drawLine(ox+i+pt[0][0],oy+pt[0][1],ox+i+pt[1][0],oy+pt[1][1],color);
		 tft.drawLine(ox+pt[0][0],oy+i+pt[0][1],ox+pt[1][0],oy+i+pt[1][1],color); }
		 sprintf((char *)&buf,"%f %f %f %f",ox+pt[0][0],oy+pt[0][1],ox+pt[1][0],oy+pt[1][1]);
		 pt[0][0]=pt[1][0];pt[0][1]=pt[1][1];
		 ////Serial.println((char *)&buf);
	 }
   }
   fin.close();
   deltax=r*cosa+l*cosa;deltay=r*sina+l*sina;
   return; 
}


unsigned int color;
 int dominant;
 int ca[3];
bool shiny;
#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))
#define swap_(a, b) do{ __typeof__(a) tmp;  tmp = a; a = b; b = tmp; }while(0)
void dominateColor(int color)
{
  ca[0]=( color & 0xf800) >> 11;
  ca[1]=(color & 0x07C0) >> 6;
  ca[2]=color & 0x001F;
  dominant=0;
  if (ca[1]>ca[0]) dominant=1;
  if (ca[2]>ca[dominant]) dominant=2;  
}

int  fcolor(float fract)
{
  // rrrrrggggggbbbbb
	int r,g,b;
  if (shiny)
  {
    r= (int)(trunc(31*(1.0-fract))+ca[0]);// << 11; //else r=31<<11;
    g= (int)(trunc(31*(1.0-fract))+ca[1]); // <<6; //else g=31<<6;
    b= (int)(trunc(31*(1.0-fract))+ca[2]); //else b=31;
    (r>31) ? r=31<<11 : r=r<<11;
    (g>31) ? g=31<<6 : g=g<<6;
    if (b>31)  b=31;
    return r+g+b;
  }
  else
  {
    r= (int)(ca[0]*fract)  << 11;
    g= (int)(ca[1]*fract) << 6;
    b= ca[2]*fract;
  }
	return r+g+b;
}

void plot(int x, int y, float c)
{
      if (c==1.0) {
      tft.drawPixel(x,y,color); return; }
      if (c==0.0) return;
      int cx=tft.readPixel(x,y);
      if (cx==color) return;
      tft.drawPixel(x,y,fcolor(c)); return;
      if (shiny) cx= cx & fcolor(c);
      else cx= cx | fcolor(c);
      tft.drawPixel(x,y,cx);
      yield();
}
void drawLineAnti(int x1, int y1, int x2,  int y2, unsigned int pcolor, bool bright);
// integer part of x
int ipart(float x) {return floor(x); }
//int round(float x) {return ipart(x + 0.5); }
// fractional part of x
float fpart(float x) {return x - floor(x); }
float rfpart(float x) {return 1 - fpart(x); }
void swap(int a,int b) {int temp=a; a=b;b=temp; }
void drawLineAnti2(
   int x1,  int y1,
   int x2,  int y2,
  unsigned int pcolor) { drawLineAnti(x1,y1,x2,y2,pcolor,0); }

void drawLineAnti(
   int x1,  int y1,
   int x2,  int y2,
  unsigned int pcolor,
  bool bright)
{
  color=pcolor;
  dominateColor(pcolor);
  shiny=bright;
  double dx = (double)x2 - (double)x1;
  double dy = (double)y2 - (double)y1;
  if ( fabs(dx) > fabs(dy) ) {
    if ( x2 < x1 ) {
      swap_(x1, x2);
      swap_(y1, y2);
    }
    double gradient = dy / dx;
    double xend = round_(x1);
    double yend = y1 + gradient*(xend - x1);
    double xgap = rfpart_(x1 + 0.5);
    int xpxl1 = xend;
    int ypxl1 = ipart_(yend);
    plot(xpxl1, ypxl1, 1.0); //rfpart_(yend)*xgap);
    plot(xpxl1, ypxl1+1, 0.0); //fpart_(yend)*xgap);
    double intery = yend + gradient;
 
    xend = round_(x2);
    yend = y2 + gradient*(xend - x2);
    xgap = fpart_(x2+0.5);
    int xpxl2 = xend;
    int ypxl2 = ipart_(yend);
    plot(xpxl2, ypxl2, 1.0); //rfpart_(yend) * xgap);
    plot(xpxl2, ypxl2 + 1,0.0); // fpart_(yend) * xgap);
 
    int x;
    for(x=xpxl1+1; x < xpxl2; x++) {
      plot(x, ipart_(intery), rfpart_(intery));
      plot(x, ipart_(intery) + 1, fpart_(intery));
      intery += gradient;
    }
  } else {
    if ( y2 < y1 ) {
      swap_(x1, x2);
      swap_(y1, y2);
    }
    double gradient = dx / dy;
    double yend = round_(y1);
    double xend = x1 + gradient*(yend - y1);
    double ygap = rfpart_(y1 + 0.5);
    int ypxl1 = yend;
    int xpxl1 = ipart_(xend);
    plot(xpxl1, ypxl1, 1.0);  //rfpart_(xend)*ygap);
    plot(xpxl1 + 1, ypxl1,0.0); // fpart_(xend)*ygap);
    double interx = xend + gradient;
 
    yend = round_(y2);
    xend = x2 + gradient*(yend - y2);
    ygap = fpart_(y2+0.5);
    int ypxl2 = yend;
    int xpxl2 = ipart_(xend);
    plot(xpxl2, ypxl2, 1.0); //rfpart_(xend) * ygap);
    plot(xpxl2 + 1, ypxl2,0.0); // fpart_(xend) * ygap);
    int y;
    for(y=ypxl1+1; y < ypxl2; y++) {
      plot(ipart_(interx), y, rfpart_(interx));
      plot(ipart_(interx) + 1, y, fpart_(interx));
      interx += gradient;
    }
  }
}