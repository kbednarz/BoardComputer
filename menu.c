#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "lib/lcd/hd44780.h"
#include "clock.h"
#include "adc.h"
#include "tachometer.h"

void prepareMenu(){	
	mainMenuItem = (MenuItem*)malloc(sizeof(MenuItem));		//circular list
	
	MenuItem* menu1 = (MenuItem*)malloc(sizeof(MenuItem));
	menu1->id = 1;
	menu1->delayBetweenRefreshInMillis = 1000;
	menu1->callFunction=clockView;
	
	MenuItem* menu2 = (MenuItem*)malloc(sizeof(MenuItem));
	menu2->id = 2;
	menu2->delayBetweenRefreshInMillis = 1000;
	menu2->callFunction=adcView;
	
	MenuItem* menu3 = (MenuItem*)malloc(sizeof(MenuItem));
	menu3->id = 3;
	menu3->delayBetweenRefreshInMillis = 500;
	menu3->callFunction=tachoView;
				
	menu1->nextMenu = menu2;	
	menu2->nextMenu = menu3;	
	menu3->nextMenu = menu1;	
	mainMenuItem = menu1;
}

void adcView(){
	float volt;
	volt = measureADC();
	sprintf(title1, "Volt: %.2f V", volt);
	lcd_clrscr();
	lcd_goto(0x00);
	lcd_puts(title1);
}

void clockView(){
	uint8_t sec,min,hour,day,month,year,weekday;
	readClock(&sec,&min,&hour,&day,&month,&year,&weekday);
	sprintf(title1, "%u:%u:%u", sec,min,hour);
	lcd_clrscr();
	lcd_goto(0x00);
	lcd_puts("Godz. ");
	lcd_puts(title1);
	lcd_goto(0x40);
	lcd_puts("Data: ");
	sprintf(title2, "%u:%u:%u", day,month,year);
	lcd_puts(title2);
};

void tachoView(){
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "RPS: %u", rps);
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "RPM: %u", rpm);
	lcd_puts(title2);
}

