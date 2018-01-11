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

#include "Asuro.h"


// ------------ Internal constants

// Pin numbers for usage with analog/digitalRead/Write
// These numbers correspond to the Arduino board, see
// https://www.arduino.cc/en/Hacking/PinMapping and
// http://www.asurowiki.de/pmwiki/pmwiki.php/Main/Prozessor
#define DP_PB5 13
#define DP_PB4 12
#define DP_PD5 5
#define DP_PD4 4
#define PWM_MOTOR_L 9
#define PWM_MOTOR_R 10

// Constants specific to the ASURO board
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

// Calculation factor for the switches bit field
#define STANDARD_SWITCH_FACTOR 62L


// -------------

void (*ISRfunction)();


// Asuro infrared UART interfaces uses Timer2 with 72kHz
// counts falling and rising edge => 36kHz*2 = 72kHz
#if defined(__AVR_ATmega168__)
SIGNAL(SIG_OUTPUT_COMPARE2A) {
}
#else
//SIGNAL(SIG_OUTPUT_COMPARE2) {
ISR(TIMER2_COMP_vect) {
}
#endif


#if defined (__AVR_ATmega8__)
ISR (TIMER1_COMPA_vect)
{
    (*ISRfunction)();
}
#else
#error CPU type not yet supported
#endif


/*
     Constructor
*/
Asuro::Asuro(void)
{
    // Do almost nothing. We could call Init() here, but we will adhere to the ASURO standard.
    _switchFactor = STANDARD_SWITCH_FACTOR;
}

/*
     Constructor
     
     switchFactor Calculation factor for the switches bit field. Standard value is 62 (decimal).
*/
Asuro::Asuro(long switchFactor)
{
    // Do almost nothing. We could call Init() here, but we will adhere to the ASURO standard.
    _switchFactor = switchFactor;
}


/*
     Initializes the hardware (ports, ADC, PWM)
     This function has to be called by every program first
*/
void Asuro::Init(void)
{
    // Ports for motor control
    pinMode(DP_PB4, OUTPUT);
    pinMode(DP_PB5, OUTPUT);
    pinMode(DP_PD4, OUTPUT);
    pinMode(DP_PD5, OUTPUT);
    
    pinMode(frontled, OUTPUT);
    pinMode(statusledred, OUTPUT);
    pinMode(statusledgreen, OUTPUT);
    pinMode(odometricled, OUTPUT);
    pinMode(irtxled, OUTPUT);
    
    // for PWM (8-Bit PWM) on OC1A & OC1B
    TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);

    // fix analog-to-digital converter timing (for 8 MHz clock)
    ADCSRA &= ~ADPS0;
    prepareIRTransmitter();
}


/*
     Start Timer1 to carry out a periodically called task
     
     ms 			Time in milliseconds
     isrfunction 	Function to be carried out (void, no parameters)
*/
void Asuro::startTimer1(unsigned long ms, void (*isrfunction)())
{
#if defined (__AVR_ATmega8__)
    ISRfunction = isrfunction;
    
    TCCR1A = 0x00;      // Timer does not use PWM
    
    // ASURO clock rate (F_CPU) is 8 MHz. Prescaler of 1024 gives 7812,5 ticks per second
    TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM12); // Prescale = 1024, CTC ("Clear Timer on Compare")
    
    // Hier wird der Vergleichswert gesetzt
    unsigned long compare = F_CPU / 1024L * ms  / 1000L;
    OCR1A = compare;
    
    TIMSK |= (1<<OCIE1A); // Compare A Match Interrupt aktivieren
#else
#error CPU type not yet supported
#endif
}


/*
     Stop Timer1
*/
void Asuro::stopTimer1()
{
#if defined (__AVR_ATmega8__)
    // Disable timer via timer/counter interrupt mask register
    TIMSK &= ~(1<<OCIE1A);
    // Re-enable PWM (8-Bit PWM) on OC1A & OC1B
    TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
#else
#error CPU type not yet supported
#endif
}


/*
     Prepare infrared transmitter (uses Timer2)
*/
void Asuro::prepareIRTransmitter(void)
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


/*
     Set back LEDs, values: ON, OFF
     
     left 	left LED status
     right 	right LED status
*/
void Asuro::setBackLED(unsigned char left, unsigned char right)
{
	if (left) {
		PORTD &= ~(1 << PD7); // Wheel LED OFF
		DDRC |= (1 << PC1); // Output => no odometrie
		PORTC |= (1 << PC1);
	}
	else {
		PORTD |= (1 << PD7); 
		DDRC &=~ (1 << PC1); 
		PORTC &=~ (1 << PC1);
	}
	if (right) {
		PORTD &= ~(1 << PD7); // Wheel LED OFF
		DDRC |= (1 << PC0); // Output => no odometrie
		PORTC |= (1 << PC0);
	}
	else {
		PORTD |= (1 << PD7); 
		DDRC &=~ (1 << PC0); 
		PORTC &=~ (1 << PC0);
	}	
}


/*
     Controls the front LED
     status values: ON, OFF
*/
void Asuro::setFrontLED(unsigned char status)
{
    digitalWrite(frontled, status);
}


