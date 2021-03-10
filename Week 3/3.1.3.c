#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void timer2Init( void ) {
	OCR2 = 250;
	TIMSK |= BIT(7);
	sei();
	TCCR2 = 0b00000010;
}

int count = 0;	
ISR( TIMER2_COMP_vect ) {
	count++;
	if (count == 60){
		PORTC = 0;		
	} else if (count >= 140) {
		PORTC = BIT(0);
		count = 0;
	}	
}

int main( void ) {
	DDRC = 0xFF;			
	timer2Init();

	while (1) { 
		wait(20); 
	}
}