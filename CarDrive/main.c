#include <stdlib.h>
#include "ncurses.h"
#include "fcntl.h"
#include <time.h>
#include "sys/timeb.h"
#include <linux/uinput.h>
#include <unistd.h>
#include "MotorHat.h"

#define ARROW_UP 3
#define ARROW_DOWN 2
#define ARROW_LEFT 4
#define ARROW_RIGHT 5

float Angle;

void Control_Car(void) {
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

int main(void) {
    InitMotorHat(SG90);
    initscr();
    keypad(stdscr, true);
    noecho();
    wiringPiSetupGpio();

    Angle = 0;
    ServoControl(1, Angle);
    Control_Car();
    return 0;
}