#include "APP.h"

void init_System();

ISR(INT0_vect)
{
	Setting_Mode();
}
ISR(INT1_vect)
{
	Setting_Mode();

}



int main(void)
{		
	init_System();   //initialize registers

    /* Replace with your application code */
    while (1) 
    {
    app();
    }
}

void init_System()
{
	 EEPROM_Init();//initialize EEPROM Registers
	 ADC_init();   //initialize ADC Registers
	 sevensegmant_init(); //initialize 7-segment
     init_led_timer();    //initialize led timer
	clearbit(DDRC,3); //for ON/OFF
    setbit(DDRD,7);   //for heater motor
    setbit(DDRD,6);   //for cooler motor
    setbit(DDRD,5);   //for led
     
	setbit(PORTA,6);   //for seven segmant
	setbit(PORTA,7);   //for seven segmant
	sevensegmant_w(8); //test all seven segmant led's
	_delay_ms(1500);
    clearbit(PORTA,6);   
    clearbit(PORTA,7);
	_delay_ms(500);
	
	if (EEPROM_Read(0x0100)=="0")  //if no temp set set default = 60
	{
		EEPROM_Write(0x0100,"60");
	}
}