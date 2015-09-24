/*
 
 Modified version of v0.3 of the Asurino lib inside the AsuroLib at SourceForge. 
 It corrects some errors and adds some small enhancements.
 
 Changes:
    -   Added setFrontLED
    -   Corrected readOdometry and readLinesensor
    -   Added some comments
    -   Rearranged constants
 
 */

#include "Asuro.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
extern "C" {
#include <inttypes.h>
#include <avr/interrupt.h>
}

// internal constants
#define rforward 13
#define rreverse 12
#define lforward 5
#define lreverse 4
#define lmotor 9
#define rmotor 10
#define statusledred 2
#define frontled 6
#define irtxled 11
#define lphotores 3
#define rphotores 2
#define statusledgreen 8
#define odometricled 7
#define lodometric 1
#define rodometric 0
#define switches 4
#define battery 5
#define lbackled 1
#define rbackled 0
#define IR_CLOCK_RATE    36000L

/* Asuro infrared UART interfaces uses Timer2 with 72kHz */
/* counts falling and rising edge => 36kHz*2 = 72kHz */
#if defined(__AVR_ATmega168__)
SIGNAL(SIG_OUTPUT_COMPARE2A) {
}
#else
//SIGNAL(SIG_OUTPUT_COMPARE2) {
ISR(TIMER2_COMP_vect) {
}
#endif

Asuro::Asuro(void)
{
    pinMode(rforward, OUTPUT);
    pinMode(rreverse, OUTPUT);
    pinMode(lforward, OUTPUT);
    pinMode(lreverse, OUTPUT);
    pinMode(frontled, OUTPUT);
    pinMode(statusledred, OUTPUT);
    pinMode(statusledgreen, OUTPUT);
    pinMode(odometricled, OUTPUT);
    pinMode(irtxled, OUTPUT);
    
    // fix analog-to-digital converter timing (for 8 MHz clock)
    ADCSRA &= ~ADPS0;
    setTimer2();
}

void Asuro::Init(void)
{
    pinMode(rforward, OUTPUT);
    pinMode(rreverse, OUTPUT);
    pinMode(lforward, OUTPUT);
    pinMode(lreverse, OUTPUT);
    pinMode(frontled, OUTPUT);
    pinMode(statusledred, OUTPUT);
    pinMode(statusledgreen, OUTPUT);
    pinMode(odometricled, OUTPUT);
    pinMode(irtxled, OUTPUT);
    
    // fix analog-to-digital converter timing (for 8 MHz clock)
    ADCSRA &= ~ADPS0;
    setTimer2();
}

// Set Timer2 for infrared transmitter
void Asuro::setTimer2(void)
{
    /* Asuro infrared UART interfaces uses Timer2 with 72kHz */
#if defined(__AVR_ATmega168__)
    // toggle on compare, clk/1
    TCCR2A = _BV(WGM21) | _BV(COM2A0);
    TCCR2B = _BV(CS20);
    // 36kHz carrier/timer
    OCR2A = 0x6e;    //(F_CPU/(IR_CLOCK_RATE*2L)-1);
#else
    // toggle on compare, clk/1
    TCCR2 = _BV(WGM21) | _BV(CS20) | _BV(COM20);
    // 36kHz carrier/timer
    OCR2 = 0x6e;    //(F_CPU/(IR_CLOCK_RATE*2L)-1);
#endif
    DDRB |= _BV(PB3);
}


//taillight LEDs
void Asuro::setBackLED(unsigned char left, unsigned char right)
{
    if (left || right) {
        PORTD &= ~(1 << PD7); // Wheel LED OFF
        DDRC |= (1 << PC0) | (1 << PC1); // Output => no odometrie
        PORTC |= (1 << PC0) | (1 << PC1);
    }
    if (!left) PORTC &= ~(1 << PC1);
    if (!right) PORTC &= ~(1 << PC0);
}

//
void Asuro::setFrontLED(unsigned char status)
{
    digitalWrite(frontled, status);
}

