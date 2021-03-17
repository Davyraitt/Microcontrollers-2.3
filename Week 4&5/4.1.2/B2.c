#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8e6
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
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11000110;		// ADC-enable, no interrupt, start, free running disable, division by 64
}

int main( void )
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcInit();

	while (1)
	{
		ADCSRA |= BIT(6);	// Re-enable ADC to start conversion again
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}
