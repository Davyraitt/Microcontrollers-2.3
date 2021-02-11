#define F_CPU 8E6

#include <avr/io.h>
#include <stdint.h>
#include "lcd.h"


int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x01;
	init();
	
	set_cursor(5);
	display_text("a");
	
	set_cursor(1);
	display_text("6");
	
	
    while (1) 
    {
		
    }
}


