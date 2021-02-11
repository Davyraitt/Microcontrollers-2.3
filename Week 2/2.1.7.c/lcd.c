#define F_CPU 8E6

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

void blinkE(){
	//In order to confirm our command we need to blink the E pin.
	PORTC |= (1<<3);
	_delay_ms(1);
	PORTC &= ~(1<<3);
	_delay_ms(1);
}

void displaySend(char bytes, int rs){
	// Command comes in as 8 bits
	// 1010 0101
	// First we send the left 4 bits (Upper nibble)
	// Then the right 4 bits (Lower nibble)

	if (rs) rs = 1; //RS defines if its a command or a character
	
	// First nibble.
	PORTC = (bytes & 0xF0);
	PORTC |= (rs<<2);
	blinkE();

	// Second nibble
	PORTC = (bytes << 4);
	PORTC |= (rs<<2);
	blinkE();
}

void charSend(char character){
	displaySend(character, 1);
}

void cmdSend(char cmd){
	displaySend(cmd, 0);
}

void init(){
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x20;
	blinkE();

	cmdSend(0x28);
	cmdSend(0x0F);
	cmdSend(0x06);
	return_home();
}



void display_text(char *str){
	for (; *str; str++)
	{
		charSend(*str);
	}
}

void return_home(){
	cmdSend(0x02);
}

void set_cursor(int position){
	return_home();
	for (int i = 0; i < position; i++)
	{
		cmdSend(0b00010100);
	}

}