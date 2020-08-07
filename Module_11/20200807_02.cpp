#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

using namespace std;

/* GPIO25 */
#define SPKR 6
/* number of total school bell*/
#define TOTAL 32


/*frequency*/
int notes[]
{
	391, 391, 440, 440, 391, 391, 329, 329, 
	391, 391, 329, 329, 293, 293, 293, 0, 
	391, 391, 440, 440, 391, 391, 329, 329, 
	391, 329, 293, 329, 261, 261, 261, 0
}
;

int flag_play;

PI_THREAD(play)
{
	
	while (true)
	{
		if (flag_play == 1)
		{
			
		
			for (int i = 0; i < TOTAL; i++)
			{
				softToneWrite(SPKR, notes[i]);
				delay(280);
				
				if (flag_play == 0)
				{
					softToneWrite(SPKR, 0);
					break;
				}
				
			}
		}
		else
		{
			delay(100);
		}
	}
}


void callback()
{
	printf("Button pushed \r\n");
	
	if (flag_play == 0)
	{
		flag_play = 1;
	}
	else
	{
		flag_play = 0;
	}
	
	delay(50);
}



int main(int argc, char *argv[])
{
	//inital
	wiringPiSetup();
	
	// Output
	pinMode(28, OUTPUT);
	// Input
	pinMode(29, INPUT);
	
	softPwmCreate(28, 0, 100);
	softPwmWrite(28, 0);
	
	// Interrupt
	wiringPiISR(29, INT_EDGE_RISING, callback);
	
	// Speaker
	softToneCreate(SPKR);
	// Speaker thread
	piThreadCreate(play);
	
	
	int direction = 0;
	int value = 0;
	
	while (true)
	{
		
		if (direction == 0)
		{
			softPwmWrite(28, value++);
			printf("led on \n");
			
			if (value >= 100)
			{
				direction = 1;
			}
		}
		else
		{
			softPwmWrite(28, value--);
			if (value <= 0)
			{
				direction = 0;
			}
		}
		delay(10);
	}

}