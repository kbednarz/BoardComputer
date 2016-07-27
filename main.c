/*
 * BoardComputer.c
 *
 * Created: 2016-07-26 12:47:15
 * Author : Kamil
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lib/lcd/hd44780.h"
#include "clock.h"


int main(void)
{
	uint8_t sec,min,hour,day,month,year,weekday;
    lcd_init();
    lcd_clrscr();
    
	writeClock(11,22,2,4,16,1);
	char secString[16],dateString[16];
    while (1) 
    {
		readClock(&sec,&min,&hour,&day,&month,&year,&weekday);
		lcd_clrscr();
		lcd_goto(0x00);
		lcd_puts("smh: ");
		sprintf(secString, "%u:%u:%u", sec,min,hour);
		lcd_puts(secString);
		lcd_goto(0x40);
		lcd_puts("dmy: ");
		sprintf(dateString, "%u:%u:%u", day,month,year);
		lcd_puts(dateString);
		_delay_ms(1000);
    }
}

