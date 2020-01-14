#include <sys/timeb.h>
#include <unistd.h>
#include "MotorHat.h"

#define AtoPWM(x) 8.3*(x)+1250

int fd;

void ServoControl(int Servo_num, float Angle) {
    int PWMpin;
    if(Servo_num == 1) {
        PWMpin = 0;
    } else if(Servo_num == 2) {
        PWMpin = 1;
    } else if(Servo_num == 3) {
        PWMpin = 14;
    } else if(Servo_num == 4) {
        PWMpin = 15;
    }
    wiringPiI2CWriteReg8(fd, 0x06+4*PWMpin, 0 & 0xff);
    wiringPiI2CWriteReg8(fd, 0x07+4*PWMpin, 0 >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*PWMpin, (int)(AtoPWM(Angle)) & 0xff);
    wiringPiI2CWriteReg8(fd, 0x09+4*PWMpin, (int)(AtoPWM(Angle)) >> 8);
}

void WheelPWM(int DC_num, int PWM) {
    int DCpin;

    if(DC_num == 1) {
        DCpin = 8;
    } else if(DC_num == 2) {
        DCpin = 13;
    } else if(DC_num == 3) {
        DCpin = 2;
    } else if(DC_num == 4) {
        DCpin = 7;
    }
    wiringPiI2CWriteReg8(fd, 0x06+4*DCpin, 0 & 0xff);
    wiringPiI2CWriteReg8(fd, 0x07+4*DCpin, 0 >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*DCpin, PWM & 0xff);
    wiringPiI2CWriteReg8(fd, 0x09+4*DCpin, PWM >> 8);
}

void WheelForward(int DC_num) {
    int In1, In2, i;

    if(DC_num == 1) {
        In1 = 9;
        In2 = 10;
    } else if(DC_num == 2) {
        In1 = 12;
        In2 = 11;
    } else if(DC_num == 3) {
        In1 = 3;
        In2 = 4;
    } else if(DC_num == 4) {
        In1 = 6;
        In2 = 5;
    }
    for(i=4;i>=1;i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*In1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In1, 4096/i >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In1, 0 >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*In2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In2, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In2, 4096/i >> 8);
        usleep(5000);
    }
}

void WheelBackward(int DC_num) {
    int In1, In2, i;

    if(DC_num == 1) {
        In1 = 9;
        In2 = 10;
    } else if(DC_num == 2) {
        In1 = 12;
        In2 = 11;
    } else if(DC_num == 3) {
        In1 = 3;
        In2 = 4;
    } else if(DC_num == 4) {
        In1 = 6;
        In2 = 5;
    }
    for(i=4;i>=1;i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*In1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In1, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In1, 4096/i >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*In2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In2, 4096/i >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In2, 0 >> 8);
        usleep(5000);
    }
}

void WheelStop(int DC_num) {
    int In1, In2, i;

    if(DC_num == 1) {
        In1 = 9;
        In2 = 10;
    } else if(DC_num == 2) {
        In1 = 12;
        In2 = 11;
    } else if(DC_num == 3) {
        In1 = 3;
        In2 = 4;
    } else if(DC_num == 4) {
        In1 = 6;
        In2 = 5;
    }
    for(i=4;i>=1;i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*In1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In1, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In1, 4096/i >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*In2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*In2, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*In2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*In2, 4096/i >> 8);
        usleep(5000);
    }
}
void InitMotorHat(int M_kind) {
    unsigned char mode1, oldmode, newmode;
    float prescale;

    fd = wiringPiI2CSetup(0x70);

    wiringPiI2CWriteReg8(fd, 0x01, 0x04);
    wiringPiI2CWriteReg8(fd, 0x00, 0x01);
    usleep(5000);

    prescale = 25000000.0;
    prescale /= 4096.0;

    if(M_kind == DC_MOTOR) prescale /= 1600.0;
    else if(M_kind == SG90) prescale /= 200;
    prescale -= 0.5;

    oldmode = wiringPiI2CReadReg8(fd, 0x00);
    newmode = (oldmode & 0x7F) | 0x10;
    wiringPiI2CWriteReg8(fd, 0x00, newmode);
    wiringPiI2CWriteReg8(fd, 0xFE, (unsigned char)prescale);
    wiringPiI2CWriteReg8(fd, 0x00, oldmode);

    usleep(5000);

    wiringPiI2CWriteReg8(fd, 0x00, oldmode | 0x80);
}