#include "seven_segmant.h"

void sevensegmant_w(char x){
	PORTB=(x<<4)|(PORTB & 0x0f); //Write On Led
}
void sevensegmant_init()
{
	
   DDRB |= 0xf0; //make port B(4,5,6,7);OUTPUT
	
   setbit(DDRA,6); //MAKE PORT B(1)
   setbit(DDRA,7);//MAKE PORT B(2)

} 