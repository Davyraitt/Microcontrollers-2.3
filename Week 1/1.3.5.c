#define F_CPU 8E6

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main( void )
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	int length = 29;
	uint8_t frames[] = {
		0b00000001,
		0b00000011,
		0b00000111,
		0b00001111,
		0b00011111,
		0b00111111,
		0b01111111,
		0b11111111,
		0b11111110,
		0b11111100,
		0b11111000,
		0b11110000,
		0b11100000,
		0b11000000,
		0b10000000,
		0b00000000,
		0b00000011,
		0b00000000,
		0b00000110,
		0b00000000,
		0b00001100,
		0b00000000,
		0b00011000,
		0b00000000,
		0b00110000,
		0b00000000,
		0b01100000,
		0b00000000,
		0b11000000
	};
	
	while (1)
	{
		for(int i=0; i < length; i++)
		{
			PORTA = frames[i];
			PORTB = frames[i];
			PORTC = frames[i];
			PORTD = frames[i];
			PORTE = frames[i];
			PORTF = frames[i];
			PORTG = frames[i];
			wait(100);
		}
	}

	return 1;
}
