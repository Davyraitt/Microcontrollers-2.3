#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int digits[] = {
	0b00111111,	0b00000110,	0b01011011,
	0b01001111,	0b01100110,	0b01101101,
	0b01111101,	0b00000111,	0b01111111,
	0b01101111,	0b01110111,	0b01111100, 
	0b00111001, 0b01011110, 0b01111001,
	0b01110001
};

void display(int digit){
	if (digit > 15){
		PORTA = digits[14];
	} else {
		PORTA = digits[digit];
	}
}

int main(void)
{
	DDRA = 0xFF;	// PORTA output
    DDRD = 0x00;	// PORTD input
	
	int number = 0;
	
    while (1) 
    {
		if (PIND == 0b11){
			number = 0;
		} else if (PIND == 0b01){
			number++;
		} else if (PIND == 0b10){
			number--;
		}
		wait(100);
		display(number);
    }
}