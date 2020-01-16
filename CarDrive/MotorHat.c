#include <sys/timeb.h>
#include "MotorHat.h"

#define AtoPWM(x) 8.3*(x)+1250

int ad;



void ServoControl(int M_num, float An)
{
    int PWMpin;

    if (M_num == 1) {
        PWMpin = 0;

    } else if (M_num == 2) {
        PWMpin = 1;

    } else if (M_num == 3) {
        PWMpin = 14;

    } else if (M_num == 4) {
        PWMpin = 15;

    }

    wiringPiI2CWriteReg8(ad,0x06+4*PWMpin,0 & 0xff);
    wiringPiI2CWriteReg8(ad,0x07+4*PWMpin,0 >> 8);
    wiringPiI2CWriteReg8(ad,0x08+4*PWMpin,(int)(AtoPWM(An)) & 0xff);
    wiringPiI2CWriteReg8(ad,0x09+4*PWMpin,(int)(AtoPWM(An)) >> 8);


}


void setPWM(int M_num, int PWM)
{
    int PWMpin;


    if (M_num == 1) {
        PWMpin = 8;

    } else if (M_num == 2) {
        PWMpin = 13;

    } else if (M_num == 3) {
        PWMpin = 2;

    } else if (M_num == 4) {
        PWMpin = 7;

    }

    wiringPiI2CWriteReg8(ad,0x06+4*PWMpin,0 & 0xff);
    wiringPiI2CWriteReg8(ad,0x07+4*PWMpin,0 >> 8);
    wiringPiI2CWriteReg8(ad,0x08+4*PWMpin,PWM & 0xff);
    wiringPiI2CWriteReg8(ad,0x09+4*PWMpin,PWM >> 8);
}



void RotateForward(int M_num)
{
    int In1, In2, i;



    if (M_num == 1) {

        In1 = 9;
        In2 = 10;
    } else if (M_num == 2) {

        In1 = 12;
        In2 = 11;
    } else if (M_num == 3) {

        In1 = 3;
        In2 = 4;
    } else if (M_num == 4) {

        In1 = 6;
        In2 = 5;
    }


    for (i=4;i>=1;i--) {

    	wiringPiI2CWriteReg8(ad,0x06+4*In1,4096/i & 0xff);
   	wiringPiI2CWriteReg8(ad,0x07+4*In1,4096/i >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In1,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In1,0 >> 8);

    	wiringPiI2CWriteReg8(ad,0x06+4*In2,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x07+4*In2,0 >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In2,4096/i & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In2,4096/i >> 8);
        usleep(5000);
    }

}

void RotateBackward(int M_num)
{
    int In1, In2,i;


    if (M_num == 1) {

        In1 = 9;
        In2 = 10;
    } else if (M_num == 2) {

        In1 = 12;
        In2 = 11;
    } else if (M_num == 3) {

        In1 = 3;
        In2 = 4;
    } else if (M_num == 4) {

        In1 = 6;
        In2 = 5;
    }

    for (i=4;i>=1;i--) {
    	wiringPiI2CWriteReg8(ad,0x06+4*In1,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x07+4*In1,0 >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In1,4096/i & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In1,4096/i >> 8);

    	wiringPiI2CWriteReg8(ad,0x06+4*In2,4096/i & 0xff);
    	wiringPiI2CWriteReg8(ad,0x07+4*In2,4096/i >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In2,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In2,0 >> 8);
        usleep(5000);

    }
}

void StopMotor(int M_num)
{
    int In1, In2,i;


    if (M_num == 1) {

        In1 = 9;
        In2 = 10;
    } else if (M_num == 2) {

        In1 = 12;
        In2 = 11;
    } else if (M_num == 3) {

        In1 = 3;
        In2 = 4;
    } else if (M_num == 4) {

        In1 = 6;
        In2 = 5;
    }

    for (i=4;i>=1;i--) {
    	wiringPiI2CWriteReg8(ad,0x06+4*In1,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x07+4*In1,0 >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In1,4096 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In1,4096 >> 8);

    	wiringPiI2CWriteReg8(ad,0x06+4*In2,0 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x07+4*In2,0 >> 8);
    	wiringPiI2CWriteReg8(ad,0x08+4*In2,4096 & 0xff);
    	wiringPiI2CWriteReg8(ad,0x09+4*In2,4096 >> 8);
    	usleep(5000);
    }
}

void InitAdaFruit(int M_kind)
{

    unsigned char mode1, oldmode,newmode;
    float prescale;

    ad=wiringPiI2CSetup(0x70);

    wiringPiI2CWriteReg8(ad,0x01,0x04);
    wiringPiI2CWriteReg8(ad,0x00,0x01);

    usleep(5000);

    mode1 = wiringPiI2CReadReg8(ad,0x00);
    mode1 = mode1 & ~0x10;
    wiringPiI2CWriteReg8(ad,0x00,mode1);

    usleep(5000);

    prescale = 25000000.0;
    prescale /= 4096.0;
    if (M_kind == DC_MOTOR)  prescale /= 1600.0;
    else if (M_kind == SG90) prescale /= 200;
    prescale -= 0.5;

    oldmode = wiringPiI2CReadReg8(ad,0x00);
    newmode = (oldmode & 0x7F) | 0x10;
    wiringPiI2CWriteReg8(ad,0x00,newmode);
    wiringPiI2CWriteReg8(ad,0xFE,(unsigned char)prescale);
    wiringPiI2CWriteReg8(ad,0x00,oldmode);

    usleep(5000);

    wiringPiI2CWriteReg8(ad,0x00,oldmode | 0x80);
}


