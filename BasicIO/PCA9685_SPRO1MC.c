/*
 * PCA9685_SPRO1MC.c
 * Author:		sh
 * Created:		10-09-2015 
 * Modified:	05-10-2015
 * Version:		1.0
 * Release:		20151005
 */ 

#include "PCA9685_SPRO1MC.h"
#include "i2cmaster.h"

void PCA9685_set_pwm(unsigned char pwm_reg, unsigned int on_value, unsigned int off_value)
{
	if(on_value > 0xFFF) on_value = 0;
	if(off_value > 0xFFF) off_value = 0;
	
	i2c_start(PCA_ADR + I2C_WRITE);
	i2c_write(pwm_reg);
	i2c_write(on_value&0x0FF);
	on_value >>= 8;
	i2c_write(on_value);
	i2c_write(off_value & 0x0FF);
	off_value >>= 8;
	i2c_write(off_value);
	i2c_stop();
}

void PCA9685_init_pwm(unsigned char frequency)
{
	i2c_start(PCA_ADR + I2C_WRITE);
	i2c_write(0x00);
	i2c_write(0b00110000);					// sleep and autoinc
	i2c_stop();
	
	i2c_start(PCA_ADR + I2C_WRITE);
	i2c_write(0xFE);
	i2c_write(frequency);					// set PWM frequency
	i2c_stop();
	
	i2c_start(PCA_ADR + I2C_WRITE);
	i2c_write(0x00);
	i2c_write(0b00100000);					// autoinc
	i2c_stop();
}