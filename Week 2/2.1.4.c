#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR( INT1_vect ) {
	if (PORTC == 0x80){
		PORTC = 0x01;
	} else {
		PORTC = PORTC << 1;		
	}
}

ISR( INT2_vect ) {
	if (PORTC == 0x01){
		PORTC = 0x80;
	} else {
		PORTC = PORTC >> 1;		
	}
}

int main( void ) {
	// Init I/O
	DDRD = 0x00;			// PORTD input
	DDRC = 0xFF;			// PORTC output

	PORTC = 0x01;

	// Init Interrupt hardware
	EICRA |= 0x3C;			// INT1 & INT2 op rising edge
	EIMSK |= 0x06;			// INT2 & INT1 aanzetten
	
	sei();				

	while (true){
		
	}

	return 1;
}
