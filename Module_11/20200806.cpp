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
			int v = digitalRead(29);
			
		printf("Value=%u\r\n", v);
			
			if (v == 1)
			{
				digitalWrite(28, HIGH);
				
		}
			else
			{
				digitalWrite(28, LOW);
			}
			
			//delay
			delay(100);
		
	}
		
}