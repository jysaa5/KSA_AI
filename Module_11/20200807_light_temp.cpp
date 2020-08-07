#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>
#include <wiringPiI2C.h>

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
	

	int fd_i2c = wiringPiI2CSetup(0x48);
	
	while (true)
	{
		wiringPiI2CWrite(fd_i2c, 0x40);
		// throw away first value
		wiringPiI2CRead(fd_i2c);
		// read second value 
		printf("Light: %02i\t", wiringPiI2CRead(fd_i2c));
		
		wiringPiI2CWrite(fd_i2c, 0x41);
		wiringPiI2CRead(fd_i2c);
		printf("Temp: %02i\t", wiringPiI2CRead(fd_i2c));
		
		wiringPiI2CWrite(fd_i2c, 0x43);
		wiringPiI2CRead(fd_i2c);
		printf("VR: %02i\n", wiringPiI2CRead(fd_i2c));
	}
	
	

	
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