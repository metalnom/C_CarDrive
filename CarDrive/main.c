
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
	//wchar_t ch;
	
	while( 1 ){

	        //usleep(20000);
		StopMotor(1);
		StopMotor(2);	


		//sleep(1)
		ch=getch();

		if (ch == 0xE0) ch=getch();
		

		if (ch == 'w' || ch == ARROW_UP) {

			setPWM(1,2000);
			setPWM(2,2000); 

			RotateBackward(1);
			RotateBackward(2);

			
		}
	
		else if (ch == 'x' || ch == ARROW_DOWN) {

			setPWM(1,2000);
			setPWM(2,2000); 

			RotateForward(1);
			RotateForward(2);

		}

		else if (ch == 'a'|| ch == ARROW_LEFT) {

			setPWM(2,2000);
			
			RotateBackward(2);
			
		
		}

		else if (ch == 'd' || ch == ARROW_RIGHT) {

			
			setPWM(1,2000); 

			RotateBackward(1);

			
		}

		if (ch == 'o') Angle = Angle +2;
		else if (ch == 'p') Angle=Angle-2;

		if (Angle > 50) Angle =40;
		if (Angle < -50) Angle = -40;

		ServoControl(1,Angle);

		
		
        	if (ch == 'q') {
	            endwin();
		    //system("sudo halt");
	            exit(0);
        	}
		usleep(20000);

	}
}

int main(int argc, char *argv[]){

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
