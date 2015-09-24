/*
 * A/D converter test for the Asuro
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
  int Data[2];
  
  asuro.setStatusLED(GREEN);         /* status led green */  
  
  //front LED on
  digitalWrite(frontled, HIGH);

  /* reading the line sensor photoresistors */
  asuro.readLinesensor(Data);
  Serial.println("left photoresistor");
  Serial.println(Data[0]);
  Serial.println("right photoresistor");
  Serial.println(Data[1]);

  /* odometry sensors  */
  asuro.readOdometry(Data);
  Serial.println("left odometry");
  Serial.println(Data[0]);
  Serial.println("right odometry");
  Serial.println(Data[1]);

  /* reading the battery */
  Serial. println("battery");
  Serial.println(asuro.readBattery());
  

}
