/*
 * Motor test for the Asuro
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
  // Test motion patterns
  asuro.driveCircular (MAX_SPEED);

  int var = 0;
  while (var < 10) {
    asuro.driveSquare (100, MAX_SPEED);
    var++;
  }
  
  // test engines backward and forward
  asuro.setMotorSpeed(MAX_SPEED, MAX_SPEED);
  //forward
  asuro.setMotorDirection (FWD, FWD);
  delay (500);
  asuro.setMotorDirection (BWD, BWD);
  delay (500);  
  asuro.setMotorSpeed(OFF, OFF);
}

