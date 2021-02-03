#define F_CPU 8E6

#include <avr/io.h>
#include <util/delay.h>

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
		
	PORTD = 0x01;
	while (1)
	{
		if (PORTD == 0x80)
		{
			PORTD = 0x01;
		}
		else 
		{
			PORTD = PORTD << 1;
		}
		wait(50);
	}

	return 1;
}
