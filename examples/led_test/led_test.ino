/*
 * LED test for the Asuro
 */
#include <Asuro.h>

Asuro asuro = Asuro();

void setup()
{
  asuro.Init();
  Serial.begin(2400);
}

void loop()
{
  // Status LED lightshow
  asuro.setStatusLED(RED);
  delay(200);
  asuro.setStatusLED(YELLOW);
  delay(200);
  asuro.setStatusLED(GREEN);
  delay(200);
  asuro.setStatusLED(OFF);  
  delay(200);
  asuro.setFrontLED(ON);  
  delay(200);
  asuro.setFrontLED(OFF);  
  
  // taillights 
  asuro.setBackLED (ON, ON);
  delay(200);
  asuro.setBackLED (OFF, ON);
  delay(200);
  asuro.setBackLED (ON, OFF);
  delay(200);
  asuro.setBackLED (ON, ON);
  delay(200);
}

