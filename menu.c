#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "lib/lcd/hd44780.h"
#include "clock.h"

void prepareMenu(){	
	mainMenuList = (MenuItem*)malloc(sizeof(MenuItem));		//circular list
	
	MenuItem* menu0 = (MenuItem*)malloc(sizeof(MenuItem));
	menu0->id = 0;
	menu0->delayBetweenRefreshInMillis = -1;
	
	MenuItem* menu1 = (MenuItem*)malloc(sizeof(MenuItem));
	menu1->id = 1;
	menu1->delayBetweenRefreshInMillis = 1000;
	
	menu0->nextMenu = menu1;	
	menu1->nextMenu = menu0;		
	mainMenuList = menu0;
}

void printTitles(int id){
	uint8_t sec,min,hour,day,month,year,weekday;
	char title1[16]="",title2[16]="";
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
	}
	
}

