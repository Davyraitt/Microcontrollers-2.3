#define F_CPU 8E6

#include <avr/io.h>
#include <stdint.h>
#include "lcd.h"


int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x01;
	init();
	
	display_text("Hello");
	
	set_cursor(10);
	display_text("World!");
	
    while (1) 
    {
		
    }
}


