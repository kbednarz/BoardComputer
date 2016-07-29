#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "lib/lcd/hd44780.h"
#include "clock.h"
#include "adc.h"
#include "tachometer.h"

void prepareMenu(){	
	mainMenuList = (MenuItem*)malloc(sizeof(MenuItem));		//circular list
	
	MenuItem* menu0 = (MenuItem*)malloc(sizeof(MenuItem));
	menu0->id = 0;
	menu0->delayBetweenRefreshInMillis = -1;
	
	MenuItem* menu1 = (MenuItem*)malloc(sizeof(MenuItem));
	menu1->id = 1;
	menu1->delayBetweenRefreshInMillis = 1000;
	
	MenuItem* menu2 = (MenuItem*)malloc(sizeof(MenuItem));
	menu2->id = 2;
	menu2->delayBetweenRefreshInMillis = 1000;
	
	MenuItem* menu3 = (MenuItem*)malloc(sizeof(MenuItem));
	menu3->id = 3;
	menu3->delayBetweenRefreshInMillis = 500;
		
	menu0->nextMenu = menu1;	
	menu1->nextMenu = menu2;	
	menu2->nextMenu = menu3;	
	menu3->nextMenu = menu0;	
	mainMenuList = menu0;
}

void printTitles(int id){
	uint8_t sec,min,hour,day,month,year,weekday;
	char title1[16]="",title2[16]="";
	float volt;
	switch (id){
		case 0:
			lcd_clrscr();
			strcpy(title1,"Hello!");
			lcd_puts(title1);
			break;
		case 1:
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
			break;
		case 2:
			volt = measureADC();
			sprintf(title1, "Volt: %.2f V", volt);
			lcd_clrscr();
			lcd_goto(0x00);
			lcd_puts(title1);		
			break;
		case 3:
			lcd_clrscr();
			lcd_goto(0x00);
			sprintf(title1, "RPS: %u", rps);
			lcd_puts(title1);
			lcd_goto(0x40);
			sprintf(title2, "RPM: %u", rpm);
			lcd_puts(title2);
			break;
	}
	
}

