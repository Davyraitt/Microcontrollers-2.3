/*
 * Week1.c
 *
 * Created: 3-2-2021 09:52:47
 * Author : Davy
 */ 

#include <avr/io.h>
#define F_CPU 8E6
#include <util/delay.h>

int main(void)
{
	
	DDRE = 0XFF; // DDRE OP OUTPUT ZETTEN (We willen die lampjes laten branden)
	DDRD = 0x00; // DDRD OP INPUT ZETTEN
	PORTE = 0x01; 
	int currentbit = 99;
    /* Replace with your application code */
    while (1) 
    {
		//LOOP START (start bit is 99)	##########################
		// Vanuit Start kan je naar STATE1 door D6 in te drukken
	
		while (currentbit == 99) {
			PORTE = 0b11111111;
			if (PIND == 0b01000000) { //Als 6 ingedrukt wordt
				currentbit = 1;
			}
		}
		
		//LOOP S1	##########################
		//Bij loop 1 kan 7 --> Start
		//Of 5 --> State 2
		while (currentbit == 1) {
			PORTE = 0b00000001;
			if (PIND == 0b1000000) { //Als 7 ingedrukt wordt, terug naar start
				currentbit = 99;
			}
			if (PIND == 0b0010000) { //Als 5 ingedrukt wordt, naar state 2
				currentbit = 2;
			}
		}
		
		//LOOP S2	##########################
		//Bij loop 2 kan 
		//   7 --> Start
		//Of 6 --> State 1
		//Of 5 --> State 3
		while (currentbit == 2) {
			PORTE = 0b00000010;
			if (PIND == 0b1000000) {  // 7 --> Start
				currentbit = 99;
			}
			if (PIND == 0b0100000) {  //6 --> State 1
				currentbit = 1;
			}
			
			if (PIND == 0b0010000) {  //5 --> State 3
				currentbit = 3;
			}
		}
		
		//LOOP S3	##########################
		//Bij loop 3 kan
		//   7 --> Start
		//Of 6 -->	END
		//Of 5 --> END
		while (currentbit == 3) {
			PORTE = 0b0000100;
			if (PIND == 0b1000000) {  // 7 --> Start
				currentbit = 99;
			}
			if (PIND == 0b0100000) {  //6 --> END
				currentbit = 98;
			}
			
			if (PIND == 0b0010000) {  //5 --> END
				currentbit = 98;
			}
		}
		
		//LOOP END	##########################
		//Bij loop END kan
		//   7 --> Start
		while (currentbit == 98) {
			PORTE = 0b1010101;
			if (PIND == 0b1000000) {  // 7 --> Start
				currentbit = 99;
			}
		}
		
		
		
    }
}

