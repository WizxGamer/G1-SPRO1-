/*
 * BasicIO.c
 *
 * Created: 10/12/2018 18:02:06
 * Author : G1
 */ 
 
 #define F_CPU 16000000UL

 #include <stdio.h>
 #include <avr/io.h>
 #include <util/delay.h>
 #include "Audiomodule861.h"
 #include "i2cmaster.h"
 #include "PCA9685_SPRO1MC.h"
 #include "usart.h"
 
 
void initAll(void);
void resetfunction(void);

void platform(int);
void background(void);
void plane(int);
void bomb(void);
void valveControl(int); //Function parameter: ON time in ms

void set_RGB0(unsigned int red, unsigned int green, unsigned int blue);
void set_RGB1(unsigned int red, unsigned int green, unsigned int blue);
void set_RGB2(unsigned int red, unsigned int green);


int main(void) 
{
	DDRD = 0x0F;
	PORTD = 0x3F;
	PORTB = 0x01;
	PORTD = 0b11110000;
	
	initAll();
	/*
	plane();

	background();
	
	platform(1);
	
	_delay_ms(1000);
	platform(2);
	_delay_ms(1000);
	platform(3);
	_delay_ms(1000);
	platform(2);
	_delay_ms(1000);
	*/
	while(1)
	{
		plane(1);
		_delay_ms(1000);
		plane(2);
		_delay_ms(1000);
	}
	
	
 } 
void resetfunction(void)
{
    set_RGB0(0,0,0);
    set_RGB1(0,0,0);
	set_RGB2(0,0);
	
	PCA9685_set_pwm(SERVO1, 0, 0);
	PCA9685_set_pwm(SERVO2, 0, 0);
	PCA9685_set_pwm(SERVO3, 0, 0);
	PCA9685_set_pwm(SERVO4, 0, 0);
	PCA9685_set_pwm(SERVO4, 0, 0);
}

void plane(int n)
{
	int running = 1;
	int mask = 0b11100000;	
	while(running == 1)
	{
		switch(n)
		{
			case 1:
			if((PIND & mask) == mask)
			{
				PCA9685_set_pwm(SERVO4, 0, 319);
				running = 1;
			}
			
			else
			{
				PCA9685_set_pwm(SERVO4, 0, 0);
				running = 0;
			break;
			
			case 2:
			if((PIND & mask) == mask)
			{
				PCA9685_set_pwm(SERVO4, 0, 329);//326 slowest AC rotation
				running = 1;
			}
			
			else
			{
				PCA9685_set_pwm(SERVO4, 0, 0);
				running = 0;
			break;
			}
		 }
	  }		
	}
}

void platform(int n)
{
	switch(n)
	{
		case 1:
		PCA9685_set_pwm(SERVO1,0,100);
		break;
		
		case 2:
		PCA9685_set_pwm(SERVO1,0,300);
		break;
		
		case 3:
		PCA9685_set_pwm(SERVO1,0,500);
		break;
	}
}

void bomb(void)
{
	
}

void background(void)
{
	int running = 1;//Running var for truth parameter for while loop
	
	PCA9685_set_pwm(SERVO2,0,400);//Running to change position from hole
	_delay_ms(250);
	
	while((running == 1))
	{
		if (!(PINB & 0x01))
		{
			PCA9685_set_pwm(SERVO2,0,400);
			running = 1;
		}
		
		else
		{	
			PCA9685_set_pwm(SERVO2, 0, 0);
			running = 0;
		}
	}
}
 
void valveControl(int a)//Change trigger pin if possible
{
	PCA9685_set_pwm(SERVO5, 0,4090);
	for (int i=0;i<a;i++)
	{
		_delay_ms(1);
	}

	PCA9685_set_pwm(SERVO5, 0, 0);
}


void set_RGB0(unsigned int red, unsigned int green, unsigned int blue)
{
	PCA9685_set_pwm(LED1, 0, red);
	PCA9685_set_pwm(LED2, 0, green);
	PCA9685_set_pwm(LED3, 0, blue);
}

void set_RGB1(unsigned int red, unsigned int green, unsigned int blue)
{
	PCA9685_set_pwm(LED5, 0, red);
	PCA9685_set_pwm(LED6, 0, green);
	PCA9685_set_pwm(LED7, 0, blue);
}

void set_RGB2(unsigned int red, unsigned int green)
{
	PCA9685_set_pwm(LED4, 0, red);
	PCA9685_set_pwm(LED8, 0, green);
}

void initAll(void)
{
	uart_init(); // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the uart
	i2c_init();
	PCA9685_init_pwm(PWM_FREQUENCY_50); //function for the servos and the LEDs	AP_init(); //function for music
	resetfunction();
	AP_select_track_start(1);
}