void setup();
void loop();
int main(int argc,char ** argv)
{
  setup();
  //for (;;) loop();
  // Uncomment to run loop forever.
  //  When running loop forever,
  //  you'll get no response to web events
  return 0;
}

void setup()
{
  int i;char buf[33]; 
  oclear();
  odrawString(0,0,"Display is 6x21");
  for (i=1;i<6;i++) {
    sprintf((char *)&buf,"Display line %d is drawn here",i);
    odrawString(0,10*i,(char *)&buf);
  }
  odisplay();
  delay(5000);
  oclear();
  odrawString(0,25,"Hello World");
  odisplay();delay(3000);oconsoleInit();
  for (i=0;i<21;i++)
  {
    sprintf((char *)&buf,"Line %d is put on the display here",i);
    oconsolePrintln((char *)&buf);delay(250);
  }
}

void loop()
{

}