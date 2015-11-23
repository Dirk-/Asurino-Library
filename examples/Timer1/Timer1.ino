 /*
 * Timer1-Test for the Asuro
 */
#include <Asuro.h>

Asuro asuro = Asuro();

/*
 * Action to be carried out every time the timer fires
 */
void blink()
{
  // State of the LED is kept between calls of the function
  static boolean output = HIGH;

  // Set the state
  asuro.setFrontLED(output);

  // Invert the state
  output = !output; 
}


void setup()
{
  asuro.Init();
  Serial.begin(2400);

  // Just print some info about the robot
  Serial.print("ASURO Frequency: ");
  Serial.println(F_CPU);

  // We want the front LED to blink every 0.5 seconds
  asuro.startTimer1(500, blink);
}


void loop()
{
  Serial.println("Blinking should have started now.");
  delay(10000);
  asuro.stopTimer1();
  Serial.println("Blinking should have stopped now.");
  delay(10000);
  asuro.startTimer1(500, blink);
}

