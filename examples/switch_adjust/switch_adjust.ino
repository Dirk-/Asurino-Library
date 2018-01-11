/*
 * Switch adjustment for the Asuro
 */
#include <Asuro.h>

Asuro asuro = Asuro();

void setup()
{
  asuro.Init();
  Serial.begin(2400);
  Serial.print("Original switch factor: ");
  Serial.println(asuro.getSwitchFactor());
}

void loop()
{
  int switches;
  int diff;
  long factor;

  while (Serial.available() > 0) {
    diff = Serial.parseInt();   // Enter positive or negative integer values
    if (Serial.read() == '\n') {
       factor = asuro.getSwitchFactor()+diff;
       asuro.setSwitchFactor(factor);
       Serial.print("Switch factor set to: ");
       Serial.println(factor);
    }
  }
        
  // front switch test
  switches = asuro.readSwitches();
  if (switches > 0)  // at least one switch was pressed
  {
    Serial.print("Value read: ");
    Serial.println(switches); 
    //Serial.print("Switches pressed: ");
    //Serial.println(Switches, BIN);   // send switch value as binary so one can identify the switches
    asuro.setStatusLED(RED);  
    delay(10); 
  }
  asuro.setStatusLED(GREEN); 
  
}
 
