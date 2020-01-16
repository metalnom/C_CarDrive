
#include <wiringPi.h>
#include <wiringPiI2C.h>


#define DC_MOTOR 1
#define SG90 2

void ServoControl(int, float);

void setPWM(int, int);
void RotateForward(int);
void RotateBackward(int);
void StopMotor(int);
void InitAdaFruit(int);