// Bicolor Status LED
void Asuro::setStatusLED(unsigned char color)
{
    if (color == OFF)    {digitalWrite(statusledgreen, LOW); digitalWrite(statusledred, LOW);}
    if (color == GREEN)  {digitalWrite(statusledgreen, HIGH); digitalWrite(statusledred, LOW);}
    if (color == YELLOW) {digitalWrite(statusledgreen, HIGH); digitalWrite(statusledred, HIGH);}
    if (color == RED)    {digitalWrite(statusledgreen, LOW); digitalWrite(statusledred, HIGH);}
}

//read front switches
int Asuro::readSwitches(void)
{
    long tmp;
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    delayMicroseconds(10);
    tmp = analogRead(switches);
    digitalWrite(3, LOW);
    return ((10240000L/tmp-10000L)*MY_SWITCH_VALUE+5000L)/10000;
}


//read battery
int Asuro::readBattery(void)
{
    int tmp;
    uint8_t oldadmux = (ADMUX & (unsigned int) 0xf0);
    ADMUX = (1 << REFS0) | (1 << REFS1);
    delayMicroseconds(10);
    tmp = analogRead(battery);
    ADMUX = oldadmux;
    return tmp;
}

//read odometry
void Asuro::readOdometry(int *data)
{
    uint8_t oldadmux = (ADMUX & (unsigned int) 0xf0);
    ADMUX = (1 << REFS0) ;
    DDRC &= ~((1 << PC0) | (1 << PC1));   // Back-LEDs off
    digitalWrite(odometricled, HIGH);
    delayMicroseconds(10);
    data[LEFT] = analogRead(lphotores);
    data[RIGHT] = analogRead(rphotores);
    ADMUX = oldadmux;
}

//read line sensors
void Asuro::readLinesensor(int *data)
{
    uint8_t oldadmux = (ADMUX & (unsigned int) 0xf0);
    ADMUX = (1 << REFS0) ;
    data[LEFT] = analogRead(lodometric);
    data[RIGHT] = analogRead(rodometric);
    ADMUX = oldadmux;
}

//motor direction
void Asuro::setMotorDirection (int left, int right)
{
    if (left == FWD)
    {
        //left motor forwards
        digitalWrite (4, LOW);
        digitalWrite (5, HIGH);
    }
    else
    {
        //left motor backwards
        digitalWrite (4, HIGH);
        digitalWrite (5, LOW);
    }
    if (right == FWD)
    {
        //right motor forwards
        digitalWrite (12, LOW);
        digitalWrite (13, HIGH);
    }
    else
    {
        //right motor backwards
        digitalWrite (12, HIGH);
        digitalWrite (13, LOW);
    }
}

//motor speed
void Asuro::setMotorSpeed (int left, int right)
{
    lmotorspeed = left;
    rmotorspeed = right;
    analogWrite(9, lmotorspeed);
    analogWrite(10, rmotorspeed);
}

//"square" motion pattern
void Asuro::driveSquare(int timeForOneEdge, int speed)
{
    setMotorSpeed(speed, speed);
    //forwards
    setMotorDirection (1, 1);
    delay (timeForOneEdge);
    //right
    setMotorDirection (1,0);
    delay (timeForOneEdge);
    //backwards
    setMotorDirection (0, 0);
    delay (timeForOneEdge);
    //left
    setMotorDirection (0,1);
    delay (timeForOneEdge);
    setMotorSpeed(0, 0);
}

//circular accelerating motion pattern
void Asuro::driveCircular(int maxSpeed)
{
    int var = 0;
    if (maxSpeed > 255)
        maxSpeed = 255;
    while(var < maxSpeed)
    {
        //left motor forwards
        digitalWrite (4, LOW);
        digitalWrite (5, HIGH);
        //right motor backwards
        digitalWrite (12, HIGH);
        digitalWrite (13, LOW);
        setMotorSpeed(var, var);
        delay(25);
        var++;
    }
}

