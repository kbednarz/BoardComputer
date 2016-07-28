#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "buttons_controller.h"

void prepareButtons(){
	DDRD  &= ~(1<<BUTTON1); //output
	PORTD |=  (1<<BUTTON1); //pull up resistor
};

int isClickedShortOrLong(){			//1-shortly 2-longly
	if ((PIND & (1<<BUTTON1)))
	{
		return 0;
	}
	int clickTimeCounter=0;
	while(!(PIND & (1<<BUTTON1)) && (clickTimeCounter < 12)){
		_delay_ms(20);
		clickTimeCounter++;
	}
	if(clickTimeCounter<20){
		return 1;
	} else return 2;
}