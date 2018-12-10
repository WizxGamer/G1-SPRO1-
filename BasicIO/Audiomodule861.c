/*
 * Audiomodule861.c
 * Author: sh
 * Created: 26-11-2015
 * Modified: 29-08-2016
 * Version:	2.0
 * Release:	20160829
 */ 


#define F_CPU 16E6
#include <util/delay.h>
#include <avr/io.h>

void AP_select_track_start(unsigned char track)
{
	while(PIND & 0b00000100);		// wait while Busy pin is active
	track &= 0x07;
	track = track << 1;
	PORTB |= 0b00001110;
	PORTB &=~(track);
	while(!(PIND & 0b00000100));	// wait for Busy pin to be active
}

void AP_stop(void)
{
	PORTB |= 0b00001110;
}

void AP_wait_busy(void)
{
	while(PIND & 0b00000100);
}


void AP_init(void)
{
	DDRB |= 0b00001110;				// PB1, PB2, PB3 output
	PORTB |= 0b00001110;			// PB1, PB2, PB3 high
	DDRD &= ~0b00000100;			// PD2 input
}