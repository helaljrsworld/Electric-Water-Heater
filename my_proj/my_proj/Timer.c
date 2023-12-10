#include "Timer.h"

void init_led_timer(void)       //initialize timer value
{
setbit(TCCR1A,COM1A1);
setbit(TCCR1A,WGM11);
setbit(TCCR1B,WGM12);
setbit(TCCR1B,WGM13);
setbit(TCCR1B,CS12);
ICR1=6000;

}

void cooling_mode(void)
{
	OCR1A=6000;
}

void Heating_mode(void)
{
	OCR1A=3000;
}

void idle_mode(void)
{
	OCR1A=0;
}