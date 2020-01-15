#include <stdlib.h>
#include "ncurses.h"
#include "fcntl.h"
#include <time.h>
#include "sys/timeb.h"
#include <linux/uinput.h>
#include <unistd.h>
#include "MotorHat.h"

int main(void) {
    CarDrive CarD;
    CarD.InitMotorHat(SG90);
    initscr();
    keypad(stdscr, true);
    noecho();
    wiringPiSetupGpio();

    CarD.Angle = 0;
    CarD.ServoControl(1, CarD.Angle);
    CarD.ControlCar();
    
    return 0;
}

