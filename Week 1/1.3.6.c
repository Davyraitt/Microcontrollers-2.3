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
	DDRD = 0xFF;
	DDRC = 0x00;
	
	int hertz = 1;
	
	while (1)
	{
		if (PINC & 0x01)
		{
			hertz = 4;
		} else {
			hertz = 1;
		}
		
		wait(1000/hertz);
		PORTD = 0x01;
		wait(1000/hertz);
		PORTD = 0;
	
	}

	return 1;
}
