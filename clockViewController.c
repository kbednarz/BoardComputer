#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/lcd/hd44780.h"
#include "clock.h"
#include "menu.h"
#include "clockViewController.h"
#include "buttons_controller.h"

void turnOnUnderline(){
	lcd_command(_BV(LCD_DISPLAYMODE) | _BV(LCD_DISPLAYMODE_ON) | _BV(LCD_DISPLAYMODE_BLINK));
}
void turnOffUnderline(){
	lcd_command(_BV(LCD_DISPLAYMODE) | _BV(LCD_DISPLAYMODE_ON));
	
}

void clockView(){
	readClock(&sec,&min,&hour,&day,&month,&year,&weekday);
	sprintf(title1, "%02u:%02u:%02u", hour,min,sec);
	lcd_clrscr();
	lcd_goto(0x00);
	lcd_puts("Godz. ");
	lcd_puts(title1);
	lcd_goto(0x40);
	lcd_puts("Data: ");
	sprintf(title2, "%u.%u", day,month);
	lcd_puts(title2);
};

void timeSettings(){
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "> Set time");
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "  Set date");
	lcd_puts(title2);
}

void setTime(){
	uint8_t newHour,newMin;
	readClock(&sec,&newMin,&newHour,&day,&month,&year,&weekday);
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "Format: hh:mm:ss");
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "%02u:%02u:00", newHour,newMin);
	lcd_puts(title2);
	_delay_ms(500);
	lcd_goto(0x41);
	turnOnUnderline();
	char hourStr[2], minStr[2];
	int clickStatus;
	
	while ( !( (clickStatus = isClickedShortOrLong()) == 2) )
	{
		if (clickStatus == 1) {
			newHour++;
			if (newHour > 23) newHour = 0;
			lcd_goto(0x40);
			sprintf(hourStr, "%02u", newHour);
			lcd_puts(hourStr);
			lcd_goto(0x41);
		}
	}
	lcd_goto(0x44);
	while ( !( (clickStatus = isClickedShortOrLong()) == 2) )
	{
		if (clickStatus == 1) {
			newMin++;
			if (newMin > 59) newMin = 0;
			lcd_goto(0x43);
			sprintf(minStr, "%02u", newMin);
			lcd_puts(minStr);
			lcd_goto(0x44);
		}
	}
	
	turnOffUnderline();
	writeClock(newMin,newHour,day,month,year,weekday);
	
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "Saved");
	lcd_puts(title1);
}

void setDate(){
	uint8_t newDay,newMonth,newYear;
	readClock(&sec,&min,&hour,&newDay,&newMonth,&newYear,&weekday);
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "Format: d:m:y");
	lcd_puts(title1);
	lcd_goto(0x40);
	sprintf(title2, "%02u:%02u:20%02u", newDay,newMonth,newYear);
	lcd_puts(title2);
	_delay_ms(500);
	lcd_goto(0x41);
	turnOnUnderline();
	char tempStr[2];
	int clickStatus;
	
	while ( !( (clickStatus = isClickedShortOrLong()) == 2) )
	{
		if (clickStatus == 1) {
			newDay++;
			if (newDay > 31) newDay = 1;
			lcd_goto(0x40);
			sprintf(tempStr, "%02u", newDay);
			lcd_puts(tempStr);
			lcd_goto(0x41);
		}
	}
	lcd_goto(0x44);
	while ( !( (clickStatus = isClickedShortOrLong()) == 2) )
	{
		if (clickStatus == 1) {
			newMonth++;
			if (newMonth > 12) newMonth = 1;
			lcd_goto(0x43);
			sprintf(tempStr, "%02u", newMonth);
			lcd_puts(tempStr);
			lcd_goto(0x44);
		}
	}
	lcd_goto(0x49);
	while ( !( (clickStatus = isClickedShortOrLong()) == 2) )
	{
		if (clickStatus == 1) {
			newYear++;
			if (newYear > 99) newYear = 0;
			lcd_goto(0x48);
			sprintf(tempStr, "%02u", newYear);
			lcd_puts(tempStr);
			lcd_goto(0x49);
		}
	}
	
	turnOffUnderline();
	writeClock(min,hour,day,month,year,weekday);
	
	lcd_clrscr();
	lcd_goto(0x00);
	sprintf(title1, "Saved");
	lcd_puts(title1);
}

void exitToClockMenu(){
	sprintf(title1, "Exit");
	lcd_clrscr();
	lcd_goto(0x00);
	lcd_puts(title1);
}

int isLeapYear(int year) {
	if(((year%4==0)&&(year%100!=0))||((year%400==0)))
	return 1;
	else
	return 0;
}

int isDateValid(int dd,int mm,int yyyy) {

	int isValid=0;
	if(mm<0||mm>12) {
		isValid=0;
	}
	else {

		if((mm==1)||(mm==3)||(mm==5)||(mm==7)||(mm==8)||(mm==10)||(mm==12)) {
			if((dd>0)&&(dd<=31))
			isValid=1;
			}  else if((mm==4)||(mm==6)||(mm==9)||(mm==11)) {
			if((dd>0)&&(dd<=30))
			isValid=1;
			}  else {
			if(isLeapYear(yyyy)){
				if((dd>0)&&dd<30)
				isValid=1;
				} else {
				if((dd>0)&&dd<29)
				isValid=1;
			}
		}
	}
	return isValid;
}