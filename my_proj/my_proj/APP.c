#include "APP.h"
int set_tempreture;

void sevensegm_display(uint8 data)  //used to display data on seven sigmant
{
		setbit(PORTA,6);          //turn first 7segmant on
		sevensegmant_w(data/10);  //display	first 7segmant data
		_delay_ms(10);            //wait to see it
		clearbit(PORTA,6);        //turn first 7segmant off
		setbit(PORTA,7);          //turn second 7segmant on
		sevensegmant_w(data%10);  //display second 7segmant data
		_delay_ms(10);            //wait to see it
		clearbit(PORTA,7);        //turn second 7segmant off
}

void app(void) //application
{
	signed int volt;
	float current_temp;
   	  
   
    while(readbit(PINC,3))  //if on (button is pressed)
	{
	 PORTD |= (1<<PD3); 	//enable pull-up
	 PORTD |= (1<<PD2); 	//enable pull-up
	 GICR |= (1<<INT1);  	//enable external interrupt 1
	 GICR |= (1<<INT0);	    //enable external interrupt 0
     sei();                 //enable global interrupt
		
	  volt=Temp_ADC_read();             //take the reading from the sensor
	  current_temp=(float)(5*volt)/1023;//conversation for LM45 Sensor
	  current_temp*=100;                //convert it ti degree
	    set_tempreture = EEPROM_Read(0x0100);   //take set temp from the memory
		
    	if ((uint8)current_temp<=((uint8)set_tempreture-5))//heater is on
		{
			setbit(PORTD,7);          //open the heater
			clearbit(PORTD,6);        //close the cooler
			sevensegm_display((uint8)current_temp);  //display current temperature
	     	Heating_mode();              //set led to blink every second 

		}
		
		else if ((uint8)current_temp>=((uint8)set_tempreture+5))//cooler is on
		{
			clearbit(PORTD,7);  //close the heater
			setbit(PORTD,6);    //open the cooler
    		sevensegm_display((uint8)current_temp);  //display current temperature
			cooling_mode();              //set led to be ON 
		}
		
		else
		{
		    sevensegm_display((uint8)current_temp); //display current temperature
		}
	}	
	if (readbit(PINC,3)==0)  //if off (button is released)
	{
		PORTD |= (0<<PD3); 	//disable pull-up
		PORTD |= (0<<PD2); 	//disable pull-up
		GICR |= (0<<INT1);	//disable external interrupt 1
		GICR |= (0<<INT0);	//disable external interrupt 0
		clearbit(SREG,7);   //disable global interrupt
		clearbit(PORTD,6);  //close the cooler
		clearbit(PORTD,7);  //close the heater
		idle_mode();        //set led to be OFF 

	}
}

void Setting_Mode() //Function used to setup temperature
{
PORTB=0xf0;  //to clear screen at first
	int i;
	int j;
	
	for (j=0;j<3;j++)
	{
	 for (i=0;i<40;i++)
	  {
		if (readbit(PIND,2)==0)
		{
			while (readbit(PIND,2)==0)  //wait till button unpressed
			{
				;
			}
			increase_temp();  //by 5 degree
			Setting_Mode();   //restart timing again
		}
		else if (readbit(PIND,3)==0)
		{
			while (readbit(PIND,3)==0)  //wait till button unpressed
			{
				;
			}
			decrease_temp();  //by 5 degree
			Setting_Mode();   //restart timing again
		}
		else
		sevensegm_display((uint8)set_tempreture);//display set temp
	}
    if (j<2)
     {
	  for (i=0;i<32500;i++)
	   {
		if (readbit(PIND,2)==0)
		{
			while (readbit(PIND,2)==0)  //wait till button unpressed
			{
				;
			}
			increase_temp();
			Setting_Mode();//restart timing again
		}
		else if (readbit(PIND,3)==0)
		{
			while (readbit(PIND,3)==0)  //wait till button unpressed
			{
				;
			}
			decrease_temp();
			Setting_Mode();//restart timing again
		}
		else
		{
		}
	 }
	}
  }
}

void increase_temp()  //Function to increase temperature
{
	if (set_tempreture>=35 && set_tempreture<=70)
	{
		set_tempreture+=5;
		EEPROM_Write(0x0100,set_tempreture);
		_delay_ms(10);
	}
	else
	{
	}
	
}  
void decrease_temp() //Function to decrease temperature
{
	if (set_tempreture>=40 && set_tempreture<=75)
	{
	   set_tempreture-=5;
	   EEPROM_Write(0x0100,set_tempreture);
       _delay_ms(10);
    }
	else
	{
	}
}
	
	