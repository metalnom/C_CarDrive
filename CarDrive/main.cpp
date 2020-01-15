#include <stdlib.h>
#include "ncurses.h"
#include "fcntl.h"
#include <time.h>
#include "sys/timeb.h"
#include <linux/uinput.h>
#include <unistd.h>
#include "MotorHat.hpp"




int main(void) {
    MotorHat motorhat(0);
    
    motorhat.InitMotorHat(SG90);
    initscr();
    keypad(stdscr, true);
    noecho();
    wiringPiSetupGpio();

    motorhat.ServoControl(1);
    motorhat.Control_Car();
    return 0;
}