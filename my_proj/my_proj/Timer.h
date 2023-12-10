#ifndef TIMER_H_
#define TIMER_H_

#include "StandredMacros.h"
#include <avr/io.h>
#include <util/delay.h>

void init_led_timer(void);    //initialize timer value
void cooling_mode(void);         //Function to made led always on
void Heating_mode(void);         //Function to blink led every 1 sec


#endif 