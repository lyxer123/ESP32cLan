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
  float i,j;
  pinMode(2,"INPUT");
  setServoReport(1);
  for (j=0.0;j<25.0;j+=1.0)
  {
    for (i=2;i<4096;i+=2*sqrt(i)) {analogWrite(2,(int)(i));delay(25);}
    for (i=4096;i>0;i-=2*sqrt(i)) {analogWrite(2,(int)(i));delay(25);}
    setServoReport(0);
    printf("%0.0f\n",j);
  }
}

void loop()
{

}