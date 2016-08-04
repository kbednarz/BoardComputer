/*** Clock freq. 1MHz ***/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lib/lcd/hd44780.h"
#include "menu.h"
#include "buttons_controller.h"
#include "clock.h"
#include "adc.h"
#include "tachometer.h"
#include "interruptionsController.h"

int main(void)
{
    lcd_init();
    lcd_clrscr();
	initInterruptions();
	initClock();
	initAdc();
	initTacho();
	prepareButtons();
	prepareMenu();
	
	welcomingMessage();
	_delay_ms(1000);
	
	int status, delay10ms=0;
	while (1)
	{
		status = isClickedShortOrLong();
		if(status == 1){		//if pressed short
			mainMenuItem = mainMenuItem->nextMenu;
			mainMenuItem->callFunction();
			_delay_ms(500);
		} else if(status == 2)
		{	
			if( mainMenuItem->subMenu != NULL ){
				mainMenuItem = mainMenuItem->subMenu;
				mainMenuItem->callFunction();
				_delay_ms(500);
			}
		} else if(mainMenuItem->delayBetweenRefreshInMillis >=0){
			if(delay10ms <= (mainMenuItem->delayBetweenRefreshInMillis)/10) {
				delay10ms++;
				_delay_ms(10);
			} else{
				mainMenuItem->callFunction();
				delay10ms=0;
			}
		}
		
	}
}

//Interrupts for tachometer
ISR(INT0_vect) 
{
	rps_counter++;
}

ISR(TIMER1_COMPA_vect)		//interrupt every 500ms
{
	rps=rps_counter*2;
	rpm=rps*30;
	rps_counter=0;
}

