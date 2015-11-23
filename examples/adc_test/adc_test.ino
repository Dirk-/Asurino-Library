 /*
 * A/D converter test for the Asuro
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
  int Data[2];
  
  asuro.setStatusLED(GREEN);  
  asuro.setFrontLED(ON);

  // Read the line sensor photoresistors
  asuro.readLinesensor(Data);
  Serial.print("Left photoresistor: ");
  Serial.println(Data[LEFT]);
  Serial.print("Right photoresistor: ");
  Serial.println(Data[RIGHT]);

  // Read odometry sensors
  asuro.readOdometry(Data);
  Serial.print("Left odometry: ");
  Serial.println(Data[LEFT]);
  Serial.print("Right odometry: ");
  Serial.println(Data[RIGHT]);

  // Read battery charge
  Serial.print("Battery: ");
  Serial.println(asuro.readBattery());

}
