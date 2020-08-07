#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

using namespace std;


void callback()
{
	printf("Button pushed \r\n");
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
	
	softToneCreate(6);
	softToneWrite(6, 700);
	delay(500);
	softToneWrite(6, 0);

	
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