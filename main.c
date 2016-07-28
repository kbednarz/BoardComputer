#ifndef F_CPU
#define F_CPU 1000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lib/lcd/hd44780.h"
#include "menu.h"
#include "buttons_controller.h"
#include "clock.h"
#include "adc.h"

int main(void)
{
	
    lcd_init();
    lcd_clrscr();
	
	initClock();
	writeClock(11,22,2,4,16,1);
	initAdc();
	prepareButtons();
	prepareMenu();
	printTitles(mainMenuList->id);
	int status, delay10ms=0;
	while (1)
	{
		status = isClickedShortOrLong();
		if(status == 1){		//if pressed short
			mainMenuList = mainMenuList->nextMenu;
			printTitles(mainMenuList->id);
		} else if(status == 2)
		{	
			lcd_clrscr();
			lcd_goto(0x00);
			lcd_puts("LONG");
		} 
		else if(mainMenuList->delayBetweenRefreshInMillis >=0){
			if(delay10ms <= (mainMenuList->delayBetweenRefreshInMillis)/10) {
				delay10ms++;
				_delay_ms(10);
			} else{
				printTitles(mainMenuList->id);
				delay10ms=0;
			}
		}
		
	}
}

