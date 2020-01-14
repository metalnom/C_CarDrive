#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DC_MOTOR 1
#define SG90 2

void ServoControl(int, float);
void WheelPWM(int, int);
void WheelForward(int);
void WheelBackward(int);
void WheelStop(int);
void InitMotorHat(int);
