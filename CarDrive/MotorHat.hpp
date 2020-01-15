#include <wiringPi.h>
#include <wiringPiI2C.h>

#define AtoPWM(x) 8.3*(x)+1250
#define DC_MOTOR 1
#define SG90 2

class MotorHat{
private:
    int fd;
    float Angle;
    
    
public:
    void ServoControl(int);
    void WheelPWM(int, int);
    void WheelForward(int);
    void WheelBackward(int);
    void WheelStop(int);
    void InitMotorHat(int);
    void Control_Car(void);

    MotorHat(int ang) : Angle(ang)
    { }
};