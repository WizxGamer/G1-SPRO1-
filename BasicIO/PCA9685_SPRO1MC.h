/*
 * PCA9685_SPRO1MC.h
 * Author:		sh
 * Created:		10-09-2015 
 * Modified:	05-10-2015
 * Version:		1.0
 * Release:		20151005
 */ 



#ifndef PCA9685_SPRO1MC_H_
#define PCA9685_SPRO1MC_H_

#define PCA_ADR 0x80
#define PWM_FREQUENCY_200 30
#define PWM_FREQUENCY_100 60
#define PWM_FREQUENCY_60 100
#define PWM_FREQUENCY_50 121

#define PWM_REGISTER(n) (0x06 + n*4)

#define SERVO1 PWM_REGISTER(0)
#define SERVO2 PWM_REGISTER(1)
#define SERVO3 PWM_REGISTER(2)
#define SERVO4 PWM_REGISTER(3)
#define SERVO5 PWM_REGISTER(4)
#define SERVO6 PWM_REGISTER(5)
#define SERVO7 PWM_REGISTER(6)
#define SERVO8 PWM_REGISTER(7)

#define LED1 PWM_REGISTER(8)
#define LED2 PWM_REGISTER(9)
#define LED3 PWM_REGISTER(10)
#define LED4 PWM_REGISTER(11)
#define LED5 PWM_REGISTER(12)
#define LED6 PWM_REGISTER(13)
#define LED7 PWM_REGISTER(14)
#define LED8 PWM_REGISTER(15)

void PCA9685_set_pwm(unsigned char motor_number, unsigned int on_value, unsigned int off_value);
void PCA9685_init_pwm(unsigned char frequency);

#endif