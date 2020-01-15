#include <sys/timeb.h>
#include <unistd.h>
#include <stdlib.h>
#include "ncurses.h"
#include "MotorHat.hpp"

#define AtoPWM(x) 8.3*(x)+1250

void CarDrive::ServoControl(int Servo_num, float Angle) {
    int PWMpin;
    if(Servo_num == 1) PWMpin = 0;
    else if(Servo_num == 2) PWMpin = 1;
    else if(Servo_num == 3) PWMpin = 14;
    else if(Servo_num == 4) PWMpin = 15;

    wiringPiI2CWriteReg8(fd, 0x06+4*PWMpin, 0 & 0xff);
    wiringPiI2CWriteReg8(fd, 0x07+4*PWMpin, 0 >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*PWMpin, (int)(AtoPWM(Angle)) & 0xff);
    wiringPiI2CWriteReg8(fd, 0x09+4*PWMpin, (int)(AtoPWM(Angle)) >> 8);
}

void CarDrive::WheelPWM(int DC_num, int PWM) {
    int DCpin;
    if(DC_num == 1) DCpin = 8;
    else if(DC_num == 2) DCpin = 13;
    else if(DC_num == 3) DCpin = 2;
    else if(DC_num == 4) DCpin = 7;
    
    wiringPiI2CWriteReg8(fd, 0x06+4*DCpin, 0 & 0xff);
    wiringPiI2CWriteReg8(fd, 0x07+4*DCpin, 0 >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*DCpin, PWM & 0xff);
    wiringPiI2CWriteReg8(fd, 0x09+4*DCpin, PWM >> 8);
}

void CarDrive::WheelForward(int DC_num) {
    int IN1, IN2, i;
    if(DC_num == 1) {
        IN1 = 9;
        IN2 = 10;
    }
    else if(DC_num == 2) {
        IN1 = 12;
        IN2 = 11;
    }
    else if(DC_num == 3) {
        IN1 = 3;
        IN2 = 4;
    }
    else if(DC_num == 4) {
        IN1 = 6;
        IN2 = 5;
    }
    for(i=4; i>=1; i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*IN1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN1, 4096/i >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN1, 0 >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*IN2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN2, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN2, 4096/i >> 8);
        usleep(5000);
    }
}

void CarDrive::WheelBackward(int DC_num) {
    int IN1, IN2, i;
    if(DC_num == 1) {
        IN1 = 9;
        IN2 = 10;
    }
    else if(DC_num == 2) {
        IN1 = 12;
        IN2 = 11;
    }
    else if(DC_num == 3) {
        IN1 = 3;
        IN2 = 4;
    }
    else if(DC_num == 4) {
        IN1 = 6;
        IN2 = 5;
    }
    for(i=4; i>=1; i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*IN1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN1, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN1, 4096/i >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*IN2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN2, 4096/i >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN2, 0 >> 8);
        usleep(5000);
    }
}

void CarDrive::WheelStop(int DC_num) {
    int IN1, IN2, i;
    if(DC_num == 1) {
        IN1 = 9;
        IN2 = 10;
    } 
    else if(DC_num == 2) {
        IN1 = 12;
        IN2 = 11;
    } 
    else if(DC_num == 3) {
        IN1 = 3;
        IN2 = 4;
    } 
    else if(DC_num == 4) {
        IN1 = 6;
        IN2 = 5;
    }
    for(i=4;i>=1;i--) {
        wiringPiI2CWriteReg8(fd, 0x06+4*IN1, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN1, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN1, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN1, 4096/i >> 8);

        wiringPiI2CWriteReg8(fd, 0x06+4*IN2, 0 & 0xff);
        wiringPiI2CWriteReg8(fd, 0x07+4*IN2, 0 >> 8);
        wiringPiI2CWriteReg8(fd, 0x08+4*IN2, 4096/i & 0xff);
        wiringPiI2CWriteReg8(fd, 0x09+4*IN2, 4096/i >> 8);
        usleep(5000);
    }
}

void CarDrive::InitMotorHat(int M_kind) {
    unsigned char oldmode, newmode;
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

void CarDrive::ControlCar(void) {
    char ch;

    while(1) {
        WheelStop(1);
        WheelStop(2);
        WheelStop(3);
        WheelStop(4);

        ch = getch();

        if(ch == 0xE0) ch = getch();

        if(ch == 'w' || ch == ARROW_UP) {
            WheelPWM(1, 2000);
            WheelPWM(2, 2000);
            WheelPWM(3, 2000);
            WheelPWM(4, 2000);

            WheelBackward(1);
            WheelBackward(2);
            WheelBackward(3);
            WheelBackward(4);
        }

        if(ch == 'x' || ARROW_DOWN) {
            WheelPWM(1, 2000);
            WheelPWM(2, 2000);
            WheelPWM(3, 2000);
            WheelPWM(4, 2000);

            WheelForward(1);
            WheelForward(2);
            WheelForward(3);
            WheelForward(4);
        }

        if(ch == 'a' || ARROW_LEFT) {
            WheelPWM(1, 2000);
            WheelPWM(2, 2000);
            WheelPWM(3, 2000);
            WheelPWM(4, 2000);

            WheelForward(1);
            WheelBackward(2);
            WheelBackward(3);
            WheelForward(4);
        }

        if(ch == 'd' || ARROW_RIGHT) {
            WheelPWM(1, 2000);
            WheelPWM(2, 2000);
            WheelPWM(3, 2000);
            WheelPWM(4, 2000);

            WheelBackward(1);
            WheelForward(2);
            WheelForward(3);
            WheelBackward(4);
        }

        if(ch == 'o') Angle = Angle + 5;
        else if(ch == 'p') Angle = Angle - 5;

        if(Angle > 50) Angle = 40;
        if(Angle < -50) Angle = -40;

        ServoControl(1, Angle);

        if(ch == 'q') {
            endwin();
            exit(0);
        }
        usleep(20000);
    }
}