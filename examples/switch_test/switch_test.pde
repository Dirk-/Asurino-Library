/*
 * Switch Test for the Asuro
 */
#include <Asuro.h>

Asuro asuro = Asuro();

void setup()
{
  asuro.Init();
//  Serial.begin(9600);
  Serial.begin(2400);
  asuro.setTimer2();       /* 36kHz for IR communication */
}

void loop()
{
  int Switches;
  
  /* front switch check */
  Switches = asuro.readSwitches();
  if (Switches)    /* switch pressed? */
  {
    Serial.println("switches pressed");
    Serial.println(Switches, BIN);   /* send swicth value binary */
    asuro.setStatusLED(RED);         /* set status led red */  
    delay(1000);                     /* wait 1 second */  
  }
  asuro.setStatusLED(GREEN);         /* status led green */  
  
}
 
