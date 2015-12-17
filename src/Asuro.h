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
#include <inttypes.h>

#define OFF     0
#define ON      1
#define RED     2
#define GREEN   3
#define YELLOW  4

#define LEFT    0
#define RIGHT   1

#define FWD     1
#define RWD     0
#define BREAK	3
#define FREE	4


// user adjustable values
#define MY_SWITCH_VALUE  62L


// Class definition
class Asuro {

public:
    /*
     Constructor
     */
    Asuro(void);
    
    /*
     Initializes the hardware (ports, ADC, PWM)
     this function has to be called by every program first
     */
    void Init(void);
    
    /*
     Prepare infrared transmitter
     */
    void setTimer2(void);
    
    /*
     Start Timer1 to carry out a periodically called task
     ms Time in milliseconds
     isrfunction Function to be carried out (void, no parameters)
     */
    void startTimer1(unsigned long ms, void (*isrfunction)());
    
    /*
     Stop Timer1
     */
    void stopTimer1();

    /*
     Set back LEDs, values: ON, OFF
     left left LED status
     right right LED status
     */
    void setBackLED(unsigned char left, unsigned char right);
    
    /*
     Controls the StatusLED
     color values: OFF, GREEN, RED, YELLOW
     */
    void setStatusLED(unsigned char color);
    
    /*
     Controls the FrontLED
     status values: ON, OFF
     */
    void setFrontLED(unsigned char status);
    
    /*
     Read out switches
     bit field of switch value bit0 = K6, ... , bit5 = K1
     */
    int readSwitches(void);
    
    /*
     Returns the battery voltage
     return ADC value. range: 0..1023
     */
    int readBattery(void);
    
    /*
     Reads out the odometry sensors
     data pointer to the data destination. access: data[LEFT], data[RIGHT]
     */
    void readOdometry(int *data);
    
    /*
     Reads out photo transistors of line sensor
     data pointer to the data destination. access: data[LEFT], data[RIGHT]
     */
    void readLinesensor(int *data);
    
    /*
     Motor configuration. values: FWD, RWD, (BREAK, FREE not yet available)
     left left motor direction
     right right motor direction
     */
    void setMotorDirection (int left, int right);
    
    /*
     Sets motor speed. range: 0..255
     left speed of left motor
     right speed of right motor
     */
    void setMotorSpeed (int left, int right);
    
    /*
     Drive a square figure
     */
    void driveSquare(int timeForOneEdge, int speed);
    
    /*
     Spin around
     */
    void driveCircular(int maxSpeed);
    
    
};

#endif
