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
  asuro.driveCircular (255);

  int var = 0;
  while (var < 10) {
    asuro.driveSquare (100, 255);
    var++;
  }
  
  // test engines backward and forward
  asuro.setMotorSpeed(255, 255);
  //forward
  asuro.setMotorDirection (1, 1);
  delay (500);
  asuro.setMotorDirection (0,0);
  delay (500);  
  asuro.setMotorSpeed(0,0);
}

