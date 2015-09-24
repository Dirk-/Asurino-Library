/*
 * LED test for the Asuro
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
  /* status LED lightshow */
  asuro.setStatusLED(RED);
  delay(200);
  asuro.setStatusLED(YELLOW);
  delay(200);
  asuro.setStatusLED(GREEN);
  delay(200);
  asuro.setStatusLED(OFF);  
  
  /*taillights (routine copypasted from asuro lib) */
  asuro.setBackLED (1,1);
  delay(200);
  asuro.setBackLED (0,1);
  delay(200);
  asuro.setBackLED (1,0);
  delay(200);
  asuro.setBackLED (1,1);
}

