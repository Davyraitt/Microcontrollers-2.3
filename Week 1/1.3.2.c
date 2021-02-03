#define F_CPU 8E6

#include <avr/io.h>

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
	
	while (1)
	{
		PORTD = 0b01000000;
		wait( 500 );
		PORTD = 0b10000000;
		wait( 500 );
	}
	
	return 1;
}

