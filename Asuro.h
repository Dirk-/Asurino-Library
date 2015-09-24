#ifndef Asuro_h
#define Asuro_h

#include <inttypes.h>

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

#define OFF 0
#define ON 1
#define RED 2
#define GREEN 3
#define YELLOW 4

#define LEFT 0
#define RIGHT 1

#define IR_CLOCK_RATE    36000L

// user adjustable values
#define MY_SWITCH_VALUE  62L

class Asuro {
public:
  Asuro(void);
  void Init(void);
  void setTimer2(void);
  void setBackLED(unsigned char left, unsigned char right);
  void setStatusLED(unsigned char color);
  int readSwitches(void);
  int readBattery(void);
  void readOdometry(int *data);
  void readLinesensor(int *data);
  void setMotorDirection (int left, int right);
  void setMotorSpeed (int left, int right);
  void driveSquare(int size, int speed);
  void driveCircular(int length);


private:
  int lmotorspeed;
  int rmotorspeed;
};

#endif
