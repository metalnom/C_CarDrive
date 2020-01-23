#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DC_MOTOR 1
#define SG90 2
#define ARROW_UP 3
#define ARROW_DOWN 2
#define ARROW_LEFT 4
#define ARROW_RIGHT 5

int fd;

class CarDrive {

    public:
        float Angle;
        void ServoControl(int, float);
        void WheelPWM(int, int);
        void WheelForward(int);
        void WheelBackward(int);
        void WheelStop(int);
        void InitMotorHat(int);
        void ControlCar(void);
};
