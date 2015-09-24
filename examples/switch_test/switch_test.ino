/*
 * Switch Test for the Asuro
 */
#include <Asuro.h>

Asuro asuro = Asuro();

void setup()
{
  asuro.Init();
  Serial.begin(2400);
  asuro.setTimer2();       /* 36kHz for IR communication */
}

void loop()
{
  int Switches;
  
  // front switch test
  Switches = asuro.readSwitches();
  if (Switches)    /* switch pressed? */
  {
    Serial.print("Switches pressed: ");
    Serial.println(Switches, BIN);   // send switch value as binary so one can identify the switches
    asuro.setStatusLED(RED);  
    delay(1000);                     // wait 1 second  
  }
  asuro.setStatusLED(GREEN); 
  
}
 
