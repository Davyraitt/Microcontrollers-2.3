/*
 * counter_t2_interrupt.c
 *
 * Created: 21/02/2021 13:00:25
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define BIT(x)			(1 << (x))

volatile int TimerPreset = -1;  // 0xF6, 10 till overflow
volatile int overflowValue = 0;

// Interrupt routine timer2 overflow
ISR( TIMER2_OVF_vect ) {
	TCNT2 = TimerPreset;	// Preset value
	overflowValue++;		// Increment counter
	clear();
	char countString[5];
	itoa(overflowValue, countString, 10);
	display_text(countString);
}

// Initialize timer2
void timer2Init( void ) {
	TCNT2 = TimerPreset;	// Preset value of counter 2
	TIMSK |= BIT(6);		// T2 overflow interrupt enable
	sei();				// turn_on intr all
	TCCR2 = 0x07;		// Initialize T2: ext.counting, rising edge, run
}

int main(void) {
	
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	DDRA = 0xFF;			// set PORTA for output (shows countregister)
	DDRB = 0xFF;			// set PORTB for output (shows overflowValue)
	
	timer2Init();
	init();

	while (1) {
		PORTA = TCNT2;		// show value counter 2
		PORTB = overflowValue;	// show value tenth counter
		wait(100);
	}
}
