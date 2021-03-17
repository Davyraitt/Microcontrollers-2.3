#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <stdio.h>

#define BIT(x)	(1 << (x))

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

void adcInit( void )
{
	ADMUX = 0b11100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running disable, division by 64
}

int main( void )
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	init(); // Init LCD
	adcInit();

	while (1)
	{
		PORTB = ADCL;
		PORTA = ADCH;
		return_home();
		char buffer[6];
		sprintf(buffer, "%dC", (int)ADCH);
		display_text(buffer); //Display text on LCD
		wait(200);
	}
}
