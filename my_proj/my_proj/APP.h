#ifndef APP_H_
#define APP_H_

//Includes
#include "IIC.h"
#include "ADC.h"
#include "EEPROM.h"
#include "StandredMacros.h"
#include "STD.h"
#include "seven_segmant.h"
#include "Timer.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL

//Prototypes
void sevensegm_display(uint8 data); //used to display data on seven sigmant
void app();           //application 
void Setting_Mode();  //Function used to setup temperature
void increase_temp(); //Function to increase temperature
void decrease_temp(); //Function to decrease temperature



#endif /* APP_H_ */