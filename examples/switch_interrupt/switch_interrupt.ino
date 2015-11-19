/*
 * ASURO: Read switches via interrupt
 */
#include <Asuro.h>

#define SWITCHES_INTERRUPT 1

Asuro asuro = Asuro();

volatile int switchPressed = false;

void setup()
{
  asuro.Init();
  Serial.begin(2400);
  
  attachInterrupt(SWITCHES_INTERRUPT, switchesISR, CHANGE);
}


void switchesISR() {
    switchPressed = true;
}


void loop()
{
   asuro.setStatusLED(GREEN); 

  if (switchPressed) 
  {
    Serial.println("Boom!");
    asuro.setStatusLED(RED); 
    delay(1000);                     // wait 1 second  
    switchPressed = false; 
  }
}
 