/*
     Controls the status LED
     color values: OFF, GREEN, RED, YELLOW
*/
void Asuro::setStatusLED(unsigned char color)
{
    if (color == OFF)    {digitalWrite(statusledgreen, LOW); digitalWrite(statusledred, LOW);}
    if (color == GREEN)  {digitalWrite(statusledgreen, HIGH); digitalWrite(statusledred, LOW);}
    if (color == YELLOW) {digitalWrite(statusledgreen, HIGH); digitalWrite(statusledred, HIGH);}
    if (color == RED)    {digitalWrite(statusledgreen, LOW); digitalWrite(statusledred, HIGH);}
}


/*
     Set the calculation factor for the switches bit field.
     Standard value is 62 (decimal). Vary this value if you get
     wrong results from the readSwitches() function.
*/
void Asuro::setSwitchFactor(long switchFactor)
{
    _switchFactor = switchFactor;
}
    
/*
     Get the calculation factor for the switches bit field.
     Standard value is 62 (decimal). 
*/
long Asuro::getSwitchFactor(void)
{
    return _switchFactor;
}
    
/*
     Read out switches
     
     returns bit field of switch value bit0 = K6, ... , bit5 = K1
*/
int Asuro::readSwitches(void)
{
    long tmp;
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    delayMicroseconds(10);
    tmp = analogRead(switches);	// 0..1023
    digitalWrite(3, LOW);
    return ((10240000L/tmp-10000L)*_switchFactor+5000L)/10000;
}


/*
     Returns the battery voltage
     
     return ADC value. range: 0..1023
*/
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


/*
     Reads out the odometry sensors
     
     data 	Pointer to the data destination array. access: data[LEFT], data[RIGHT]
*/
void Asuro::readOdometry(int *data)
{
    digitalWrite(odometricled, HIGH);
    data[LEFT] = analogRead(lodometric);
    data[RIGHT] = analogRead(rodometric);
}


/*
     Reads out photo transistors of line sensor
     
     data 	Pointer to the data destination array. access: data[LEFT], data[RIGHT]
*/
void Asuro::readLinesensor(int *data)
{
    uint8_t oldadmux = (ADMUX & (unsigned int) 0xf0);
    ADMUX = (1 << REFS0) ;
    data[LEFT] = analogRead(lphotores);
    data[RIGHT] = analogRead(rphotores);
    ADMUX = oldadmux;
}


/*
     Motor configuration. values: FWD, BWD, RWD, (BREAK, FREE not yet available)
     
     left left motor direction
     right right motor direction
*/
void Asuro::setMotorDirection (int left, int right)
{
    switch (left) {
        case FWD:
            digitalWrite (DP_PD4, LOW);
            digitalWrite (DP_PD5, HIGH);
            break;
        case RWD:
            digitalWrite (DP_PD4, HIGH);
            digitalWrite (DP_PD5, LOW);
            break;
        case BREAK:
            digitalWrite (DP_PD4, LOW);
            digitalWrite (DP_PD5, LOW);
            break;
        case FREE:
            digitalWrite (DP_PD4, HIGH);
            digitalWrite (DP_PD5, HIGH);
            break;
        default:
            break;
    }
    
    switch (right) {
        case FWD:
            digitalWrite (DP_PB4, LOW);
            digitalWrite (DP_PB5, HIGH);
            break;
        case RWD:
            digitalWrite (DP_PB4, HIGH);
            digitalWrite (DP_PB5, LOW);
            break;
        case BREAK:
            digitalWrite (DP_PB4, LOW);
            digitalWrite (DP_PB5, LOW);
            break;
        case FREE:
            digitalWrite (DP_PB4, HIGH);
            digitalWrite (DP_PB5, HIGH);
            break;
        default:
            break;
    }
}


/*
     Sets motor speed. range: 0..255
     
     left 	speed of left motor
     right 	speed of right motor
*/
void Asuro::setMotorSpeed (int left, int right)
{
	left = constrain(left, -255, 255);
	right = constrain(right, -255, 255);
	int motorDirs[2] {FWD, FWD};
	if (left < 0) {
		left = -left;
		motorDirs[LEFT] = RWD;
	}
	if (right < 0) {
		right = -right;
		motorDirs[RIGHT] = RWD;
	}
	Asuro::setMotorDirection(motorDirs[LEFT], motorDirs[RIGHT]);
    analogWrite(PWM_MOTOR_L, left);
    analogWrite(PWM_MOTOR_R, right);
}


    /*
     Drive a square figure for demo purposes
     
     timeForOneEdge		time in ms
     speed				Range 0..255
     */
void Asuro::driveSquare(int timeForOneEdge, int speed)
{
	int timeForTurning = 200;	// Estimated time for making a right turn in full speed
	
	for (int i=0; i<4; i++) {	
    	// Drive forward
    	setMotorSpeed(speed, speed);
    	setMotorDirection (FWD, FWD);
    	delay (timeForOneEdge);
    	
    	// Turn right
    	setMotorSpeed(255, 255);
    	setMotorDirection (FWD, RWD);
    	delay (timeForTurning);
		}

    setMotorSpeed(0, 0);
}


/*
     Spin around for demo purposes
*/
void Asuro::driveCircular(int maxSpeed)
{
    int var = 0;
    if (maxSpeed > 255)
        maxSpeed = 255;
    setMotorDirection(FWD, RWD);
    while(var < maxSpeed)
    {
        setMotorSpeed(var, var);
        delay(25);
        var++;
    }
}

