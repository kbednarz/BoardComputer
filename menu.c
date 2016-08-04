#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "lib/lcd/hd44780.h"
#include "clock.h"
#include "adc.h"
#include "tachometer.h"
#include "clockViewController.h"

void prepareMenu(){	
	mainMenuItem = (MenuItem*)malloc(sizeof(MenuItem));		//circular list
	
	MenuItem* clockMenu = (MenuItem*)malloc(sizeof(MenuItem));
	clockMenu->delayBetweenRefreshInMillis = 1000;
	clockMenu->callFunction=clockView;	
		MenuItem* timeSettingsMenu = (MenuItem*)malloc(sizeof(MenuItem));
		timeSettingsMenu->delayBetweenRefreshInMillis = -1;
		timeSettingsMenu->callFunction=timeSettings;		
			MenuItem* setTimeMenu = (MenuItem*)malloc(sizeof(MenuItem));
			setTimeMenu->delayBetweenRefreshInMillis = -1;
			setTimeMenu->callFunction=setTime;
			MenuItem* exitClockMenu = (MenuItem*)malloc(sizeof(MenuItem));
			exitClockMenu->delayBetweenRefreshInMillis = -1;
			exitClockMenu->callFunction=exitToClockMenu;
			
	MenuItem* adcMenu = (MenuItem*)malloc(sizeof(MenuItem));
	adcMenu->delayBetweenRefreshInMillis = 1000;
	adcMenu->callFunction=adcView;
	
	MenuItem* tachoMenu = (MenuItem*)malloc(sizeof(MenuItem));
	tachoMenu->delayBetweenRefreshInMillis = 500;
	tachoMenu->callFunction=tachoView;
				
	clockMenu->nextMenu = adcMenu;
	clockMenu->subMenu = timeSettingsMenu;	
		timeSettingsMenu->nextMenu = exitClockMenu;
		timeSettingsMenu->subMenu = setTimeMenu;
			setTimeMenu->nextMenu = timeSettingsMenu;
			setTimeMenu->subMenu = NULL;
		exitClockMenu->nextMenu = timeSettingsMenu;
		exitClockMenu->subMenu = clockMenu;


	adcMenu->nextMenu = tachoMenu;
	adcMenu->subMenu = NULL;
		
	tachoMenu->nextMenu = clockMenu;	
	tachoMenu->subMenu = NULL;
	
	mainMenuItem = clockMenu;
}

void adcView(){
	float volt;
	volt = measureADC();
	sprintf(title1, "Volt: %.2f V", volt);
	lcd_clrscr();
	lcd_goto(0x00);
	lcd_puts(title1);
}

void tachoView(){
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "RPS: %u", rps);
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "RPM: %u", rpm);
	lcd_puts(title2);
}

void welcomingMessage(){
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "Hello rider!");
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "Turn on lights");
	lcd_puts(title2);
}
