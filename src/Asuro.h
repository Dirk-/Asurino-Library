#ifndef Asuro_h
#define Asuro_h
/*
 
 Modified version of v0.3 of the Asurino lib inside the AsuroLib at SourceForge.
 It corrects some errors and adds some small enhancements.
 
 Changes:
 -   Added setFrontLED
 -   Corrected readOdometry and readLinesensor
 -   Added some comments
 -   Rearranged constants
 -   New Arduino library format
 -   Added interrupt example
 
 Modifications by Dirk Froehling, November 2015
 
 License: GNU General Public License version 2.0 (GPLv2)
 
 */
#include "Arduino.h"

// LED values
#define OFF     0
#define ON      1
#define RED     2
#define GREEN   3
#define YELLOW  4

// Array indexes for line sensor and odometry
#define LEFT    0
#define RIGHT   1

// Motor directions
#define FWD     1
#define BWD     0
#define RWD     0	// Same as BWD
#define BREAK	3
#define FREE	4


// Class definition
class Asuro {

public:
    /*
     Constructor
     */
    Asuro(void);
    
    /*
     Constructor
     */
    Asuro(long switchFactor);
    
    /*
     Set the calculation factor for the switches bit field
     */
    void setSwitchFactor(long switchFactor);
    
	/*
     Get the calculation value for the switches bit field
	*/
	void Asuro::getSwitchFactor(void);

    /*
     Initializes the hardware (ports, ADC, PWM)
     This function has to be called by every program first
     */
    void Init(void);
    
    /*
     Start Timer1 to carry out a periodically called task. This interferes with
     the motor pwm signals, so don't use it when driving
     
     ms 			Time in milliseconds
     isrfunction 	Function to be carried out (void, no parameters)
     */
    void startTimer1(unsigned long ms, void (*isrfunction)());
    
    /*
     Stop Timer1
     */
    void stopTimer1();

    /*
     Set back LEDs, values: ON, OFF
     
     left 			left LED status
     right 			right LED status
     */
    void setBackLED(unsigned char left, unsigned char right);
    
    /*
     Controls the status LED
     
     color 			Values: OFF, GREEN, RED, YELLOW
     */
    void setStatusLED(unsigned char color);
    
    /*
     Controls the front LED
     
     status 		Values: ON, OFF
     */
    void setFrontLED(unsigned char status);
    
    /*
     Read out switches
     
     returns bit field of switch value bit0 = K6, ... , bit5 = K1
     */
    int readSwitches(void);
    
    /*
     Returns the battery voltage
     
     return ADC value. range: 0..1023
     */
    int readBattery(void);
    
    /*
     Reads out the odometry sensors
     
     expects data pointer to the data destination. access: data[LEFT], data[RIGHT]
     */
    void readOdometry(int *data);
    
    /*
     Reads out photo transistors of line sensor
     
     expects data pointer to the data destination. access: data[LEFT], data[RIGHT]
     */
    void readLinesensor(int *data);
    
    /*
     Motor configuration. values: FWD, RWD, (BREAK, FREE not yet available)
     
     left			left motor direction
     right 			right motor direction
     */
    void setMotorDirection (int left, int right);
    
    /*
     Sets motor speed. range: 0..255
     left speed of left motor
     right speed of right motor
     */
    void setMotorSpeed (int left, int right);
    
    /*
     Drive a square figure for demo purposes
     */
    void driveSquare(int timeForOneEdge, int speed);
    
    /*
     Spin around for demo purposes
     */
    void driveCircular(int maxSpeed);
    
private:
	/*
	 Variable for the calculation factor for the switches bit field
	 */
	long _switchFactor = 62L;
	
    /*
     Prepare infrared transmitter (uses Timer2), called from Init()
     */
	void prepareIRTransmitter(void);

};

#endif
