#include <iostream>
#include <wiringPi.h>

using namespace std;

// pin number
#define PIN_NUM 28

int main(void)
{
	
	if (wiringPiSetup() == -1)
	{
		return -1;
	}
	//inital
	
	wiringPiSetup();
	// Pin = 28
	pinMode(PIN_NUM, OUTPUT);
	
	// LED Toggle
	while(true)
	{
		int v = digitalRead(29); 
		if (v == 1)
		{
			digitalWrite(PIN_NUM, 1);
			delay(500);	
		}
		else
		{
			digitalWrite(PIN_NUM, 0);
			delay(500);
		}
	}
	return 0;
}