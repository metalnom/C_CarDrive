#include "ncurses.h"
#include "fcntl.h"
#include <time.h>
#include "sys/timeb.h"
#include <linux/uinput.h>

#include "MotorHat.h"

#define ARROW_UP 3
#define ARROW_DOWN 2
#define ARROW_LEFT 4
#define ARROW_RIGHT 5

float Angle;

void Control_Car(void){
	char ch;
	
	while( 1 ){
		StopMotor(1);
		StopMotor(2);
		StopMotor(3);
		StopMotor(4);	

		ch=getch();

		if (ch == 0xE0) ch=getch();

		if (ch == 'w' || ch == ARROW_UP) {
			setPWM(1,2000);
			setPWM(2,2000);
		    setPWM(3,2000);
			setPWM(4,2000);	

			RotateForward(1);
			RotateForward(2);
			RotateForward(3);
			RotateForward(4);
		}
	
		else if (ch == 'x' || ch == ARROW_DOWN) {
			setPWM(1,2000);
			setPWM(2,2000);
		    setPWM(3,2000);
			setPWM(4,2000);	

			RotateBackward(1);
			RotateBackward(2);
			RotateBackward(3);
			RotateBackward(4);
		}

		else if (ch == 'a'|| ch == ARROW_LEFT) {
			setPWM(1,2000);
			setPWM(2,2000);
			setPWM(3,2000);
			setPWM(4,2000);
			
			RotateForward(1);
			RotateBackward(2);
			RotateBackward(3);
			RotateForward(4);
		}

		else if (ch == 'd' || ch == ARROW_RIGHT) {
			setPWM(1,2000);
		    setPWM(2,2000);
			setPWM(3,2000);
			setPWM(4,2000);	

			RotateBackward(1);
			RotateForward(2);
			RotateForward(3);
			RotateBackward(4);
		}

		if (ch == 'o') Angle = Angle +4;
		else if (ch == 'p') Angle=Angle-4;

		if (Angle > 24) Angle = 20;
		if (Angle < -24) Angle = -20;

		ServoControl(1,Angle);
		
       	if (ch == 'q') {
	        endwin();
	        exit(0);
		}
		usleep(20000);
	}
}

int main(){
    InitAdaFruit(SG90);
    initscr();
    keypad(stdscr,true);
    noecho();
    wiringPiSetupGpio();
    
    Angle=0;
    ServoControl(1,Angle);
    Control_Car();

	return 0;
}
